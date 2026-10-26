# Source recovery

The original firmware source was lost on 2026-07-04 (it lived in a temporary
folder that macOS purged). This folder holds everything recovered from the
published `release/Assets/pockettunes/common/pockettunes.elf`, which still
carries its full symbol table.

- `decompiled/` — Ghidra 12.2 pseudocode for every app function, grouped by
  original source file (`main.c`, `ipod_ui.c`, `game_*.c`; `global` = exported
  functions). Reference only; the clean rebuild lives in `../firmware/src/`.
- `symbols.txt` — `readelf -sW` output: every function/variable with address,
  size and source file.
- `strings*.txt` — every string literal in the app's read-only data.
- `tools/` — the scripts used: `Dump.java` (Ghidra headless decompile),
  `elfdump.py` (read bytes by address), `gen_headers.py` (regenerates the
  font atlas and Apple logo headers byte-for-byte).

Build facts recovered from the ELF:
- Compiler: GCC 16.1.0, `-march=rv32imafc -mabi=ilp32f -O2`, SDK `app.ld`.
- SDK: openfpgaOS/openfpgaSDK commit `827d47d` (2026-06-24). The release's
  `os.bin`, `os25.rbf_r` and `loader.bin` match that commit exactly.
- Build flavour: `UI_SCALE=2` (640x480 RGB565), 200x200 album art.
