import fs from 'node:fs';
import fsp from 'node:fs/promises';
import path from 'node:path';
import crypto from 'node:crypto';
import { AUDIO_EXTENSIONS, CACHE_DIR } from './config.js';
import { probeTrack } from './metadata.js';

export interface LibraryTrack {
  /** Stable id derived from the absolute path. */
  id: string;
  path: string;
  title: string;
  artist: string;
  album: string;
  trackNo: number | null;
  durationSeconds: number;
  hasArt: boolean;
  /** DRM/unreadable files are flagged and excluded from sync. */
  drmOrUnreadable: boolean;
}

export interface LibraryScan {
  root: string;
  scannedAt: string;
  trackCount: number;
  skippedCount: number;
  tracks: LibraryTrack[];
}

function idForPath(p: string): string {
  return crypto.createHash('sha1').update(p).digest('hex').slice(0, 16);
}

function cacheFileFor(root: string): string {
  const key = crypto.createHash('sha1').update(path.resolve(root)).digest('hex').slice(0, 16);
  return path.join(CACHE_DIR, `scan-${key}.json`);
}

async function walk(dir: string, out: string[]): Promise<void> {
  let entries: fs.Dirent[];
  try {
    entries = await fsp.readdir(dir, { withFileTypes: true });
  } catch {
    return; // unreadable dir — skip
  }
  for (const entry of entries) {
    const full = path.join(dir, entry.name);
    if (entry.name.startsWith('.')) continue; // skip dotfiles/dotdirs
    if (entry.isDirectory()) {
      // Skip Apple Music's internal database bundle.
      if (entry.name.endsWith('.musiclibrary')) continue;
      await walk(full, out);
    } else if (entry.isFile()) {
      const ext = path.extname(entry.name).toLowerCase();
      if (AUDIO_EXTENSIONS.includes(ext)) out.push(full);
    }
  }
}

export function readCachedScan(root: string): LibraryScan | null {
  const f = cacheFileFor(root);
  if (!fs.existsSync(f)) return null;
  try {
    return JSON.parse(fs.readFileSync(f, 'utf8')) as LibraryScan;
  } catch {
    return null;
  }
}

export type ScanProgress = (done: number, total: number) => void;

/**
 * Recursively scan `root` for audio, ffprobe each file for tags/duration/art,
 * and return a sorted library. DRM/unreadable files are kept but flagged so
 * the UI can show them; they are excluded from sync. Results are cached to
 * disk keyed by the root path.
 */
export async function scanLibrary(
  root: string,
  onProgress?: ScanProgress,
  concurrency = 8,
): Promise<LibraryScan> {
  const resolved = path.resolve(root);
  const files: string[] = [];
  await walk(resolved, files);
  files.sort((a, b) => a.localeCompare(b));

  const tracks: LibraryTrack[] = new Array(files.length);
  let done = 0;
  let cursor = 0;

  async function worker(): Promise<void> {
    while (true) {
      const i = cursor++;
      if (i >= files.length) return;
      const file = files[i];
      const meta = await probeTrack(file);
      tracks[i] = {
        id: idForPath(file),
        path: file,
        title: meta.title,
        artist: meta.artist,
        album: meta.album,
        trackNo: meta.trackNo,
        durationSeconds: meta.durationSeconds,
        hasArt: meta.hasArt,
        drmOrUnreadable: meta.unreadable,
      };
      done++;
      if (onProgress && (done % 5 === 0 || done === files.length)) {
        onProgress(done, files.length);
      }
    }
  }

  const workers = Array.from({ length: Math.min(concurrency, files.length || 1) }, () => worker());
  await Promise.all(workers);

  const skippedCount = tracks.filter((t) => t.drmOrUnreadable).length;
  const scan: LibraryScan = {
    root: resolved,
    scannedAt: new Date().toISOString(),
    trackCount: tracks.length,
    skippedCount,
    tracks,
  };

  try {
    fs.mkdirSync(CACHE_DIR, { recursive: true });
    fs.writeFileSync(cacheFileFor(resolved), JSON.stringify(scan));
  } catch {
    /* cache write best-effort */
  }

  return scan;
}
