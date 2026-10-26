import { FFMPEG } from './config.js';
import { run } from './proc.js';

// Loudness normalization targets (ReplayGain-style, applied as gain on device).
const TARGET_LUFS = -11; // portable, loud-but-clean target (pure gain, peak-limited)
const PEAK_CEILING_DBTP = -1; // never push the true peak past this (anti-clip)

/**
 * Compute a per-track loudness gain (Q8, 256 = unity) from ffmpeg's ebur128
 * summary. Pure gain — preserves dynamics, never boosts a track's true peak past
 * the ceiling, so nothing clips. Returns 256 (unity) if the measurement can't be
 * parsed, so playback is simply un-normalized rather than wrong.
 */
function gainQ8FromEbur128(stderr: string): number {
  const iAll = [...stderr.matchAll(/I:\s*(-?\d+(?:\.\d+)?)\s*LUFS/g)];
  if (iAll.length === 0) return 256;
  const I = parseFloat(iAll[iAll.length - 1][1]);
  if (!Number.isFinite(I) || I <= -70) return 256; // silent / unmeasurable
  const pAll = [...stderr.matchAll(/Peak:\s*(-?\d+(?:\.\d+)?)\s*dBFS/g)];
  const tp = pAll.length ? parseFloat(pAll[pAll.length - 1][1]) : -1; // assume ~full peak if absent
  let gainDb = TARGET_LUFS - I;
  const maxGainDb = PEAK_CEILING_DBTP - tp; // keep true peak under the ceiling
  if (gainDb > maxGainDb) gainDb = maxGainDb;
  if (gainDb > 12) gainDb = 12;
  if (gainDb < -12) gainDb = -12;
  let q8 = Math.round(Math.pow(10, gainDb / 20) * 256);
  if (q8 < 8) q8 = 8;
  if (q8 > 2048) q8 = 2048;
  return q8;
}

/**
 * Transcode one source file to the exact on-device MP3 format:
 *   48kHz / stereo / 256 kbps, metadata stripped.
 * Also measures loudness in the same pass (ebur128 passes audio through
 * unchanged) and returns a per-track gain for ReplayGain-style normalization on
 * device. `-nostdin` is mandatory so ffmpeg doesn't consume our stdin in a loop.
 */
export async function transcodeTrack(input: string, output: string): Promise<{ gainQ8: number }> {
  const res = await run(FFMPEG, [
    '-nostdin',
    '-y',
    '-v',
    'info', // ebur128 prints its summary at info level
    '-i',
    input,
    '-map_metadata',
    '-1',
    '-vn',
    '-af',
    'ebur128=peak=true', // measure only; audio passes through unchanged
    '-ar',
    '48000',
    '-ac',
    '2',
    '-c:a',
    'libmp3lame',
    '-b:a',
    '320k', // highest standard MP3 bitrate (device decodes MP3)
    output,
  ]);
  if (res.code !== 0) {
    throw new Error(`transcode failed (${input}): ${res.stderr.trim() || 'ffmpeg error'}`);
  }
  return { gainQ8: gainQ8FromEbur128(res.stderr) };
}

/**
 * Build the hybrid ISO from a staging dir using hdiutil (macOS):
 *   hdiutil makehybrid -o music.iso -iso -joliet -default-volume-name MUSIC <stage>
 */
export async function buildIso(stageDir: string, isoOut: string, volumeName: string): Promise<void> {
  const res = await run(
    'hdiutil',
    ['makehybrid', '-o', isoOut, '-iso', '-joliet', '-default-volume-name', volumeName, stageDir],
    { timeoutMs: 30 * 60 * 1000 },
  );
  if (res.code !== 0) {
    throw new Error(`hdiutil makehybrid failed: ${res.stderr.trim() || res.stdout.trim()}`);
  }
}
