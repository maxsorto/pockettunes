#!/usr/bin/env bash
# Generate a tiny music library for the desktop build: five 20 s sine-tone
# MP3s, gradient album art, and playlist.tsv, laid out like music.iso.
# Needs ffmpeg.
set -euo pipefail
OUT="${1:-testlib}"
mkdir -p "$OUT/art"
: > "$OUT/playlist.tsv"
i=0
while IFS='|' read -r title artist album hz; do
    i=$((i + 1))
    f=$(printf "%02d_track.mp3" "$i")
    ffmpeg -loglevel error -y -f lavfi -i "sine=frequency=$hz:duration=20" \
        -ac 2 -ar 48000 -b:a 320k "$OUT/$f"
    ffmpeg -loglevel error -y -f lavfi \
        -i "gradients=s=200x200:c0=0x$(printf %06x $((hz * 9973 % 16777215))):c1=0x202040:duration=1:speed=0" \
        -frames:v 1 -pix_fmt rgb565le -f rawvideo "$OUT/art/${f%.mp3}.bin"
    printf "%s\t%s\t%s\t%s\t20\t256\n" "$f" "$title" "$artist" "$album" >> "$OUT/playlist.tsv"
done <<'TRACKS'
Sine Wave Sunrise|Test Tones|Calibration Vol. 1|440
Fourth Of A|Test Tones|Calibration Vol. 1|330
A Very Long Title That Should Scroll Across The Now Playing Screen|The Marquee Testers|Long Names Edition|550
Low Hum|Bass Department|Rumble|110
High Whistle|Bass Department|Rumble|880
TRACKS
echo "Test library ready: $OUT/ ($i tracks)"
