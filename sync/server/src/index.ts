import { serve } from '@hono/node-server';
import { Hono } from 'hono';
import { cors } from 'hono/cors';
import { streamSSE } from 'hono/streaming';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { EventEmitter } from 'node:events';
import {
  PORT,
  DEFAULT_LIBRARY_DIR,
  DEFAULT_CORE_BUILD_DIR,
  ensureDirs,
} from './config.js';
import { scanLibrary, readCachedScan } from './library.js';
import { listVolumes, ejectVolume } from './volumes.js';
import { startSync, getJob, estimateSizeBytes, type SyncEvent } from './sync.js';
import {
  inspectCore,
  readCardCoreVersion,
  startCoreUpdate,
  getCoreJob,
  type CoreUpdateEvent,
} from './core.js';
import { renderPreview, getPreviewImage } from './preview.js';

ensureDirs();

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const WEB_DIST = path.resolve(__dirname, '../../web/dist');
const isProd = process.env.NODE_ENV === 'production';

const app = new Hono();
app.use('/api/*', cors());

// --- Health & defaults -----------------------------------------------------
app.get('/api/health', (c) =>
  c.json({
    ok: true,
    defaults: {
      libraryDir: DEFAULT_LIBRARY_DIR,
      coreBuildDir: DEFAULT_CORE_BUILD_DIR,
    },
  }),
);

// --- Library scan ----------------------------------------------------------
app.get('/api/scan', async (c) => {
  const root = c.req.query('dir') || DEFAULT_LIBRARY_DIR;
  const force = c.req.query('force') === '1';
  if (!fs.existsSync(root)) return c.json({ error: `Folder not found: ${root}` }, 400);
  if (!force) {
    const cached = readCachedScan(root);
    if (cached) return c.json({ ...cached, fromCache: true });
  }
  const scan = await scanLibrary(root);
  return c.json({ ...scan, fromCache: false });
});

// Streaming scan with progress (SSE).
app.get('/api/scan/stream', async (c) => {
  const root = c.req.query('dir') || DEFAULT_LIBRARY_DIR;
  if (!fs.existsSync(root)) return c.json({ error: `Folder not found: ${root}` }, 400);
  return streamSSE(c, async (stream) => {
    const scan = await scanLibrary(root, (done, total) => {
      void stream.writeSSE({
        event: 'progress',
        data: JSON.stringify({ done, total, pct: Math.round((done / Math.max(1, total)) * 100) }),
      });
    });
    await stream.writeSSE({ event: 'done', data: JSON.stringify(scan) });
  });
});

// --- Album art thumbnail (UI preview) --------------------------------------
app.get('/api/art', async (c) => {
  const p = c.req.query('path');
  if (!p) return c.json({ error: 'Missing path' }, 400);
  if (!fs.existsSync(p)) return c.json({ error: 'Not found' }, 404);
  const sizeRaw = Number(c.req.query('size'));
  const size = Number.isFinite(sizeRaw) ? Math.min(300, Math.max(32, sizeRaw)) : 80;
  const { getThumbnail } = await import('./art.js');
  const buf = await getThumbnail(p, size);
  if (!buf) return c.body(null, 204); // no embedded art
  return new Response(buf, {
    headers: { 'content-type': 'image/jpeg', 'cache-control': 'public, max-age=86400' },
  });
});

// --- Volumes ---------------------------------------------------------------
app.get('/api/volumes', async (c) => {
  const volumes = await listVolumes();
  return c.json({ volumes });
});

app.post('/api/eject', async (c) => {
  const body = await c.req.json<{ mountPath?: string }>();
  if (!body?.mountPath) return c.json({ error: 'Missing mountPath' }, 400);
  return c.json(await ejectVolume(body.mountPath));
});

// --- Size estimate ---------------------------------------------------------
app.post('/api/estimate', async (c) => {
  const body = await c.req.json<{ tracks: { durationSeconds: number }[] }>();
  const bytes = estimateSizeBytes(body.tracks ?? []);
  return c.json({ bytes });
});

// --- Sync ------------------------------------------------------------------
app.post('/api/sync', async (c) => {
  const body = await c.req.json();
  if (!body?.target) return c.json({ error: 'Missing target' }, 400);
  if (!Array.isArray(body?.tracks) || body.tracks.length === 0)
    return c.json({ error: 'No tracks selected' }, 400);
  const job = startSync({ tracks: body.tracks, target: body.target, eject: !!body.eject });
  return c.json({ jobId: job.id });
});

app.get('/api/sync/:id/stream', async (c) => {
  const id = c.req.param('id');
  const job = getJob(id);
  if (!job) return c.json({ error: 'Unknown job' }, 404);
  return streamGenericSSE(c, job.emitter, job.events, () => job.status !== 'running');
});

// --- Core / firmware update ------------------------------------------------
app.get('/api/core', (c) => {
  const dir = c.req.query('dir') || undefined;
  const card = c.req.query('card') || undefined;
  const info = inspectCore(dir);
  const cardVersion = card ? readCardCoreVersion(card) : null;
  return c.json({ ...info, cardVersion });
});

