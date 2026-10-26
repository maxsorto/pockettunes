import { useEffect, useState } from 'react';
import { renderPreview, previewImageUrl, type PreviewScreen } from './api';

/**
 * Studio tab: pixel-accurate snapshots of the on-device UI, rendered server
 * side with the real firmware renderer. Hit Refresh after a change to re-render
 * without flashing the Pocket. The frames are real PNGs, so you can drag one
 * out to save it (handy for posts / screenshots).
 */
export function Studio() {
  const [screens, setScreens] = useState<PreviewScreen[]>([]);
  const [token, setToken] = useState('');
  const [loading, setLoading] = useState(false);
  const [err, setErr] = useState<string | null>(null);
  const [scale, setScale] = useState(1);
  const [smooth, setSmooth] = useState(false);
  const [res, setRes] = useState<1 | 2>(2);
  const [renderedScale, setRenderedScale] = useState(1);

  async function render(scaleArg: 1 | 2 = res) {
    setLoading(true);
    setErr(null);
    try {
      const r = await renderPreview(scaleArg);
      setScreens(r.screens);
      setToken(r.token);
      setRenderedScale(r.scale);
    } catch (e: any) {
      setErr(e?.message ?? String(e));
    } finally {
      setLoading(false);
    }
  }

  useEffect(() => {
    void render();
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return (
    <div style={{ flex: 1, overflow: 'auto', padding: 20 }}>
      <div className="toolbar" style={{ padding: 0, marginBottom: 16, alignItems: 'baseline' }}>
        <strong style={{ fontSize: 15 }}>Device Studio</strong>
        <span style={{ fontSize: 12, color: 'var(--text-dim)' }}>
          Live snapshots from the real firmware renderer — no flashing needed.
        </span>
        <div className="grow" />
        <label style={{ fontSize: 12, color: 'var(--text-dim)', display: 'flex', gap: 6, alignItems: 'center' }}>
          Resolution
          <select
            value={res}
            onChange={(e) => {
              const v = Number(e.target.value) as 1 | 2;
              setRes(v);
              void render(v);
            }}
          >
            <option value={1}>320x240 (UI_SCALE=1)</option>
            <option value={2}>640x480 (default)</option>
          </select>
        </label>
        <label style={{ fontSize: 12, color: 'var(--text-dim)', display: 'flex', gap: 6, alignItems: 'center' }}>
          Zoom
          <select value={scale} onChange={(e) => setScale(Number(e.target.value))}>
            <option value={1}>1x</option>
            <option value={2}>2x</option>
            <option value={3}>3x</option>
          </select>
        </label>
        <label style={{ fontSize: 12, color: 'var(--text-dim)', display: 'flex', gap: 6, alignItems: 'center' }}>
          View
          <select value={smooth ? 'smooth' : 'pixels'} onChange={(e) => setSmooth(e.target.value === 'smooth')}>
            <option value="pixels">Raw pixels</option>
            <option value="smooth">Smoothed (like the Pocket scales it)</option>
          </select>
        </label>
        <button className="primary" onClick={() => render()} disabled={loading}>
          {loading ? 'Rendering…' : 'Refresh'}
        </button>
      </div>

      {err && (
        <div className="warn-box" style={{ marginBottom: 16, whiteSpace: 'pre-wrap' }}>
          {err}
        </div>
      )}

      <div style={{ display: 'flex', flexWrap: 'wrap', gap: 24 }}>
        {screens.map((s) => (
          <figure key={s.name} style={{ margin: 0 }}>
            <img
              src={previewImageUrl(s.name, token, renderedScale)}
              width={s.width * scale}
              height={s.height * scale}
              alt={s.label}
              style={{
                imageRendering: smooth ? 'auto' : 'pixelated',
                display: 'block',
                border: '1px solid var(--line)',
                borderRadius: 8,
                background: '#000',
              }}
            />
            <figcaption
              style={{ textAlign: 'center', fontSize: 12, color: 'var(--text-dim)', marginTop: 8 }}
            >
              {s.label}
            </figcaption>
          </figure>
        ))}
      </div>

      {!err && !loading && screens.length === 0 && <div className="empty">No preview yet.</div>}
    </div>
  );
}
