# PocketTunes Sync

A Mac-first companion app (iTunes-style) that loads your music library and syncs
selected tracks to an **Analogue Pocket** SD card for the **PocketTunes** openFPGA
music-player core.

It is a local web app: a **Hono (Node) backend** that does all the filesystem work
and shells out to `ffmpeg` / `ffprobe` / `hdiutil` / `diskutil`, and a **Vite + React +
TypeScript** frontend that talks to it over `localhost` HTTP (with SSE for live
progress). A pure browser app can't touch the filesystem, ffmpeg, or the SD card —
hence the local backend.

## Prerequisites

- **macOS** (uses `diskutil` / `hdiutil`; see "Cross-platform" below).
- **Node 18+** and npm. Install with `brew install node` if missing.
- **ffmpeg** and **ffprobe** on `PATH` (Homebrew installs them to `/opt/homebrew/bin`).
  Install with `brew install ffmpeg`. The backend prepends the common Homebrew bin dirs
  to its child-process `PATH`, and you can override the binaries with `FFMPEG_PATH` /
  `FFPROBE_PATH`.
- `hdiutil` and `diskutil` ship with macOS.

## Quick start

```bash
cd pockettunes/sync
npm install
npm start            # builds the UI, starts the backend, opens the browser
```

`npm start` serves the built UI and the API from a single port
(`http://localhost:4380` by default) and opens it in your browser.

### Development (hot reload)

```bash
npm run dev          # backend on :4380 + Vite UI on :5173 (Vite proxies /api)
```

Open http://localhost:5173. The backend port is 4380 to avoid colliding with other
local dev servers (Astro defaults to 4321). Override with `PORT=...`.

## What it does

1. **Library picker / scan.** Choose a source folder (default `~/Music`, which holds
   Apple Music under `~/Music/Music/Media.localized/Music/<Artist>/<Album>/<track>`).
   The backend recursively scans for `.m4a .mp3 .flac .aac .wav .alac`, runs `ffprobe`
   on each for title / artist / album / track# / duration and whether it carries
   embedded cover art. DRM-protected (FairPlay) files make ffprobe fail — they are
   flagged and skipped rather than crashing. Scans are cached on disk per source folder.
2. **iTunes-style browser & selection.** Browse by Artists → Albums, plus an all-Songs
   view, with album-art thumbnails and checkboxes to pick what to sync. The status bar
   shows the selected count and an estimated output size (~2 MB/min at 256 kbps).
3. **Sync.** Transcodes the selected tracks + art into a staging dir, generates
   `playlist.tsv`, builds the ISO, and writes it to the card with live per-track
   progress over SSE. Tracks are numbered `0001..` in the current library order.
4. **Core / firmware update.** Detects the PocketTunes core build (reads `version` from
   `core.json`), shows current-on-card vs available, and pushes the core tree
   (`Cores/`, `Assets/`, `Platforms/`) to the card. **Never overwrites the card's
   `music.iso`.**

## The exact on-device format it produces

The Pocket core mounts **one ISO** and reads files from it. The app builds that ISO and
writes it to:

```
<SDCARD>/Assets/pockettunes/common/music.iso
```

ISO contents (flat root, Joliet, volume name `MUSIC`):

- `0001.mp3`, `0002.mp3`, … — tracks, **MP3 48 kHz / stereo / 256 kbps**, 4-digit
  sequential. Numbering / order defines library order.
- `playlist.tsv` — one line per track, **TAB-separated, exactly 5 columns**:
  `filename<TAB>title<TAB>artist<TAB>album<TAB>durationSeconds`
  (e.g. `0002.mp3\tFeds Watching\t2 Chainz\tFeds Watching - Single\t250`).
- `art/0001.bin`, `art/0002.bin`, … — album art, **100×100, raw RGB565 little-endian,
  exactly 20000 bytes** (no header). Mapped by stem: `0001.mp3` → `art/0001.bin`.
- `art/placeholder.bin` — same format, a gray placeholder, used when a track has no
  embedded art.

