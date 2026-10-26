import path from 'node:path';
import { FFPROBE } from './config.js';
import { run } from './proc.js';

export interface TrackMeta {
  title: string;
  artist: string;
  album: string;
  trackNo: number | null;
  durationSeconds: number;
  hasArt: boolean;
  /** True when ffprobe could not read the file at all (e.g. DRM/FairPlay). */
  unreadable: boolean;
}

/**
 * Strip a leading track-number prefix from a filename-derived title.
 * Mirrors the reference playlist_meta.sh:
 *   sed -E 's/^[0-9]+([-_ ][0-9]+)?[ .._-]+//'
 * Handles "01 Title", "1-13 Title", "13. Title", "1_05_Title".
 */
export function stripTrackPrefix(base: string): string {
  const cleaned = base.replace(/^[0-9]+([-_ ][0-9]+)?[ ._-]+/, '');
  return cleaned.length > 0 ? cleaned : base;
}

/** Title derived purely from the filename (fallback when no tag). */
export function titleFromPath(filePath: string): string {
  const base = path.basename(filePath, path.extname(filePath));
  return stripTrackPrefix(base);
}

/** artist = parent-parent dir, album = parent dir (Apple Music layout). */
export function artistAlbumFromPath(filePath: string): { artist: string; album: string } {
  const dir = path.dirname(filePath);
  const album = path.basename(dir);
  const artist = path.basename(path.dirname(dir));
  return { artist, album };
}

function firstNonEmpty(...vals: (string | undefined | null)[]): string | undefined {
  for (const v of vals) {
    if (typeof v === 'string' && v.trim().length > 0) return v.trim();
  }
  return undefined;
}

/**
 * Probe a single audio file for tags + duration + whether it carries embedded
 * cover art. Prefers real tags (ffprobe) and falls back to folder-name
 * conventions, matching the reference scripts' artist=parent-parent /
 * album=parent / title=stripped-filename behaviour.
 *
 * DRM-protected (FairPlay) files make ffprobe exit non-zero; we flag those as
 * `unreadable` and let the caller skip them rather than crashing.
 */
export async function probeTrack(filePath: string): Promise<TrackMeta> {
  const folder = artistAlbumFromPath(filePath);
  const fileTitle = titleFromPath(filePath);

  const res = await run(FFPROBE, [
    '-v',
    'error',
    '-show_entries',
    // NOTE: disposition fields must be requested via `stream_disposition=`.
    // Folding them into `stream=...,disposition` yields an empty disposition.
    'format=duration:format_tags=title,artist,album,album_artist,track:stream=codec_type:stream_disposition=attached_pic',
    '-of',
    'json',
    filePath,
  ]);

  if (res.code !== 0) {
    return {
      title: fileTitle,
      artist: folder.artist,
      album: folder.album,
      trackNo: null,
      durationSeconds: 0,
      hasArt: false,
      unreadable: true,
    };
  }

  let parsed: any = {};
  try {
    parsed = JSON.parse(res.stdout);
  } catch {
    parsed = {};
  }

  const tags = parsed?.format?.tags ?? {};
  const streams: any[] = parsed?.streams ?? [];

  // Embedded art = a video stream flagged as an attached picture.
  const hasArt = streams.some(
    (s) => s?.codec_type === 'video' && s?.disposition?.attached_pic === 1,
  );

  const durRaw = Number(parsed?.format?.duration);
  const durationSeconds = Number.isFinite(durRaw) ? Math.round(durRaw) : 0;

  // track tag can be "5" or "5/12"
  let trackNo: number | null = null;
  const trackTag = firstNonEmpty(tags.track, tags.TRACK);
  if (trackTag) {
    const n = parseInt(trackTag.split('/')[0], 10);
    if (Number.isFinite(n)) trackNo = n;
  }

  return {
    title: firstNonEmpty(tags.title, tags.TITLE) ?? fileTitle,
    artist:
      firstNonEmpty(tags.artist, tags.ARTIST, tags.album_artist, tags.ALBUM_ARTIST) ??
      folder.artist,
    album: firstNonEmpty(tags.album, tags.ALBUM) ?? folder.album,
    trackNo,
    durationSeconds,
    hasArt,
    unreadable: false,
  };
}
