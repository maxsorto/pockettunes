import fs from 'node:fs';
import path from 'node:path';
import { run } from './proc.js';

export interface Volume {
  name: string;
  mountPath: string;
  fsType: string | null;
  totalBytes: number | null;
  freeBytes: number | null;
  /** A valid Analogue Pocket card: exFAT with Cores/ and Assets/ at root. */
  isPocket: boolean;
  /** Bonus signal — Analogue_Pocket.json present at root. */
  hasPocketJson: boolean;
  /** Whether Cores/ and Assets/ both exist (the core structural check). */
  hasCoreStructure: boolean;
}

/**
 * macOS-specific volume inspection via `diskutil info`. Wrapped so a
 * Linux/Windows fork can swap the implementation. Returns null fields when the
 * info isn't available rather than throwing.
 */
async function diskutilInfo(
  mountPath: string,
): Promise<{ fsType: string | null; totalBytes: number | null; freeBytes: number | null }> {
  try {
    const res = await run('diskutil', ['info', '-plist', mountPath], { timeoutMs: 8000 });
    if (res.code !== 0) return { fsType: null, totalBytes: null, freeBytes: null };
    // Parse the plist with simple key->value extraction (avoids a plist dep).
    const xml = res.stdout;
    const grabString = (key: string): string | null => {
      const re = new RegExp(`<key>${key}</key>\\s*<string>([^<]*)</string>`);
      const m = xml.match(re);
      return m ? m[1] : null;
    };
    const grabInt = (key: string): number | null => {
      const re = new RegExp(`<key>${key}</key>\\s*<integer>(\\d+)</integer>`);
      const m = xml.match(re);
      return m ? Number(m[1]) : null;
    };
    const fsType =
      grabString('FilesystemName') ?? grabString('FilesystemType') ?? grabString('FilesystemUserVisibleName');
    const totalBytes = grabInt('TotalSize') ?? grabInt('Size');
    const freeBytes = grabInt('FreeSpace') ?? grabInt('APFSContainerFree');
    return { fsType, totalBytes, freeBytes };
  } catch {
    return { fsType: null, totalBytes: null, freeBytes: null };
  }
}

function dirExists(p: string): boolean {
  try {
    return fs.statSync(p).isDirectory();
  } catch {
    return false;
  }
}

function fileExists(p: string): boolean {
  try {
    return fs.statSync(p).isFile();
  } catch {
    return false;
  }
}

/** Enumerate mounted volumes under /Volumes and classify each. */
export async function listVolumes(): Promise<Volume[]> {
  let names: string[] = [];
  try {
    names = fs.readdirSync('/Volumes');
  } catch {
    names = [];
  }

  const volumes: Volume[] = [];
  for (const name of names) {
    const mountPath = path.join('/Volumes', name);
    let realPath = mountPath;
    try {
      // "Macintosh HD" is a symlink to / on modern macOS; resolve & skip root.
      const st = fs.lstatSync(mountPath);
      if (st.isSymbolicLink()) {
        realPath = fs.realpathSync(mountPath);
        if (realPath === '/') continue;
      }
      if (!fs.statSync(mountPath).isDirectory()) continue;
    } catch {
      continue;
    }

    const hasCores = dirExists(path.join(mountPath, 'Cores'));
    const hasAssets = dirExists(path.join(mountPath, 'Assets'));
    const hasCoreStructure = hasCores && hasAssets;
    const hasPocketJson = fileExists(path.join(mountPath, 'Analogue_Pocket.json'));

    const info = await diskutilInfo(mountPath);
    const isExfat = (info.fsType ?? '').toLowerCase().includes('exfat');

    volumes.push({
      name,
      mountPath,
      fsType: info.fsType,
      totalBytes: info.totalBytes,
      freeBytes: info.freeBytes,
      hasCoreStructure,
      hasPocketJson,
      // A real Pocket card has the Cores/ + Assets/ layout AND is either exFAT
      // (how the Pocket formats its cards) or carries Analogue_Pocket.json. The
      // second clause stops some unrelated volume that merely happens to have
      // Cores/ and Assets/ folders from being mistaken for the Pocket.
      isPocket: hasCoreStructure && (isExfat || hasPocketJson),
    });
  }

  // Pocket cards first, then by name.
  volumes.sort((a, b) => {
    if (a.isPocket !== b.isPocket) return a.isPocket ? -1 : 1;
    return a.name.localeCompare(b.name);
  });
  return volumes;
}

/** Eject a volume by mount path (best-effort). */
export async function ejectVolume(mountPath: string): Promise<{ ok: boolean; message: string }> {
  const res = await run('diskutil', ['eject', mountPath], { timeoutMs: 30000 });
  return { ok: res.code === 0, message: (res.stdout + res.stderr).trim() };
}