Pipeline commands (matching the reference shell scripts; `-nostdin` is mandatory so
ffmpeg never consumes the parent's stdin):

- transcode: `ffmpeg -nostdin -y -i IN -map_metadata -1 -vn -ar 48000 -ac 2 -c:a libmp3lame -b:a 256k OUT.mp3`
- art: extract embedded cover then `ffmpeg -nostdin -y -i cover.png -vf scale=100:100 -pix_fmt rgb565le -f rawvideo OUT.bin`
  (`rgb565le` — little-endian, verified correct for the device; **not** `rgb565be`)
- ISO: `hdiutil makehybrid -o music.iso -iso -joliet -default-volume-name MUSIC <stage>`

Metadata prefers real tags from `ffprobe`; it falls back to folder conventions
(artist = parent-parent dir, album = parent dir, title = filename with a leading
track-number prefix stripped, e.g. `01 ` / `1-13 ` / `13. `).

## SD card detection & validation

The backend enumerates mounted volumes under `/Volumes`, uses `diskutil info` for
filesystem type / total / free space, and classifies a volume as a valid Analogue Pocket
card when it is **exFAT** and contains both `Cores/` and `Assets/` at its root
(`Analogue_Pocket.json` is a bonus signal). The UI polls for insert/remove and shows
detected / not-detected, volume name, total/free space, and the validity check. The
current test card mounts as `/Volumes/Untitled`.

> **Warning:** writing large files over the Pocket's USB-SD-Access mode is unreliable.
> Use a physical card reader. The app writes to the mounted volume either way.

## Configuration

- `PORT` — backend port (default `4380`).
- `FFMPEG_PATH` / `FFPROBE_PATH` — override tool locations.
- `CORE_BUILD_DIR` — default "core build directory" for the core-update feature. If
  unset, falls back to the openfpgaSDK build output if present on this machine. You can
  also set it per-update in the UI.
- `BACKEND_URL` — (dev only) where Vite proxies `/api` (default `http://localhost:4380`).

## API (backend routes)

- `GET  /api/health` — ok + default library/core dirs.
- `GET  /api/scan?dir=&force=` — scan a folder (cached). `force=1` re-probes.
- `GET  /api/scan/stream?dir=` — SSE: scan progress, then the full result.
- `GET  /api/art?path=&size=` — JPEG thumbnail of a track's embedded cover (UI preview).
- `GET  /api/volumes` — mounted volumes with Pocket classification.
- `POST /api/estimate` — estimated output bytes for a track selection.
- `POST /api/sync` → `{ jobId }`; `GET /api/sync/:id/stream` — SSE sync progress.
- `GET  /api/core?dir=&card=` — core build info + version-on-card.
- `POST /api/core/update` → `{ jobId }`; `GET /api/core/update/:id/stream` — SSE.

## Project layout

```
pockettunes-sync/
  server/   Hono backend (TypeScript, tsx)
    src/
      index.ts       routes + SSE bridge + static serving
      config.ts      paths, ports, tool locations, on-device layout constants
      proc.ts        spawn wrapper (stdin closed; Homebrew on PATH)
      metadata.ts    ffprobe tag/duration/art-detection + title cleaning
      library.ts     recursive scan + concurrency + disk cache
      volumes.ts     /Volumes enumeration + diskutil info + Pocket detection
      art.ts         RGB565 art + gray placeholder + UI JPEG thumbnails
      transcode.ts   ffmpeg transcode + hdiutil makehybrid
      sync.ts        the full sync pipeline as a progress-emitting job
      core.ts        core-build inspection + push (preserves music.iso)
  web/      Vite + React + TypeScript UI
    src/
      App.tsx        iTunes-style browser, selection, status bar
      SyncModal.tsx  confirm + live sync log
      CoreModal.tsx  core update + version compare + live log
      SdStatus       target-volume picker (in App.tsx)
      api.ts         typed fetch/SSE client
```

## Known limitations / what's stubbed

- **macOS only** in practice. `diskutil`/`hdiutil` calls are isolated in `volumes.ts`
  and `transcode.ts` so a Linux/Windows fork can swap them (e.g. `lsblk` + `genisoimage`/
  `mkisofs`), but no effort was spent making that work now.
- **Sync writes to whatever target you point at** — a real card mount or any folder
  (handy for testing). It does not require a physical card to develop.
- **Core update** copies from a local "core build directory"; it does not download
  releases from the internet. Version comparison is a plain string compare of
  `core.json`'s `metadata.version`.
- **FairPlay/DRM** tracks are detected and skipped, not converted (there is no legal way
  to transcode them).
- Verified end-to-end on this Mac: 368-track `~/Music` scan, a real 3-track sync whose
  ISO was mounted and confirmed to contain 48k/stereo/256k MP3s, a 5-column
  `playlist.tsv`, and exactly-20000-byte RGB565 art (with placeholder fallback), plus a
  core push to a fake card that left an existing `music.iso` byte-for-byte intact, and
  exFAT Pocket-card detection against a real mounted image named `Untitled`.
```
