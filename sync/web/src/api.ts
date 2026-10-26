// Thin client over the Hono backend. In dev, Vite proxies /api -> :4321.

export interface LibraryTrack {
  id: string;
  path: string;
  title: string;
  artist: string;
  album: string;
  trackNo: number | null;
  durationSeconds: number;
  hasArt: boolean;
  drmOrUnreadable: boolean;
}

export interface LibraryScan {
  root: string;
  scannedAt: string;
  trackCount: number;
  skippedCount: number;
  tracks: LibraryTrack[];
  fromCache?: boolean;
}

export interface Volume {
  name: string;
  mountPath: string;
  fsType: string | null;
  totalBytes: number | null;
  freeBytes: number | null;
  isPocket: boolean;
  hasPocketJson: boolean;
  hasCoreStructure: boolean;
}

export interface CoreInfo {
  available: boolean;
  buildDir: string;
  version: string | null;
  author: string | null;
  shortname: string | null;
  dateRelease: string | null;
  topLevelDirs: string[];
  cardVersion: string | null;
}

async function json<T>(res: Response): Promise<T> {
  if (!res.ok) {
    const body = await res.json().catch(() => ({}));
    throw new Error((body as any).error || `${res.status} ${res.statusText}`);
  }
  return res.json() as Promise<T>;
}

export async function health() {
  return json<{ ok: boolean; defaults: { libraryDir: string; coreBuildDir: string } }>(
    await fetch('/api/health'),
  );
}

export async function scan(dir?: string, force = false): Promise<LibraryScan> {
  const q = new URLSearchParams();
  if (dir) q.set('dir', dir);
  if (force) q.set('force', '1');
  return json<LibraryScan>(await fetch(`/api/scan?${q.toString()}`));
}

/** Streaming scan via SSE; calls onProgress and resolves with the final scan. */
export function scanStream(
  dir: string | undefined,
  onProgress: (done: number, total: number) => void,
): Promise<LibraryScan> {
  return new Promise((resolve, reject) => {
    const q = new URLSearchParams();
    if (dir) q.set('dir', dir);
    const es = new EventSource(`/api/scan/stream?${q.toString()}`);
    es.addEventListener('progress', (e) => {
      const d = JSON.parse((e as MessageEvent).data);
      onProgress(d.done, d.total);
    });
    es.addEventListener('done', (e) => {
      es.close();
      resolve(JSON.parse((e as MessageEvent).data));
    });
    es.onerror = () => {
      es.close();
      reject(new Error('Scan stream failed'));
    };
  });
}

export async function listVolumes(): Promise<Volume[]> {
  const r = await json<{ volumes: Volume[] }>(await fetch('/api/volumes'));
  return r.volumes;
}

export async function ejectVolume(mountPath: string): Promise<{ ok: boolean; message: string }> {
  return json(
    await fetch('/api/eject', {
      method: 'POST',
      headers: { 'content-type': 'application/json' },
      body: JSON.stringify({ mountPath }),
    }),
  );
}

export async function estimate(tracks: { durationSeconds: number }[]): Promise<number> {
  const r = await json<{ bytes: number }>(
    await fetch('/api/estimate', {
      method: 'POST',
      headers: { 'content-type': 'application/json' },
      body: JSON.stringify({ tracks }),
    }),
  );
  return r.bytes;
}

export interface SyncTrackInput {
  path: string;
  title: string;
  artist: string;
  album: string;
  durationSeconds: number;
  hasArt: boolean;
}

export async function startSync(tracks: SyncTrackInput[], target: string, eject: boolean): Promise<string> {
  const r = await json<{ jobId: string }>(
    await fetch('/api/sync', {
      method: 'POST',
      headers: { 'content-type': 'application/json' },
      body: JSON.stringify({ tracks, target, eject }),
    }),
  );
  return r.jobId;
}

export async function getCore(buildDir?: string, card?: string): Promise<CoreInfo> {
  const q = new URLSearchParams();
  if (buildDir) q.set('dir', buildDir);
  if (card) q.set('card', card);
  return json<CoreInfo>(await fetch(`/api/core?${q.toString()}`));
}

export async function startCoreUpdate(target: string, buildDir?: string): Promise<string> {
  const r = await json<{ jobId: string }>(
    await fetch('/api/core/update', {
      method: 'POST',
      headers: { 'content-type': 'application/json' },
      body: JSON.stringify({ target, buildDir }),
    }),
  );
  return r.jobId;
}

export interface PreviewScreen {
  name: string;
  label: string;
  width: number;
  height: number;
}

/** Render the on-device UI screens at the given scale (1 = 320x240, 2 = 640x480). */
export async function renderPreview(
  scale = 1,
): Promise<{ token: string; scale: number; screens: PreviewScreen[] }> {
  return json(await fetch(`/api/preview/render?scale=${scale}`));
}

/** URL for a rendered screen PNG. The token busts the browser cache per render. */
export function previewImageUrl(name: string, token: string, scale = 1): string {
  return `/api/preview/image/${encodeURIComponent(name)}?scale=${scale}&v=${encodeURIComponent(token)}`;
}

/** Subscribe to a job SSE stream (sync or core). Resolves on end. */
export function subscribeJob(
  path: string,
  onMsg: (e: any) => void,
): Promise<void> {
  return new Promise((resolve, reject) => {
    const es = new EventSource(path);
    es.addEventListener('msg', (e) => {
      try {
        onMsg(JSON.parse((e as MessageEvent).data));
      } catch {
        /* ignore */
      }
    });
    es.addEventListener('end', () => {
      es.close();
      resolve();
    });
    es.onerror = () => {
      es.close();
      reject(new Error('Stream error'));
    };
  });
}
