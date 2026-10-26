import fs from 'node:fs';
import fsp from 'node:fs/promises';
import path from 'node:path';
import { EventEmitter } from 'node:events';
import { STAGE_ROOT, ISO_OUT_DIR, ISO_VOLUME_NAME, MUSIC_ISO_REL, ensureDirs } from './config.js';
import { transcodeTrack, buildIso } from './transcode.js';
import { buildArtFromSource, buildPlaceholder } from './art.js';
import type { LibraryTrack } from './library.js';

export interface SyncRequestTrack {
  path: string;
  title: string;
  artist: string;
  album: string;
  durationSeconds: number;
  hasArt: boolean;
}

export interface SyncRequest {
  /** Tracks in the desired library order. */
  tracks: SyncRequestTrack[];
  /** Mount path of the target volume, OR a plain target folder for testing. */
  target: string;
  /** If true, eject the volume on completion (macOS). */
  eject?: boolean;
}

export type SyncEvent =
  | { type: 'start'; total: number }
  | { type: 'phase'; phase: string; message: string }
  | { type: 'track'; index: number; total: number; title: string; status: 'ok' | 'failed'; reason?: string }
  | { type: 'log'; message: string }
  | { type: 'progress'; done: number; total: number; pct: number }
  | { type: 'done'; isoBytes: number; written: number; failed: number; target: string }
  | { type: 'error'; message: string };

export interface SyncJob {
  id: string;
  emitter: EventEmitter;
  status: 'running' | 'done' | 'error';
  events: SyncEvent[];
}

const jobs = new Map<string, SyncJob>();

export function getJob(id: string): SyncJob | undefined {
  return jobs.get(id);
}

function pad4(n: number): string {
  return String(n).padStart(4, '0');
}

/** TSV-escape a field: tabs and newlines would break the 5-column format. */
function tsvField(s: string): string {
  return s.replace(/[\t\r\n]+/g, ' ').trim();
}

/**
 * Run the full sync pipeline for a job. Emits SyncEvents as it goes.
 * Phases: stage prep -> transcode+art per track -> playlist.tsv -> ISO ->
 * write to card. Numbers tracks 0001.. in the provided order.
 */
