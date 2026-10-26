import os from 'node:os';
import path from 'node:path';
import fs from 'node:fs';

// 4380 chosen to avoid colliding with common dev servers (Astro defaults to 4321).
export const PORT = Number(process.env.PORT ?? 4380);
export const HOME = os.homedir();

// Where we keep cache, staging dirs, generated ISOs, etc.
export const APP_DATA_DIR = path.join(HOME, '.pockettunes-sync');
export const CACHE_DIR = path.join(APP_DATA_DIR, 'cache');
export const STAGE_ROOT = path.join(APP_DATA_DIR, 'staging');
export const ISO_OUT_DIR = path.join(APP_DATA_DIR, 'iso');

// External tool locations. Homebrew ffmpeg lives in /opt/homebrew/bin on Apple Silicon.
// We prepend the common homebrew bin dirs to PATH so child processes resolve the tools.
export const FFMPEG = process.env.FFMPEG_PATH ?? 'ffmpeg';
export const FFPROBE = process.env.FFPROBE_PATH ?? 'ffprobe';

export const EXTRA_PATH = ['/opt/homebrew/bin', '/usr/local/bin'];
export const CHILD_ENV: NodeJS.ProcessEnv = {
  ...process.env,
  PATH: [...EXTRA_PATH, process.env.PATH ?? ''].join(':'),
};

// Audio extensions we recognise as importable sources.
export const AUDIO_EXTENSIONS = ['.m4a', '.mp3', '.flac', '.aac', '.wav', '.alac'];

// Default music source folder (Apple Music lives under ~/Music).
export const DEFAULT_LIBRARY_DIR = path.join(HOME, 'Music');

// On-device layout. The Pocket core mounts ONE iso and reads files from it.
// We write the ISO to <SDCARD>/Assets/pockettunes/common/music.iso
export const MUSIC_ISO_REL = path.join('Assets', 'pockettunes', 'common', 'music.iso');
export const ISO_VOLUME_NAME = 'MUSIC';

// Default "core build directory" used by the Update Core feature.
// Resolution order, first hit wins:
//   1. CORE_BUILD_DIR env var
//   2. a local pointer file at ~/.pockettunes-sync/core-build-dir.txt holding the
//      absolute path to your built core (one line). It lives outside the repo so
//      machine-specific paths never get committed.
//   3. '' — the feature stays off until you point it at a built core.
function resolveCoreBuildDir(): string {
  const fromEnv = process.env.CORE_BUILD_DIR?.trim();
  if (fromEnv) return fromEnv;
  try {
    const p = fs.readFileSync(path.join(APP_DATA_DIR, 'core-build-dir.txt'), 'utf8').trim();
    if (p && fs.existsSync(p)) return p;
  } catch {
    // no pointer file yet; fall through to disabled
  }
  return '';
}

export const DEFAULT_CORE_BUILD_DIR = resolveCoreBuildDir();

export function ensureDirs(): void {
  for (const d of [APP_DATA_DIR, CACHE_DIR, STAGE_ROOT, ISO_OUT_DIR]) {
    fs.mkdirSync(d, { recursive: true });
  }
}
