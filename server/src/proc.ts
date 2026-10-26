import { spawn } from 'node:child_process';
import { CHILD_ENV } from './config.js';

export interface RunResult {
  code: number;
  stdout: string;
  stderr: string;
}

export interface RunOptions {
  /** Capture stdout/stderr (default true). */
  capture?: boolean;
  /** Optional timeout in ms. */
  timeoutMs?: number;
}

/**
 * Spawn a child process and resolve with its exit code + captured output.
 * Never rejects on non-zero exit — callers inspect `code`. Rejects only on
 * spawn errors (e.g. command not found).
 *
 * IMPORTANT: stdin is closed immediately. We never pipe our own stdin into
 * children. The reference scripts pass `-nostdin` to ffmpeg for the same
 * reason (ffmpeg will otherwise consume the parent's stdin and corrupt loops).
 */
export function run(cmd: string, args: string[], opts: RunOptions = {}): Promise<RunResult> {
  const { capture = true, timeoutMs } = opts;
  return new Promise((resolve, reject) => {
    const child = spawn(cmd, args, {
      env: CHILD_ENV,
      stdio: ['ignore', capture ? 'pipe' : 'inherit', capture ? 'pipe' : 'inherit'],
    });

    let stdout = '';
    let stderr = '';
    let timer: NodeJS.Timeout | undefined;

    if (capture) {
      child.stdout?.on('data', (d) => (stdout += d.toString()));
      child.stderr?.on('data', (d) => (stderr += d.toString()));
    }

    if (timeoutMs) {
      timer = setTimeout(() => {
        child.kill('SIGKILL');
      }, timeoutMs);
    }

    child.on('error', (err) => {
      if (timer) clearTimeout(timer);
      reject(err);
    });

    child.on('close', (code) => {
      if (timer) clearTimeout(timer);
      resolve({ code: code ?? -1, stdout, stderr });
    });
  });
}
