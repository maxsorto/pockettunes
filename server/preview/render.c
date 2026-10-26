/*
 * PocketTunes Studio render harness.
 *
 * Renders the on-device UI screens to PPM files using the REAL firmware
 * renderer (ipod_ui.c), so the Sync app's Studio tab shows pixel-accurate
 * previews without flashing hardware.
 *
 * The backend compiles this on demand with the firmware source on the include
 * path, e.g.:
 *   clang -O2 -I<firmware-src-dir> render.c -o render.bin -lm
 * then runs:  render.bin <output-dir>   (writes <output-dir>/<screen>.ppm)
 */
#include "ipod_ui.h"
#include "ipod_ui.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint16_t fb[UI_W * UI_H];

static const char *SAMPLE[] = {
    "_ _ - No Turning Back", "2 Chainz - Feds Watching", "2 Chainz - I'm Different",
    "AKA AKA - Spoony Talker", "AKA AKA - Relajate (Milkwish)", "AKA AKA - Taksi Taksi",
    "AmpLive - Video Tapez", "Armin van Buuren - Light The Skies", "Augustana - Sunday Best",
    "Avicii - Wake Me Up", "Daft Punk - Get Lucky", "Weezer - Heart Songs", "Wolfmother - Joker",
};
static const int N = (int)(sizeof(SAMPLE) / sizeof(SAMPLE[0]));

static const char *title_of(int i, void *ctx) { (void)ctx; return SAMPLE[i]; }
static int folder_of(int i, void *ctx) { (void)ctx; return (i % 3) != 1; }

static char OUT[1024];

static void write_ppm(const char *name) {
    char p[1140];
    snprintf(p, sizeof p, "%s/%s", OUT, name);
    FILE *f = fopen(p, "wb");
    if (!f) return;
    fprintf(f, "P6\n%d %d\n255\n", UI_W, UI_H);
    for (int i = 0; i < UI_W * UI_H; i++) {
        uint16_t px = fb[i];
        int r = ((px >> 11) & 31) * 255 / 31, g = ((px >> 5) & 63) * 255 / 63, b = (px & 31) * 255 / 31;
        fputc(r, f); fputc(g, f); fputc(b, f);
    }
    fclose(f);
}

int main(int argc, char **argv) {
    strncpy(OUT, argc > 1 ? argv[1] : ".", sizeof(OUT) - 1);
    OUT[sizeof(OUT) - 1] = 0;

    /* Main menu, one per theme. */
    ui_set_playstate(1);
    ui_set_theme(0);
    ui_menu(fb, "Music", N, 1, 0, title_of, folder_of, NULL);
    write_ppm("menu_video.ppm");
    if (IPOD_NTHEMES > 1) {
        ui_set_theme(1);
        ui_menu(fb, "Music", N, 1, 0, title_of, folder_of, NULL);
        write_ppm("menu_classic.ppm");
    }
    if (IPOD_NTHEMES > 2) {
        ui_set_theme(2);
        ui_menu(fb, "Music", N, 1, 0, title_of, folder_of, NULL);
        write_ppm("menu_mini.ppm");
    }

    /* Now Playing (normal + a long-title marquee case). */
    ui_set_theme(0);
    ui_set_playstate(2);
    ui_now_playing(fb, "Feds Watching", "2 Chainz", "Based on a T.R.U. Story", 2, N, 67, 250, NULL, 80, 0, 0);
    write_ppm("nowplaying.ppm");
    ui_now_playing(fb, "A Really Quite Long Song Title That Overflows",
                   "Armin van Buuren feat. Somebody", "Some Very Long Album Name Edition",
                   2, N, 67, 250, NULL, 80, 0, 2200);
    write_ppm("marquee.ppm");

    /* Boot splash. */
    ui_boot(fb, 55);
    write_ppm("boot.ppm");
    return 0;
}
