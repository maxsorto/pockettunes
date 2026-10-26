import { useEffect, useRef, useState } from 'react';
import { getCore, startCoreUpdate, subscribeJob, type CoreInfo, type Volume } from './api';

interface LogLine {
  cls?: string;
  text: string;
}

export function CoreModal({
  target,
  volume,
  defaultBuildDir,
  onClose,
}: {
  target: string;
  volume: Volume | null;
  defaultBuildDir: string;
  onClose: () => void;
}) {
  const [buildDir, setBuildDir] = useState(defaultBuildDir);
  const [info, setInfo] = useState<CoreInfo | null>(null);
  const [phase, setPhase] = useState<'confirm' | 'running' | 'done' | 'error'>('confirm');
  const [lines, setLines] = useState<LogLine[]>([]);
  const logRef = useRef<HTMLDivElement>(null);

  function log(text: string, cls?: string) {
    setLines((l) => [...l, { text, cls }]);
  }

  async function refreshInfo(dir: string) {
    try {
      const i = await getCore(dir || undefined, target);
      setInfo(i);
    } catch {
      setInfo(null);
    }
  }

  useEffect(() => {
    void refreshInfo(buildDir);
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  useEffect(() => {
    logRef.current?.scrollTo(0, logRef.current.scrollHeight);
  }, [lines]);

  async function go() {
    setPhase('running');
    try {
      const jobId = await startCoreUpdate(target, buildDir || undefined);
      await subscribeJob(`/api/core/update/${jobId}/stream`, (e) => {
        switch (e.type) {
          case 'start':
            log(`Pushing core from ${e.buildDir}`, 'phase');
            log(`to ${e.target}`, 'phase');
            break;
          case 'file':
            log(`  ${e.rel}`, 'ok');
            break;
          case 'log':
            log(`  ${e.message}`);
            break;
          case 'done':
            log(`Done. Copied ${e.files} file(s). Library ISO preserved.`, 'phase');
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

  const sameVersion = info?.version && info?.cardVersion && info.version === info.cardVersion;

  return (
    <div className="modal-backdrop" onClick={phase === 'confirm' ? onClose : undefined}>
      <div className="modal" onClick={(e) => e.stopPropagation()}>
        <header>Update PocketTunes Core</header>
        <div className="body">
          {phase === 'confirm' && (
            <>
              <dl className="kv">
                <dt>Target card</dt>
                <dd>{volume ? `${volume.name} (${target})` : target}</dd>
                <dt>Available version</dt>
                <dd>{info?.available ? info.version ?? '(no version string)' : 'core build not found'}</dd>
                <dt>On card now</dt>
                <dd>{info?.cardVersion ?? '— (none / unknown)'}</dd>
                <dt>Author</dt>
                <dd>{info?.author ?? '—'}</dd>
                <dt>Will copy</dt>
                <dd>{info?.topLevelDirs?.length ? info.topLevelDirs.join(', ') : '—'}</dd>
              </dl>

              <label style={{ display: 'block', marginTop: 12, fontSize: 12, color: 'var(--text-dim)' }}>
                Core build directory
              </label>
              <div style={{ display: 'flex', gap: 8, marginTop: 4 }}>
                <input
                  type="text"
                  style={{ flex: 1 }}
                  value={buildDir}
                  onChange={(e) => setBuildDir(e.target.value)}
                  onBlur={() => refreshInfo(buildDir)}
                  placeholder="/path/to/pockettunes core build"
                />
                <button onClick={() => refreshInfo(buildDir)}>Check</button>
              </div>

              {sameVersion && (
                <p style={{ color: 'var(--amber)', fontSize: 12, marginTop: 12 }}>
                  The card already has version {info?.cardVersion}. Updating will re-copy the same files.
                </p>
              )}
              <p style={{ fontSize: 12, color: 'var(--text-dim)', marginTop: 12 }}>
                This copies <code>Cores/</code>, <code>Assets/</code> (non-music) and <code>Platforms/</code> to the
                card. Your <code>music.iso</code> library is never touched.
              </p>
            </>
          )}

          {phase !== 'confirm' && (
            <div className="log" ref={logRef}>
              {lines.map((l, i) => (
                <div key={i} className={l.cls}>
                  {l.text}
                </div>
              ))}
            </div>
          )}
        </div>
        <footer>
          {phase === 'confirm' && (
            <>
              <button onClick={onClose}>Cancel</button>
              <button className="primary" onClick={go} disabled={!info?.available}>
                Update Core on Card
              </button>
            </>
          )}
          {phase === 'running' && <button disabled>Updating…</button>}
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
