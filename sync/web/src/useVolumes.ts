import { useEffect, useRef, useState } from 'react';
import { listVolumes, type Volume } from './api';

/** Poll mounted volumes every few seconds to detect insert/remove. */
export function useVolumes(intervalMs = 4000) {
  const [volumes, setVolumes] = useState<Volume[]>([]);
  const [loading, setLoading] = useState(true);
  const timer = useRef<number | null>(null);

  async function refresh() {
    try {
      const v = await listVolumes();
      setVolumes(v);
    } catch {
      /* keep last known */
    } finally {
      setLoading(false);
    }
  }

  useEffect(() => {
    void refresh();
    timer.current = window.setInterval(refresh, intervalMs);
    return () => {
      if (timer.current) window.clearInterval(timer.current);
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [intervalMs]);

  return { volumes, loading, refresh };
}
