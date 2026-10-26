import fs from 'node:fs';
import fsp from 'node:fs/promises';
import path from 'node:path';
import { EventEmitter } from 'node:events';
import { DEFAULT_CORE_BUILD_DIR } from './config.js';

export interface CoreInfo {
  available: boolean;
  buildDir: string;
  version: string | null;
  author: string | null;
  shortname: string | null;
  dateRelease: string | null;
  /** Top-level dirs that will be pushed to the card. */
  topLevelDirs: string[];
}

/** Find core.json inside a core build dir and pull its metadata.version. */
function readCoreMeta(buildDir: string): Pick<CoreInfo, 'version' | 'author' | 'shortname' | 'dateRelease'> {
  const empty = { version: null, author: null, shortname: null, dateRelease: null };
  try {
    const coresDir = path.join(buildDir, 'Cores');
    if (!fs.existsSync(coresDir)) return empty;
    for (const entry of fs.readdirSync(coresDir)) {
      const coreJson = path.join(coresDir, entry, 'core.json');
      if (fs.existsSync(coreJson)) {
        const j = JSON.parse(fs.readFileSync(coreJson, 'utf8'));
        const meta = j?.core?.metadata ?? {};
        return {
          version: meta.version ?? null,
          author: meta.author ?? null,
          shortname: meta.shortname ?? null,
          dateRelease: meta.date_release ?? null,
        };
      }
    }
  } catch {
    /* ignore */
  }
  return empty;
}

/** Inspect a core build dir (or the configured default). */
export function inspectCore(buildDir?: string): CoreInfo {
  const dir = buildDir || DEFAULT_CORE_BUILD_DIR;
  if (!dir || !fs.existsSync(dir)) {
    return {
      available: false,
      buildDir: dir || '',
      version: null,
      author: null,
      shortname: null,
      dateRelease: null,
      topLevelDirs: [],
    };
  }
  const topLevelDirs = fs
    .readdirSync(dir, { withFileTypes: true })
    .filter((e) => e.isDirectory())
    .map((e) => e.name);
  return { available: true, buildDir: dir, ...readCoreMeta(dir), topLevelDirs };
}

/**
 * Read the version currently on the card (if any) for "current vs available".
 * Looks for the same core.json under <card>/Cores/<*>/core.json.
 */
export function readCardCoreVersion(cardPath: string): string | null {
  return readCoreMeta(cardPath).version;
}

async function copyDir(
  src: string,
  dest: string,
  onFile: (rel: string) => void,
  onSkip: (rel: string) => void,
  rel = '',
): Promise<void> {
  await fsp.mkdir(dest, { recursive: true });
  const entries = await fsp.readdir(src, { withFileTypes: true });
  for (const e of entries) {
    if (e.name === '.DS_Store') continue;
    const s = path.join(src, e.name);
    const d = path.join(dest, e.name);
    const r = path.join(rel, e.name);
    if (e.isDirectory()) {
      await copyDir(s, d, onFile, onSkip, r);
    } else if (e.isFile()) {
      // CRITICAL guard: never overwrite the card's music library.
      if (e.name.toLowerCase() === 'music.iso') {
        onSkip(r);
        continue;
      }
      await fsp.copyFile(s, d);
      onFile(r);
    }
  }
}

export type CoreUpdateEvent =
  | { type: 'start'; buildDir: string; target: string }
  | { type: 'file'; rel: string }
  | { type: 'log'; message: string }
  | { type: 'done'; files: number }
  | { type: 'error'; message: string };

export interface CoreUpdateJob {
  id: string;
  emitter: EventEmitter;
  status: 'running' | 'done' | 'error';
  events: CoreUpdateEvent[];
}

const coreJobs = new Map<string, CoreUpdateJob>();
export function getCoreJob(id: string): CoreUpdateJob | undefined {
  return coreJobs.get(id);
}

/**
 * Push the core build tree (Cores/, Assets/[non-music], Platforms/) to the
 * card. CRITICAL: never overwrite the card's music.iso. We copy everything in
 * the build dir EXCEPT any music.iso it might contain, so an existing library
 * on the card is preserved.
 */
export function startCoreUpdate(buildDir: string, target: string): CoreUpdateJob {
  const id = `core-${Date.now()}`;
  const emitter = new EventEmitter();
  const job: CoreUpdateJob = { id, emitter, status: 'running', events: [] };
  coreJobs.set(id, job);
  const emit = (e: CoreUpdateEvent) => {
    job.events.push(e);
    emitter.emit('event', e);
  };

  void (async () => {
    try {
      if (!buildDir || !fs.existsSync(buildDir)) throw new Error(`Core build dir not found: ${buildDir}`);
      if (!fs.existsSync(target)) throw new Error(`Target not found: ${target}`);
      emit({ type: 'start', buildDir, target });

      let files = 0;
      const entries = await fsp.readdir(buildDir, { withFileTypes: true });
      for (const e of entries) {
        if (e.name === '.DS_Store') continue;
        const src = path.join(buildDir, e.name);
        const dest = path.join(target, e.name);
        if (e.isDirectory()) {
          await copyDir(
            src,
            dest,
            (rel) => {
              files++;
              if (files % 5 === 0) emit({ type: 'file', rel: `${e.name}/${rel}` });
            },
            (rel) => emit({ type: 'log', message: `Skipped (preserving library): ${e.name}/${rel}` }),
          );
        } else if (e.isFile()) {
          if (e.name.toLowerCase() === 'music.iso') {
            emit({ type: 'log', message: `Skipped (preserving library): ${e.name}` });
          } else {
            await fsp.copyFile(src, dest);
            files++;
          }
        }
      }
      emit({ type: 'log', message: 'music.iso on card left untouched.' });
      job.status = 'done';
      emit({ type: 'done', files });
    } catch (err: any) {
      job.status = 'error';
      emit({ type: 'error', message: err?.message ?? String(err) });
    }
  })();

  return job;
}
