# PocketTunes

An iPod-style music player for the Analogue Pocket, running as an app on openfpgaOS.

## Status
Private until the YouTube video is out.

## What's here
- `release/`: the build that is on my Pocket (2026-06-28): the openfpgaOS core package
  (`Cores/DapperLogic.PocketTunes`), the app binary (`pockettunes.elf`, RISC-V), `os.bin` and `bank.ofsf`.
  Copy `release/` onto the SD card root (merge folders).
- The music library (`Assets/pockettunes/common/music.iso`) is not in the repo; build your own.
- Source: to be pushed from the machine it was built on.
