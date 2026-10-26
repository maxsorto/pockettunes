import fs from 'node:fs';
import path from 'node:path';
import zlib from 'node:zlib';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { APP_DATA_DIR } from './config.js';

const __dirname = path.dirname(fileURLToPath(import.meta.url));

// The Studio feature renders the on-device UI via the REAL firmware renderer
// (ipod_ui.c). It needs the firmware source dir to put on the C include path.
// Resolution: PREVIEW_SRC_DIR env, else ~/.pockettunes-sync/firmware-src-dir.txt,
// else firmware/src in this repository (sync/ sits next to firmware/).
function resolveFirmwareSrcDir(): string {
  const env = process.env.PREVIEW_SRC_DIR?.trim();
  if (env) return env;
  try {
    const p = fs.readFileSync(path.join(APP_DATA_DIR, 'firmware-src-dir.txt'), 'utf8').trim();
    if (p) return p;
  } catch {
    // no pointer file
  }
  const inRepo = path.resolve(__dirname, '../../../firmware/src');
  if (fs.existsSync(path.join(inRepo, 'ipod_ui.c'))) return inRepo;
  return '';
}
const RENDER_SRC = path.resolve(__dirname, '../preview/render.c');
const binPath = (scale: number) => path.join(APP_DATA_DIR, `preview-render-${scale}x.bin`);
const outDir = (scale: number) => path.join(APP_DATA_DIR, `preview-${scale}x`);

interface ScreenDef {
  name: string;
  label: string;
  file: string;
}

// Order = display order. Now Playing and Main Menu lead, per request.
const SCREENS: ScreenDef[] = [
  { name: 'now_playing', label: 'Now Playing', file: 'nowplaying.ppm' },
  { name: 'menu_video', label: 'Main Menu (Video)', file: 'menu_video.ppm' },
  { name: 'menu_classic', label: 'Main Menu (Classic)', file: 'menu_classic.ppm' },
  { name: 'menu_mini', label: 'Main Menu (Mini)', file: 'menu_mini.ppm' },
  { name: 'marquee', label: 'Now Playing (long title)', file: 'marquee.ppm' },
  { name: 'boot', label: 'Boot', file: 'boot.ppm' },
];

// --- minimal PPM (P6) -> PNG, no external deps ------------------------------
const CRC_TABLE = (() => {
  const t = new Uint32Array(256);
  for (let n = 0; n < 256; n++) {
    let c = n;
    for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1;
    t[n] = c >>> 0;
  }
  return t;
})();

function crc32(buf: Buffer): number {
  let c = 0xffffffff;
  for (let i = 0; i < buf.length; i++) c = CRC_TABLE[(c ^ buf[i]) & 0xff] ^ (c >>> 8);
  return (c ^ 0xffffffff) >>> 0;
}

function pngChunk(type: string, data: Buffer): Buffer {
  const len = Buffer.alloc(4);
  len.writeUInt32BE(data.length, 0);
  const body = Buffer.concat([Buffer.from(type, 'ascii'), data]);
  const crc = Buffer.alloc(4);
  crc.writeUInt32BE(crc32(body), 0);
  return Buffer.concat([len, body, crc]);
}

function parsePPM(buf: Buffer): { w: number; h: number; pixels: Buffer } {
  let pos = 0;
  const isWs = (b: number) => b === 32 || b === 9 || b === 10 || b === 13;
  const token = (): string => {
    while (pos < buf.length && isWs(buf[pos])) pos++;
    let s = '';
    while (pos < buf.length && !isWs(buf[pos])) s += String.fromCharCode(buf[pos++]);
    return s;
  };
  const magic = token();
  if (magic !== 'P6') throw new Error(`Unexpected PPM magic: ${magic}`);
  const w = parseInt(token(), 10);
  const h = parseInt(token(), 10);
  token(); // maxval (255)
  pos++; // single whitespace separator before binary data
  return { w, h, pixels: buf.subarray(pos, pos + w * h * 3) };
}

