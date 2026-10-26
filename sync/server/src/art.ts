import fs from 'node:fs';
import fsp from 'node:fs/promises';
import path from 'node:path';
import crypto from 'node:crypto';
import { FFMPEG, CACHE_DIR } from './config.js';
import { run } from './proc.js';

/** Exact on-device art format: ART_DIM×ART_DIM RGB565 little-endian, no header. */
export const ART_DIM = 200;
export const ART_BYTES = ART_DIM * ART_DIM * 2;

// Placeholder eighth-note geometry is authored at 100px and scaled to ART_DIM.
const NOTE_K = ART_DIM / 100;
function placeholderNoteFilter(): string {
  const box = (x: number, y: number, w: number, h: number) =>
    `drawbox=x=${x * NOTE_K}:y=${y * NOTE_K}:w=${w * NOTE_K}:h=${h * NOTE_K}:color=black:t=fill`;
  return [box(58, 22, 5, 46), box(44, 60, 20, 12), box(58, 20, 12, 5)].join(',');
}

const THUMB_DIR = path.join(CACHE_DIR, 'thumbs');

/**
 * Produce (and cache) a small JPEG thumbnail of a track's embedded cover for
 * the UI. Returns the JPEG bytes, or null if the file has no usable art.
 * Distinct from buildArtFromSource (which makes the exact 20000-byte RGB565
 * the device needs) — this is purely for on-screen preview.
 */
export async function getThumbnail(sourceAudio: string, size = 80): Promise<Buffer | null> {
  fs.mkdirSync(THUMB_DIR, { recursive: true });
  const key = crypto.createHash('sha1').update(`${sourceAudio}|${size}`).digest('hex').slice(0, 20);
  const cached = path.join(THUMB_DIR, `${key}.jpg`);
  if (fs.existsSync(cached)) {
    try {
      const buf = await fsp.readFile(cached);
      if (buf.length > 0) return buf;
    } catch {
      /* fall through and regenerate */
    }
  }

  const res = await run(FFMPEG, [
    '-nostdin',
    '-y',
    '-v',
    'error',
    '-i',
    sourceAudio,
    '-an',
    '-frames:v',
    '1',
    '-vf',
    `scale=${size}:${size}:force_original_aspect_ratio=increase,crop=${size}:${size}`,
    '-f',
    'mjpeg',
    cached,
  ]);

  if (res.code !== 0) {
    await fsp.rm(cached, { force: true });
    return null;
  }
  try {
    const buf = await fsp.readFile(cached);
    return buf.length > 0 ? buf : null;
  } catch {
    return null;
  }
}

/**
 * Build the gray eighth-note placeholder, identical to the reference
 * art_convert.sh. 100x100 solid gray with a crude note drawn in black,
 * encoded as rgb565le rawvideo (exactly 20000 bytes).
 */
export async function buildPlaceholder(outPath: string): Promise<void> {
  const res = await run(FFMPEG, [
    '-nostdin',
    '-y',
    '-v',
    'error',
    '-f',
    'lavfi',
    '-i',
    `color=c=0xC8C8C8:s=${ART_DIM}x${ART_DIM}`,
    '-vf',
    placeholderNoteFilter(),
    '-frames:v',
    '1',
    '-pix_fmt',
    'rgb565le',
    '-f',
    'rawvideo',
    outPath,
  ]);
  if (res.code !== 0) throw new Error(`placeholder ffmpeg failed: ${res.stderr}`);
  assertArtSize(outPath);
}

/**
 * Extract a file's embedded cover, scale to 100x100, and write rgb565le raw.
 * Returns true on success; false when there is no usable art (caller should
 * fall back to the placeholder). Two-step pipeline matching the reference
 * scripts (extract PNG, then convert) but kept in one temp dir.
 *
 * NOTE: rgb565LE is intentional — verified correct for the little-endian
 * device. Do NOT switch to rgb565be.
 */
export async function buildArtFromSource(sourceAudio: string, outBin: string, tmpDir: string): Promise<boolean> {
  const tmpPng = path.join(tmpDir, `cover-${path.basename(outBin)}.png`);
  const extract = await run(FFMPEG, [
    '-nostdin',
    '-y',
    '-v',
    'error',
    '-i',
    sourceAudio,
    '-an',
    '-frames:v',
    '1',
    tmpPng,
  ]);

  let ok = extract.code === 0;
  try {
    ok = ok && fs.statSync(tmpPng).size > 0;
  } catch {
    ok = false;
  }
  if (!ok) {
    await fsp.rm(tmpPng, { force: true });
    return false;
  }

  const convert = await run(FFMPEG, [
    '-nostdin',
    '-y',
    '-v',
    'error',
    '-i',
    tmpPng,
    '-vf',
    `scale=${ART_DIM}:${ART_DIM}`,
    '-pix_fmt',
    'rgb565le',
    '-f',
    'rawvideo',
    outBin,
  ]);
  await fsp.rm(tmpPng, { force: true });

  if (convert.code !== 0) return false;
  try {
    assertArtSize(outBin);
  } catch {
    await fsp.rm(outBin, { force: true });
    return false;
  }
  return true;
}

function assertArtSize(p: string): void {
  const size = fs.statSync(p).size;
  if (size !== ART_BYTES) {
    throw new Error(`art ${p} is ${size} bytes, expected ${ART_BYTES}`);
  }
}
