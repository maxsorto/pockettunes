import { useEffect, useMemo, useState } from 'react';
import {
  ejectVolume,
  health,
  scanStream,
  type LibraryScan,
  type LibraryTrack,
  type SyncTrackInput,
  type Volume,
} from './api';
import { useVolumes } from './useVolumes';
import { SyncModal } from './SyncModal';
import { CoreModal } from './CoreModal';
import { Studio } from './Studio';
import { fmtBytes, fmtDuration, groupBy } from './util';

type View = { kind: 'songs' } | { kind: 'artist'; name: string } | { kind: 'album'; artist: string; album: string };

export function App() {
  const [scan, setScan] = useState<LibraryScan | null>(null);
  const [libDir, setLibDir] = useState('');
  const [defaultLibDir, setDefaultLibDir] = useState('');
  const [defaultCoreDir, setDefaultCoreDir] = useState('');
  const [scanning, setScanning] = useState(false);
  const [scanPct, setScanPct] = useState(0);
  const [scanErr, setScanErr] = useState<string | null>(null);

  const [view, setView] = useState<View>({ kind: 'songs' });
  const [query, setQuery] = useState('');
  const [selected, setSelected] = useState<Set<string>>(new Set());

  const { volumes, refresh: refreshVolumes } = useVolumes();
  const [targetMount, setTargetMount] = useState<string | null>(null);
  const [showSync, setShowSync] = useState(false);
  const [showCore, setShowCore] = useState(false);
  const [tab, setTab] = useState<'library' | 'studio'>('library');

  // Boot: load defaults, then run an initial (cached or fresh) scan.
  useEffect(() => {
    (async () => {
      try {
        const h = await health();
        setDefaultLibDir(h.defaults.libraryDir);
        setDefaultCoreDir(h.defaults.coreBuildDir);
        setLibDir(h.defaults.libraryDir);
        await doScan(h.defaults.libraryDir);
      } catch (e: any) {
        setScanErr(e?.message ?? String(e));
      }
    })();
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  // Auto-pick the first detected Pocket volume as the sync target.
  useEffect(() => {
    if (targetMount && volumes.some((v) => v.mountPath === targetMount)) return;
    const pocket = volumes.find((v) => v.isPocket);
    setTargetMount(pocket ? pocket.mountPath : volumes[0]?.mountPath ?? null);
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [volumes]);

  async function doScan(dir: string) {
    setScanning(true);
    setScanErr(null);
    setScanPct(0);
    try {
      const result = await scanStream(dir, (done, total) => {
        setScanPct(total ? Math.round((done / total) * 100) : 0);
      });
      setScan(result);
    } catch (e: any) {
      setScanErr(e?.message ?? String(e));
    } finally {
      setScanning(false);
    }
  }

  const tracks = scan?.tracks ?? [];
  const syncable = useMemo(() => tracks.filter((t) => !t.drmOrUnreadable), [tracks]);

  const artists = useMemo(() => {
    const g = groupBy(syncable, (t) => t.artist || 'Unknown Artist');
    return [...g.keys()].sort((a, b) => a.localeCompare(b));
  }, [syncable]);

  // Tracks visible in the current view, filtered by the search query.
  const visible = useMemo(() => {
    let list = syncable;
    if (view.kind === 'artist') list = list.filter((t) => (t.artist || 'Unknown Artist') === view.name);
    else if (view.kind === 'album')
      list = list.filter((t) => t.artist === view.artist && t.album === view.album);
    if (query.trim()) {
      const q = query.toLowerCase();
      list = list.filter(
        (t) =>
          t.title.toLowerCase().includes(q) ||
          t.artist.toLowerCase().includes(q) ||
          t.album.toLowerCase().includes(q),
      );
    }
    return list;
  }, [syncable, view, query]);

  // Albums for the sidebar when an artist is selected.
  const albumsForArtist = useMemo(() => {
    if (view.kind === 'songs') return [];
    const artist = view.kind === 'artist' ? view.name : view.artist;
    const g = groupBy(
      syncable.filter((t) => (t.artist || 'Unknown Artist') === artist),
      (t) => t.album || 'Unknown Album',
    );
    return [...g.keys()].sort((a, b) => a.localeCompare(b));
  }, [syncable, view]);

  function toggle(id: string) {
    setSelected((prev) => {
      const next = new Set(prev);
      if (next.has(id)) next.delete(id);
      else next.add(id);
      return next;
    });
  }

  function setMany(ids: string[], on: boolean) {
    setSelected((prev) => {
      const next = new Set(prev);
      for (const id of ids) {
        if (on) next.add(id);
        else next.delete(id);
      }
      return next;
    });
  }

  const selectedTracks: LibraryTrack[] = useMemo(
    () => syncable.filter((t) => selected.has(t.id)),
    [syncable, selected],
  );
  const estBytes = useMemo(
    () => Math.round(selectedTracks.reduce((s, t) => s + (t.durationSeconds || 0) / 60, 0) * 2.4 * 1024 * 1024),
    [selectedTracks],
  );

  const targetVolume: Volume | null = volumes.find((v) => v.mountPath === targetMount) ?? null;

  const syncInputs: SyncTrackInput[] = selectedTracks.map((t) => ({
    path: t.path,
    title: t.title,
    artist: t.artist,
    album: t.album,
    durationSeconds: t.durationSeconds,
    hasArt: t.hasArt,
  }));

  const visibleIds = visible.map((t) => t.id);
  const allVisibleSelected = visibleIds.length > 0 && visibleIds.every((id) => selected.has(id));

  return (
    <div className="app">
      {/* Title bar */}
      <div className="titlebar">
        <div className="logo">♪</div>
        <h1>PocketTunes Sync</h1>
        <nav style={{ display: 'flex', gap: 6, marginLeft: 14 }}>
          {(['library', 'studio'] as const).map((t) => (
            <button
              key={t}
              onClick={() => setTab(t)}
              style={{
                textTransform: 'capitalize',
                padding: '4px 12px',
                borderRadius: 6,
                border: '1px solid var(--line)',
                cursor: 'pointer',
                background: tab === t ? '#2563eb' : 'transparent',
                color: tab === t ? '#fff' : 'inherit',
              }}
            >
              {t}
            </button>
          ))}
        </nav>
        <div className="spacer" />
        <SdStatus
          volumes={volumes}
          targetMount={targetMount}
          onPick={setTargetMount}
          target={targetVolume}
          onEjected={refreshVolumes}
        />
      </div>

      {tab === 'studio' ? (
        <Studio />
      ) : (
        <>
      <div className="main">
        {/* Sidebar */}
        <div className="sidebar">
          <div className="side-group">Library</div>
          <div
            className={`side-item ${view.kind === 'songs' ? 'active' : ''}`}
            onClick={() => setView({ kind: 'songs' })}
          >
            ♫ Songs <span className="count">{syncable.length}</span>
          </div>

          <div className="side-group">Artists</div>
          {artists.map((a) => (
            <div key={a}>
              <div
                className={`side-item ${
                  (view.kind === 'artist' && view.name === a) ||
                  (view.kind === 'album' && view.artist === a)
                    ? 'active'
                    : ''
                }`}
                onClick={() => setView({ kind: 'artist', name: a })}
                title={a}
              >
                {a}
                <span className="count">
                  {syncable.filter((t) => (t.artist || 'Unknown Artist') === a).length}
                </span>
              </div>
              {(view.kind === 'artist' && view.name === a) ||
              (view.kind === 'album' && view.artist === a)
                ? albumsForArtist.map((al) => (
                    <div
                      key={al}
                      className={`side-item ${
                        view.kind === 'album' && view.album === al ? 'active' : ''
                      }`}
                      style={{ paddingLeft: 36, fontSize: 12 }}
                      onClick={() => setView({ kind: 'album', artist: a, album: al })}
                      title={al}
                    >
                      ◇ {al}
                    </div>
                  ))
                : null}
            </div>
          ))}
        </div>

        {/* Content */}
        <div className="content">
          <div className="toolbar">
            <input
              type="text"
              style={{ minWidth: 280 }}
              value={libDir}
              onChange={(e) => setLibDir(e.target.value)}
              placeholder="Library folder"
            />
            <button onClick={() => doScan(libDir)} disabled={scanning}>
              {scanning ? 'Scanning…' : 'Scan'}
            </button>
            {libDir !== defaultLibDir && (
              <button className="linkish" onClick={() => setLibDir(defaultLibDir)}>
                reset to ~/Music
              </button>
            )}
            <div className="grow" />
            <input
              type="search"
              value={query}
              onChange={(e) => setQuery(e.target.value)}
              placeholder="Search"
            />
          </div>

          {scanning && (
            <div style={{ padding: '8px 16px' }}>
              <div className="progress">
                <div style={{ width: `${scanPct}%` }} />
              </div>
              <div style={{ fontSize: 12, color: 'var(--text-dim)', marginTop: 4 }}>
                Probing tracks… {scanPct}%
              </div>
            </div>
          )}

          {scanErr && (
            <div className="warn-box" style={{ margin: '10px 16px' }}>
              {scanErr}
            </div>
          )}

          {!scanning && scan && (
            <div className="table-wrap">
              {visible.length === 0 ? (
                <div className="empty">No songs in this view.</div>
              ) : (
                <table className="tracks">
                  <thead>
                    <tr>
                      <th className="check">
                        <input
                          type="checkbox"
                          checked={allVisibleSelected}
                          onChange={(e) => setMany(visibleIds, e.target.checked)}
                        />
                      </th>
                      <th className="num">#</th>
                      <th>Name</th>
                      <th>Artist</th>
                      <th>Album</th>
                      <th>Time</th>
                    </tr>
                  </thead>
                  <tbody>
                    {visible.map((t, i) => (
                      <tr key={t.id}>
                        <td className="check">
                          <input type="checkbox" checked={selected.has(t.id)} onChange={() => toggle(t.id)} />
                        </td>
                        <td className="num">{i + 1}</td>
                        <td title={t.title}>
                          <Thumb track={t} />
                          {t.title}
                          {!t.hasArt && <span className="badge">no art</span>}
                        </td>
                        <td title={t.artist}>{t.artist}</td>
                        <td title={t.album}>{t.album}</td>
                        <td>{fmtDuration(t.durationSeconds)}</td>
                      </tr>
                    ))}
                  </tbody>
                </table>
              )}
            </div>
          )}

          {!scan && !scanning && !scanErr && (
            <div className="empty">
              <span className="spinner" /> Loading library…
            </div>
          )}
        </div>
      </div>

      {/* Status bar */}
      <div className="statusbar">
        <span>
          {scan ? (
            <>
              {syncable.length} songs
              {scan.skippedCount > 0 && (
                <span className="badge drm" title="DRM / unreadable, excluded from sync">
                  {scan.skippedCount} skipped
                </span>
              )}
            </>
          ) : (
            '—'
          )}
        </span>
        <span>
          {selected.size} selected · {fmtBytes(estBytes)} est.
        </span>
        <div className="grow" />
        <button onClick={() => setMany(syncable.map((t) => t.id), true)} disabled={!scan}>
          Select all
        </button>
        <button onClick={() => setSelected(new Set())} disabled={selected.size === 0}>
          Clear
        </button>
        <button
          onClick={() => setShowCore(true)}
          disabled={!targetMount}
          title="Push the PocketTunes core to the card"
        >
          Update Core…
        </button>
        <button
          onClick={async () => {
            if (!targetMount) return;
            const r = await ejectVolume(targetMount).catch((e) => ({ ok: false, message: String(e) }));
            if (!r.ok) alert(`Eject failed: ${r.message}`);
            refreshVolumes();
          }}
          disabled={!targetMount}
          title="Safely eject the selected volume"
        >
          ⏏ Eject
        </button>
        <button className="primary" onClick={() => setShowSync(true)} disabled={selected.size === 0 || !targetMount}>
          Sync {selected.size} →
        </button>
      </div>
        </>
      )}

      {showSync && (
        <SyncModal
          tracks={syncInputs}
          estBytes={estBytes}
          target={targetMount!}
          volume={targetVolume}
          onClose={() => setShowSync(false)}
        />
      )}
      {showCore && (
        <CoreModal
          target={targetMount!}
          volume={targetVolume}
          defaultBuildDir={defaultCoreDir}
          onClose={() => setShowCore(false)}
        />
      )}
    </div>
  );
}

/**
 * Album-art thumbnail. Lazily loads the embedded cover from the backend
 * (/api/art) when the track reports art; falls back to the gray placeholder
 * box on missing art or load error.
 */
function Thumb({ track }: { track: LibraryTrack }) {
  const [failed, setFailed] = useState(false);
  if (!track.hasArt || failed) {
    return <span className="art-thumb" style={{ marginRight: 6 }} />;
  }
  return (
    <img
      className="art-thumb"
      style={{ marginRight: 6, objectFit: 'cover' }}
      loading="lazy"
      src={`/api/art?size=56&path=${encodeURIComponent(track.path)}`}
      onError={() => setFailed(true)}
      alt=""
    />
  );
}

function SdStatus({
  volumes,
  targetMount,
  onPick,
  target,
  onEjected,
}: {
  volumes: Volume[];
  targetMount: string | null;
  onPick: (m: string) => void;
  target: Volume | null;
  onEjected: () => void;
}) {
  const [open, setOpen] = useState(false);
  const [ejecting, setEjecting] = useState<string | null>(null);

  async function doEject(mountPath: string) {
    setEjecting(mountPath);
    try {
      const r = await ejectVolume(mountPath);
      if (!r.ok) alert(`Eject failed: ${r.message || 'unknown error'}`);
    } catch (e: any) {
      alert(`Eject failed: ${e?.message ?? e}`);
    } finally {
      setEjecting(null);
      setOpen(false);
      onEjected();
    }
  }
  const dotClass = !target ? 'gray' : target.isPocket ? 'green' : 'amber';
  const label = !target
    ? 'No volume'
    : target.isPocket
      ? `${target.name} · Pocket`
      : `${target.name} · not Pocket`;

  return (
    <div style={{ position: 'relative' }}>
      <div className="sd-pill" onClick={() => setOpen((o) => !o)} title="Choose target volume">
        <span className={`dot ${dotClass}`} />
        <span style={{ overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>{label}</span>
        {target && (
          <span style={{ color: 'var(--text-dim)' }}>
            {fmtBytes(target.freeBytes)} free / {fmtBytes(target.totalBytes)}
          </span>
        )}
        <span style={{ color: 'var(--text-dim)' }}>▾</span>
      </div>
      {open && (
        <div
          style={{
            position: 'absolute',
            right: 0,
            top: 32,
            background: '#fff',
            border: '1px solid var(--line)',
            borderRadius: 10,
            boxShadow: '0 8px 28px rgba(0,0,0,0.25)',
            width: 340,
            zIndex: 40,
            padding: 8,
          }}
        >
          <div style={{ fontSize: 11, color: 'var(--text-dim)', padding: '4px 8px' }}>
            Mounted volumes (writing over USB-SD is unreliable — use a card reader)
          </div>
          {volumes.length === 0 && (
            <div style={{ padding: 10, color: 'var(--text-dim)', fontSize: 12 }}>No removable volumes mounted.</div>
          )}
          {volumes.map((v) => (
            <div
              key={v.mountPath}
              onClick={() => {
                onPick(v.mountPath);
                setOpen(false);
              }}
              style={{
                display: 'flex',
                alignItems: 'center',
                gap: 8,
                padding: '7px 8px',
                borderRadius: 6,
                cursor: 'pointer',
                background: v.mountPath === targetMount ? 'var(--row-alt)' : 'transparent',
              }}
            >
              <span className={`dot ${v.isPocket ? 'green' : 'gray'}`} />
              <div style={{ flex: 1, minWidth: 0 }}>
                <div style={{ fontWeight: 600 }}>{v.name}</div>
                <div style={{ fontSize: 11, color: 'var(--text-dim)' }}>
                  {v.fsType ?? 'unknown fs'} · {fmtBytes(v.freeBytes)} free
                  {v.isPocket ? ' · valid Pocket format' : v.hasCoreStructure ? ' · has Cores/Assets' : ''}
                </div>
              </div>
              <button
                onClick={(e) => {
                  e.stopPropagation();
                  void doEject(v.mountPath);
                }}
                disabled={ejecting === v.mountPath}
                title="Eject this volume"
                style={{ fontSize: 12, padding: '3px 8px', whiteSpace: 'nowrap' }}
              >
                {ejecting === v.mountPath ? 'Ejecting…' : '⏏ Eject'}
              </button>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