function ppmToPng(ppm: Buffer): { png: Buffer; width: number; height: number } {
  const { w, h, pixels } = parsePPM(ppm);
  const stride = w * 3;
  const raw = Buffer.alloc((stride + 1) * h);
  for (let y = 0; y < h; y++) {
    raw[y * (stride + 1)] = 0; // filter type 0 (none)
    pixels.copy(raw, y * (stride + 1) + 1, y * stride, y * stride + stride);
  }
  const ihdr = Buffer.alloc(13);
  ihdr.writeUInt32BE(w, 0);
  ihdr.writeUInt32BE(h, 4);
  ihdr[8] = 8; // bit depth
  ihdr[9] = 2; // color type 2 = truecolor RGB
  const sig = Buffer.from([137, 80, 78, 71, 13, 10, 26, 10]);
  const png = Buffer.concat([
    sig,
    pngChunk('IHDR', ihdr),
    pngChunk('IDAT', zlib.deflateSync(raw, { level: 9 })),
    pngChunk('IEND', Buffer.alloc(0)),
  ]);
  return { png, width: w, height: h };
}

// --- build + run ------------------------------------------------------------
function mtime(p: string): number {
  try {
    return fs.statSync(p).mtimeMs;
  } catch {
    return -1;
  }
}

function needsCompile(srcDir: string, scale: number): boolean {
  const binM = mtime(binPath(scale));
  if (binM < 0) return true;
  const deps = [
    RENDER_SRC,
    path.join(srcDir, 'ipod_ui.c'),
    path.join(srcDir, 'ipod_ui.h'),
    path.join(srcDir, scale >= 2 ? 'font_ipod_2x.h' : 'font_ipod.h'),
  ];
  // Recompile if any dependency is newer (e.g. after a font swap) or missing.
  return deps.some((d) => {
    const m = mtime(d);
    return m < 0 || m > binM;
  });
}

function compile(srcDir: string, scale: number): void {
  const args = ['-O2', '-I', srcDir];
  if (scale >= 2) args.push(`-DUI_SCALE=${scale}`);
  args.push(RENDER_SRC, '-o', binPath(scale), '-lm');
  try {
    execFileSync('clang', args, { stdio: 'pipe' });
  } catch (e: any) {
    const detail = e?.stderr?.toString?.() || e?.message || String(e);
    throw new Error(`Preview build failed:\n${detail}`);
  }
}

const cache = new Map<string, { png: Buffer; w: number; h: number }>();
const key = (scale: number, name: string) => `${scale}:${name}`;

export interface PreviewResult {
  token: string;
  scale: number;
  screens: { name: string; label: string; width: number; height: number }[];
}

export function renderPreview(scale = 1): PreviewResult {
  if (scale !== 1 && scale !== 2) scale = 1;
  const srcDir = resolveFirmwareSrcDir();
  if (!srcDir || !fs.existsSync(path.join(srcDir, 'ipod_ui.c'))) {
    throw new Error(
      `Firmware source not found. Set PREVIEW_SRC_DIR, or write the path to your ` +
        `pockettunes source dir into ~/.pockettunes-sync/firmware-src-dir.txt ` +
        `(currently: ${srcDir || 'unset'}).`,
    );
  }
  if (scale >= 2 && !fs.existsSync(path.join(srcDir, 'font_ipod_2x.h'))) {
    throw new Error('font_ipod_2x.h not found in the firmware source (needed for the 640x480 preview).');
  }
  if (needsCompile(srcDir, scale)) compile(srcDir, scale);

  const dir = outDir(scale);
  fs.mkdirSync(dir, { recursive: true });
  try {
    execFileSync(binPath(scale), [dir], { stdio: 'pipe' });
  } catch (e: any) {
    throw new Error(`Preview render failed: ${e?.message || String(e)}`);
  }

  const screens: PreviewResult['screens'] = [];
  for (const s of SCREENS) {
    const ppmPath = path.join(dir, s.file);
    if (!fs.existsSync(ppmPath)) continue;
    const { png, width, height } = ppmToPng(fs.readFileSync(ppmPath));
    cache.set(key(scale, s.name), { png, w: width, h: height });
    screens.push({ name: s.name, label: s.label, width, height });
  }
  if (screens.length === 0) throw new Error('Preview produced no screens.');

  const token = `${scale}-${mtime(binPath(scale))}-${Date.now()}`;
  return { token, scale, screens };
}

export function getPreviewImage(scale: number, name: string): { png: Buffer; w: number; h: number } | null {
  return cache.get(key(scale, name)) ?? null;
}