app.post('/api/core/update', async (c) => {
  const body = await c.req.json<{ buildDir?: string; target: string }>();
  if (!body?.target) return c.json({ error: 'Missing target' }, 400);
  const buildDir = body.buildDir || DEFAULT_CORE_BUILD_DIR;
  const job = startCoreUpdate(buildDir, body.target);
  return c.json({ jobId: job.id });
});

app.get('/api/core/update/:id/stream', async (c) => {
  const id = c.req.param('id');
  const job = getCoreJob(id);
  if (!job) return c.json({ error: 'Unknown job' }, 404);
  return streamGenericSSE(c, job.emitter, job.events, () => job.status !== 'running');
});

// --- Studio: device UI previews --------------------------------------------
// Renders the on-device screens with the real firmware renderer and serves
// them as PNGs so the UI can be iterated on without flashing hardware.
app.get('/api/preview/render', (c) => {
  try {
    const scale = Number(c.req.query('scale')) || 1;
    return c.json(renderPreview(scale));
  } catch (e: any) {
    return c.json({ error: e?.message ?? String(e) }, 500);
  }
});

app.get('/api/preview/image/:name', (c) => {
  const scale = Number(c.req.query('scale')) || 1;
  const img = getPreviewImage(scale, c.req.param('name'));
  if (!img) return c.json({ error: 'Not rendered yet' }, 404);
  return new Response(img.png, {
    headers: { 'content-type': 'image/png', 'cache-control': 'no-store' },
  });
});

// --- Static frontend (production) ------------------------------------------
// Served directly from WEB_DIST (cwd-independent) with correct content types,
// plus an SPA fallback to index.html for unknown non-API routes.
const CONTENT_TYPES: Record<string, string> = {
  '.html': 'text/html; charset=utf-8',
  '.js': 'text/javascript; charset=utf-8',
  '.mjs': 'text/javascript; charset=utf-8',
  '.css': 'text/css; charset=utf-8',
  '.json': 'application/json; charset=utf-8',
  '.svg': 'image/svg+xml',
  '.png': 'image/png',
  '.jpg': 'image/jpeg',
  '.ico': 'image/x-icon',
  '.woff2': 'font/woff2',
  '.map': 'application/json; charset=utf-8',
};

if (isProd && fs.existsSync(WEB_DIST)) {
  app.get('*', async (c) => {
    if (c.req.path.startsWith('/api/')) return c.notFound();
    // Resolve the requested file inside WEB_DIST, guarding against traversal.
    const rel = decodeURIComponent(c.req.path.replace(/^\/+/, '')) || 'index.html';
    const candidate = path.resolve(WEB_DIST, rel);
    if (candidate.startsWith(WEB_DIST) && fs.existsSync(candidate) && fs.statSync(candidate).isFile()) {
      const ext = path.extname(candidate).toLowerCase();
      return new Response(fs.readFileSync(candidate), {
        headers: { 'content-type': CONTENT_TYPES[ext] ?? 'application/octet-stream' },
      });
    }
    // SPA fallback.
    const index = path.join(WEB_DIST, 'index.html');
    if (fs.existsSync(index)) return c.html(fs.readFileSync(index, 'utf8'));
    return c.text('Frontend not built. Run `npm run build`.', 404);
  });
}

/**
 * Generic SSE bridge: replay buffered events, then stream new ones until the
 * `isDone` predicate is satisfied. Used by both sync and core-update jobs.
 */
async function streamGenericSSE(
  c: any,
  emitter: EventEmitter,
  buffered: (SyncEvent | CoreUpdateEvent)[],
  isDone: () => boolean,
) {
  return streamSSE(c, async (stream) => {
    const seen = new Set<unknown>();
    for (const e of buffered) {
      seen.add(e);
      await stream.writeSSE({ event: 'msg', data: JSON.stringify(e) });
    }
    if (isDone()) {
      await stream.writeSSE({ event: 'end', data: '{}' });
      return;
    }
    await new Promise<void>((resolve) => {
      const onEvent = async (e: unknown) => {
        if (seen.has(e)) return;
        await stream.writeSSE({ event: 'msg', data: JSON.stringify(e) });
        const t = (e as { type?: string })?.type;
        if (t === 'done' || t === 'error') {
          emitter.off('event', onEvent);
          await stream.writeSSE({ event: 'end', data: '{}' });
          resolve();
        }
      };
      emitter.on('event', onEvent);
    });
  });
}

serve({ fetch: app.fetch, port: PORT }, (info) => {
  const url = `http://localhost:${info.port}`;
  console.log(`\n  PocketTunes Sync backend listening on ${url}`);
  if (isProd) {
    console.log(`  Open ${url} in your browser.\n`);
    // Auto-open the browser in production single-command start.
    import('node:child_process').then(({ spawn }) => {
      spawn('open', [url], { stdio: 'ignore', detached: true }).unref();
    });
  } else {
    console.log(`  (dev) Vite UI runs separately on http://localhost:5173\n`);
  }
});
