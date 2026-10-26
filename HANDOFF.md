# Handoff: flash the rebuilt core and test it on the Pocket

For the Claude Code session on the machine that has the Pocket's SD card.
Written 2026-10-25 at the end of the session that rebuilt the source.

## Where things stand

The original firmware source was lost on 2026-07-04. On 2026-10-25 it was
rebuilt from the published `release/.../pockettunes.elf`, which kept its full
symbol table. See `recovery/README.md` for how. Current state:

- `firmware/` builds with zero warnings. `make` gives the Pocket SD tree and
  `make test` runs the desktop (SDL) version.
- `ipod_ui.c` renders pixel-identical to the original renderer on all six
  saved reference screens.
- Compared with `release/`: code size is within 0.2% and every data structure
  is the same size. `os.bin`, `os25.rbf_r`, `loader.bin` and `bank.ofsf` in
  the built SD tree are byte-identical.
- In the desktop build, these all worked in a scripted run: menus, Songs,
  playback with art and scrolling title, volume overlay, pause, Brick,
  Music Quiz, Parachute and Solitaire.
- **Not yet tested on the Pocket.** That is the job.

## 1. Set up (once per machine)

```sh
brew install riscv64-elf-gcc sdl2 ffmpeg          # macOS; on Linux use the distro's riscv64-elf toolchain
git clone --recursive git@github.com:maxsorto/pockettunes.git ~/pockettunes
cd ~/pockettunes/firmware
make                                              # must end with "Ready: build/pocket/pockettunes/"
```

If the repo is already cloned: `git pull && git submodule update --init`.

## 2. Back up what's on the card first

The card holds the last core known to work. Copy the PocketTunes parts before
overwriting anything. Assume the card mounts at `$SD`, for example
`/Volumes/Pocket` or `/Volumes/Untitled`. Check `ls /Volumes`; the card has
`Cores/`, `Assets/` and `Platforms/` at its root.

```sh
SD=/Volumes/<card>
B=~/pockettunes-sd-backup-$(date +%Y%m%d-%H%M)
mkdir -p "$B"
cp -R "$SD/Cores/DapperLogic.PocketTunes" "$B/"
cp -R "$SD/Platforms/pockettunes.json" "$B/" 2>/dev/null
mkdir -p "$B/Assets" && rsync -a --exclude '*.iso' "$SD/Assets/pockettunes" "$B/Assets/"
ls -R "$B" | head -40
```

Do not copy or touch `music.iso`, the music library on the card (several GB).
`make copy` leaves it alone too.

To roll back, copy `$B`'s contents back to the same places on the card.

## 3. Flash

```sh
cd ~/pockettunes/firmware
make copy SD="$SD"
```

Pass `SD=` explicitly. Auto-detect skips volumes with spaces in their names.
Then eject the card (`diskutil eject "$SD"`) and put it in the Pocket.

Card quirks from earlier sessions: the card can unmount on its own when idle.
Big copies over the Pocket's USB SD mode are flaky. The core is small (about
3.5 MB), so this copy is fine either way.

## 4. What the user should check on the Pocket

The user tests and reports. Walk them through this list and note anything
that differs from how the old build behaved:

1. Boot: Apple logo and progress bar, then the main menu. Text is crisp at
   640x480.
2. Songs, Artists, Albums: lists load and scroll. The scrollbar shows on
   long lists. Moving up and down is snappy.
3. Play a song: art shows, the title scrolls if it's long, and the time and
   bar advance.
4. Now Playing controls: Left/Right = previous/next, Up/Down = volume
   overlay, START = pause/resume, B = back while the music keeps playing.
5. L1/R1 skip tracks from any screen while playing. SELECT jumps to Now
   Playing.
6. Shuffle Songs.
7. Settings, then Theme: switch between iPod Video, Classic and Mini.
8. Games: Brick, Music Quiz, Parachute and Solitaire each start, play, and
   exit with B, with music still playing.
9. A song plays to the end and the next one starts by itself.

## 5. If something is wrong

- Decide whether it's a hardware problem or a logic problem. Logic bugs
  usually reproduce in `make test` (keys: arrows = D-pad, Z = A, X = B,
  A = X, Q/W = L1/R1, Return = Start, right Shift = Select).
- Compare against the original: `recovery/decompiled/` has Ghidra
  pseudocode for every function. `recovery/symbols.txt` has every
  function and variable with its address and size. Disassemble the
  original with `riscv64-elf-objdump -d --start-address=0x... --stop-address=0x... release/Assets/pockettunes/common/pockettunes.elf`.
- Recovery notes on judgement calls are in the commit messages and in
  these source comments:
  - `open_any` returns the first successful `fopen`.
  - `P.paused` and `P.eof` are the two player fields recovered as unknowns.
  - The audio cushion is 14400 frames, or 33600 in a game or while Now
    Playing text scrolls.
  - Solitaire suits are ordered spade, heart, diamond, club.
- If the rebuilt core is unusable on the Pocket, restore the backup from
  step 2.

## 6. When done

- Commit fixes in `firmware/src/` with a clear message and push to `main`.
- Remove the "Not yet tested on the Pocket" line above, or replace this file
  with the test results.
- Known README inaccuracies, not yet fixed, to raise with the user:
  - "How it works" says WAV and FLAC are decoded and that saves hold settings
    and scores. The app only decodes MP3 (dr_mp3) and has no save code.
  - "Settings: Theme and volume" is wrong. Volume is Up/Down in Now Playing.
- Never build in a temporary or scratch folder. Keep everything in
  `~/pockettunes` and push often. Losing the source to a /tmp purge is how
  this whole recovery started.
