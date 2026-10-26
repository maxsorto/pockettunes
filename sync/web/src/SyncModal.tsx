import { useEffect, useRef, useState } from 'react';
import { startSync, subscribeJob, type SyncTrackInput, type Volume } from './api';
import { fmtBytes } from './util';

interface LogLine {
  cls?: string;
  text: string;
}

export function SyncModal({
  tracks,
  estBytes,
  target,
  volume,
  onClose,
}: {
  tracks: SyncTrackInput[];
  estBytes: number;
  target: string;
  volume: Volume | null;
  onClose: () => void;
}) {
  const [phase, setPhase] = useState<'confirm' | 'running' | 'done' | 'error'>('confirm');
  const [pct, setPct] = useState(0);
  const [lines, setLines] = useState<LogLine[]>([]);
  const [summary, setSummary] = useState<{ written: number; failed: number; isoBytes: number } | null>(null);
  const [eject, setEject] = useState(false);
  const logRef = useRef<HTMLDivElement>(null);

  function log(text: string, cls?: string) {
    setLines((l) => [...l, { text, cls }]);
  }

  useEffect(() => {
    logRef.current?.scrollTo(0, logRef.current.scrollHeight);
  }, [lines]);

  const freeOk = volume?.freeBytes == null || volume.freeBytes > estBytes;

  async function go() {
    setPhase('running');
    try {
      const jobId = await startSync(tracks, target, eject);
      await subscribeJob(`/api/sync/${jobId}/stream`, (e) => {
        switch (e.type) {
          case 'start':
            log(`Starting sync of ${e.total} tracks`, 'phase');
            break;
          case 'phase':
            log(`▸ ${e.message}`, 'phase');
            break;
          case 'track':
            if (e.status === 'ok') log(`  ✓ ${String(e.index).padStart(4, '0')}  ${e.title}`, 'ok');
            else log(`  ✗ ${e.title} — ${e.reason ?? 'failed'}`, 'fail');
            break;
          case 'progress':
            setPct(e.pct);
            break;
          case 'log':
            log(`  ${e.message}`);
            break;
          case 'done':
            setSummary({ written: e.written, failed: e.failed, isoBytes: e.isoBytes });
            log(`Done. Wrote ${e.written} track(s), ${e.failed} failed. ISO ${fmtBytes(e.isoBytes)}.`, 'phase');
            setPhase('done');
            break;
          case 'error':
            log(`ERROR: ${e.message}`, 'fail');
            setPhase('error');
            break;
        }
      });
    } catch (err: any) {
      log(`ERROR: ${err?.message ?? err}`, 'fail');
      setPhase('error');
    }
  }

  return (
    <div className="modal-backdrop" onClick={phase === 'confirm' ? onClose : undefined}>
      <div className="modal" onClick={(e) => e.stopPropagation()}>
        <header>Sync to Analogue Pocket</header>
        <div className="body">
          {phase === 'confirm' && (
            <>
              <dl className="kv">
                <dt>Tracks</dt>
                <dd>{tracks.length}</dd>
                <dt>Estimated size</dt>
                <dd>
                  {fmtBytes(estBytes)}
                  {!freeOk && (
                    <span style={{ color: 'var(--red)' }}> — exceeds free space ({fmtBytes(volume?.freeBytes)})</span>
                  )}
                </dd>
                <dt>Target volume</dt>
                <dd>
                  {volume ? `${volume.name} (${volume.mountPath})` : target}
                  {volume && !volume.isPocket && (
                    <span style={{ color: 'var(--amber)' }}> — not detected as a Pocket card</span>
                  )}
                </dd>
                <dt>Writes to</dt>
                <dd>
                  {target}/Assets/pockettunes/common/music.iso
                </dd>
              </dl>
              <p style={{ fontSize: 12, color: 'var(--text-dim)', marginTop: 14 }}>
                Tracks will be transcoded to 48kHz / stereo / 320 kbps MP3, loudness-normalized, numbered in the
                current library order, packed with 200×200 RGB565 album art into a single ISO, and written to the card.
              </p>
              <label style={{ display: 'flex', gap: 8, alignItems: 'center', marginTop: 8, fontSize: 12.5 }}>
                <input type="checkbox" checked={eject} onChange={(e) => setEject(e.target.checked)} />
                Eject the volume when finished
              </label>
            </>
          )}

          {phase !== 'confirm' && (
            <>
              <div className="progress">
                <div style={{ width: `${pct}%` }} />
              </div>
              <div style={{ fontSize: 12, color: 'var(--text-dim)', marginTop: 6 }}>
                {phase === 'running' ? `${pct}%` : phase === 'done' ? 'Complete' : 'Stopped'}
                {summary && ` — ${summary.written} ok, ${summary.failed} failed`}
              </div>
              <div className="log" ref={logRef}>
                {lines.map((l, i) => (
                  <div key={i} className={l.cls}>
                    {l.text}
                  </div>
                ))}
              </div>
            </>
          )}
        </div>
        <footer>
          {phase === 'confirm' && (
            <>
              <button onClick={onClose}>Cancel</button>
              <button className="primary" onClick={go} disabled={tracks.length === 0}>
                Start Sync
              </button>
            </>
          )}
          {phase === 'running' && <button disabled>Syncing…</button>}
          {(phase === 'done' || phase === 'error') && (
            <button className="primary" onClick={onClose}>
              Close
            </button>
          )}
        </footer>
      </div>
    </div>
  );
}
