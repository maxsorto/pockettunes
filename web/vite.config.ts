import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

// Dev server proxies /api to the Hono backend on :4380.
// Production build is served directly by the backend from web/dist.
const BACKEND = process.env.BACKEND_URL ?? 'http://localhost:4380';
export default defineConfig({
  plugins: [react()],
  server: {
    port: 5173,
    proxy: {
      '/api': {
        target: BACKEND,
        changeOrigin: true,
        // SSE needs an unbuffered proxy connection.
        ws: false,
      },
    },
  },
  build: {
    outDir: 'dist',
    emptyOutDir: true,
  },
});