export function startSync(req: SyncRequest): SyncJob {
  ensureDirs();
  const id = `sync-${Date.now()}`;
  const emitter = new EventEmitter();
  const job: SyncJob = { id, emitter, status: 'running', events: [] };
  jobs.set(id, job);

  const emit = (e: SyncEvent) => {
    job.events.push(e);
    emitter.emit('event', e);
  };

  // Run async; the route returns the job id immediately and the client
  // subscribes to the SSE stream.
  void (async () => {
    const stageDir = path.join(STAGE_ROOT, id);
    const artDir = path.join(stageDir, 'art');
    const isoOut = path.join(ISO_OUT_DIR, `${id}.iso`); // built on the Mac (hdiutil can't write to exFAT)
    try {
      const total = req.tracks.length;
      if (total === 0) throw new Error('No tracks selected.');
      emit({ type: 'start', total });

      emit({ type: 'phase', phase: 'stage', message: 'Preparing staging directory' });
      await fsp.rm(stageDir, { recursive: true, force: true });
      await fsp.mkdir(artDir, { recursive: true });

      // Placeholder art (used for tracks with no embedded cover).
      await buildPlaceholder(path.join(artDir, 'placeholder.bin'));

      const playlistLines: string[] = [];
      let written = 0;
      let failed = 0;

      emit({ type: 'phase', phase: 'transcode', message: 'Transcoding tracks and converting art' });
      for (let i = 0; i < req.tracks.length; i++) {
        const t = req.tracks[i];
        const num = pad4(i + 1);
        const mp3Path = path.join(stageDir, `${num}.mp3`);
        try {
          const { gainQ8 } = await transcodeTrack(t.path, mp3Path);

          // Art: try embedded; fall back to placeholder by stem mapping.
          const artBin = path.join(artDir, `${num}.bin`);
          let gotArt = false;
          if (t.hasArt) {
            gotArt = await buildArtFromSource(t.path, artBin, stageDir);
          }
          if (!gotArt) {
            // Symlink/copy placeholder so every stem maps to a 20000-byte file.
            await fsp.copyFile(path.join(artDir, 'placeholder.bin'), artBin);
          }

          playlistLines.push(
            [
              `${num}.mp3`,
              tsvField(t.title),
              tsvField(t.artist),
              tsvField(t.album),
              String(Math.max(0, Math.round(t.durationSeconds))),
              String(gainQ8), // per-track loudness gain (Q8, 256 = unity)
            ].join('\t'),
          );
          written++;
          emit({ type: 'track', index: i + 1, total, title: t.title, status: 'ok' });
        } catch (err: any) {
          failed++;
          await fsp.rm(mp3Path, { force: true });
          emit({
            type: 'track',
            index: i + 1,
            total,
            title: t.title,
            status: 'failed',
            reason: err?.message ?? String(err),
          });
        }
        const done = i + 1;
        emit({ type: 'progress', done, total, pct: Math.round((done / total) * 100) });
      }

      if (written === 0) throw new Error('All selected tracks failed to transcode.');

      emit({ type: 'phase', phase: 'playlist', message: 'Writing playlist.tsv' });
      await fsp.writeFile(path.join(stageDir, 'playlist.tsv'), playlistLines.join('\n') + '\n', 'utf8');

      // hdiutil makehybrid can only write to APFS/HFS, not exFAT, so build the ISO
      // on the Mac, then copy it onto the card. Copy to a temp file and rename it
      // into place so a dropped/partial copy never corrupts the live music.iso.
      emit({ type: 'phase', phase: 'iso', message: 'Building ISO on the Mac (hdiutil makehybrid)' });
      await fsp.rm(isoOut, { force: true });
      await buildIso(stageDir, isoOut, ISO_VOLUME_NAME);
      const isoBytes = fs.statSync(isoOut).size;
      emit({ type: 'log', message: `ISO built: ${(isoBytes / 1024 / 1024).toFixed(1)} MB` });

      emit({ type: 'phase', phase: 'write', message: 'Copying music.iso to the card' });
      const destIso = path.join(req.target, MUSIC_ISO_REL);
      const tmpIso = destIso.replace(/\.iso$/i, '.tmp.iso');
      await fsp.mkdir(path.dirname(destIso), { recursive: true });
      await fsp.rm(tmpIso, { force: true });
      await fsp.copyFile(isoOut, tmpIso);
      const tmpBytes = fs.statSync(tmpIso).size;
      if (tmpBytes !== isoBytes) {
        await fsp.rm(tmpIso, { force: true });
        throw new Error(`Copy to card incomplete: built=${isoBytes} copied=${tmpBytes} (card full or write dropped). Live music.iso left untouched.`);
      }
      await fsp.rm(destIso, { force: true });
      await fsp.rename(tmpIso, destIso);
      emit({ type: 'log', message: `Wrote ${destIso}` });
      await fsp.rm(isoOut, { force: true }); // free the Mac copy right away (Mac disk is tight)

      if (req.eject) {
        emit({ type: 'phase', phase: 'eject', message: 'Ejecting volume' });
        const { ejectVolume } = await import('./volumes.js');
        const r = await ejectVolume(req.target);
        emit({ type: 'log', message: r.ok ? 'Ejected OK' : `Eject failed: ${r.message}` });
      }

      job.status = 'done';
      emit({ type: 'done', isoBytes, written, failed, target: req.target });
    } catch (err: any) {
      job.status = 'error';
      emit({ type: 'error', message: err?.message ?? String(err) });
    } finally {
      // Clean up staging and the Mac ISO copy (don't leave ~4GB on a tight disk).
      await fsp.rm(stageDir, { recursive: true, force: true }).catch(() => {});
      await fsp.rm(isoOut, { force: true }).catch(() => {});
    }
  })();

  return job;
}

/** Estimate output size for a selection (~2.4MB/min at 320 kbps). */
export function estimateSizeBytes(tracks: { durationSeconds: number }[]): number {
  const totalMin = tracks.reduce((s, t) => s + (t.durationSeconds || 0) / 60, 0);
  return Math.round(totalMin * 2.4 * 1024 * 1024);
}

export type { LibraryTrack };
