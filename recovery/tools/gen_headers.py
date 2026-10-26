"""Regenerate font_ipod_2x.h and apple_logo.h from the published pockettunes.elf."""
import struct, sys, os
E = sys.argv[1]; OUT = sys.argv[2]
d = open(E, 'rb').read()
shoff, = struct.unpack_from('<I', d, 0x20); shentsize, shnum, _ = struct.unpack_from('<HHH', d, 0x2e)
secs = [struct.unpack_from('<IIIIII', d, shoff + i * shentsize)[3:6] + (struct.unpack_from('<I', d, shoff + i * shentsize + 4)[0],) for i in range(shnum)]
def rd(a, n):
    for addr, off, size, typ in secs:
        if addr and addr <= a < addr + size and typ != 8: return d[off + a - addr: off + a - addr + n]
FP_H, FP_MAXW, N = 38, 29, 95
font = rd(0x10418164, N * (2 + FP_H * FP_MAXW))
with open(os.path.join(OUT, 'font_ipod_2x.h'), 'w') as f:
    f.write('/* Inter Regular @30px, proportional anti-aliased atlas for UI_SCALE=2.\n'
            ' * Per glyph: advance, width, then FP_H rows of FP_MAXW coverage bytes.\n'
            ' * Recovered byte-for-byte from the published pockettunes.elf. */\n'
            '#ifndef FONT_IPOD_2X_H\n#define FONT_IPOD_2X_H\n#include <stdint.h>\n\n'
            f'#define FP_H     {FP_H}\n#define FP_MAXW  {FP_MAXW}\n#define FP_FIRST 32\n#define FP_COUNT {N}\n\n'
            'static const uint8_t FP_FONT[FP_COUNT][2 + FP_H * FP_MAXW] = {\n')
    g = 2 + FP_H * FP_MAXW
    for i in range(N):
        b = font[i * g:(i + 1) * g]
        f.write(f'  /* {chr(32 + i)!r} */ {{{b[0]},{b[1]},\n')
        for r in range(FP_H):
            f.write('    ' + ','.join(str(x) for x in b[2 + r * FP_MAXW: 2 + (r + 1) * FP_MAXW]) + ',\n')
        f.write('  },\n')
    f.write('};\n\n#endif\n')
W, H = 46, 50
logo = rd(0x10417868, W * H)
with open(os.path.join(OUT, 'apple_logo.h'), 'w') as f:
    f.write('/* Boot splash Apple logo coverage mask, 46x50, drawn 2x. Recovered from pockettunes.elf. */\n'
            '#ifndef APPLE_LOGO_H\n#define APPLE_LOGO_H\n#include <stdint.h>\n\n'
            f'#define APPLE_W {W}\n#define APPLE_H {H}\n\n'
            'static const uint8_t APPLE_COV[APPLE_H * APPLE_W] = {\n')
    for r in range(H):
        f.write('  ' + ','.join(str(x) for x in logo[r * W:(r + 1) * W]) + ',\n')
    f.write('};\n\n#endif\n')
