/* ipod_ui.h — iPod 5G-style UI rendering over an RGB565 framebuffer.
 *
 * Pure C with zero of_* calls, so the same code renders on the Pocket and in
 * a Mac preview harness. Layout literals are written in 320x240 units and
 * scaled with UI_S(), so -DUI_SCALE=2 renders the crisp 640x480 build.
 */
#ifndef IPOD_UI_H
#define IPOD_UI_H

#include <stdint.h>

#ifndef UI_SCALE
#define UI_SCALE 1
#endif
#define UI_S(n) ((n) * UI_SCALE)

#define UI_W UI_S(320)
#define UI_H UI_S(240)

#define UI_ROWS     7          /* menu rows visible at once */
#define UI_BAR_H    UI_S(21)   /* status bar height */
#define UI_ROW_H    UI_S(28)   /* menu row height */

/* Now Playing album art: ART_SRC is the size stored on the ISO, ART_SZ the
 * size drawn on screen. Must match the sync app's ART_DIM. */
#define ART_SRC 200
#define ART_SZ  UI_S(100)
#define ART_X   UI_S(9)
#define ART_Y   UI_S(34)
#define NP_TX   UI_S(118)      /* left edge of the title/artist/album text */
#define NP_TW   UI_S(196)      /* width of the scrolling text window */

typedef struct {
    const char *name;
    uint16_t bg, fg;
    uint16_t bar_top, bar_bot, bar_line;     /* status bar gradient + rule */
    uint16_t sel_top, sel_bot;               /* selected row gradient */
    uint16_t sel_hi, sel_lo;                 /* selected row bevel lines */
    uint16_t sel_fg;                         /* selected row text */
    uint16_t dim;                            /* arrows, scrollbar thumb */
    uint16_t np_artist, np_album;            /* Now Playing secondary text */
    uint16_t art_frame, well;                /* art border, empty art / tracks */
    uint16_t prog_top, prog_bot, prog_hi;    /* scrubber fill */
    uint16_t time;                           /* elapsed / remaining */
    uint16_t batt_fill, batt_low, batt_frame;
} ipod_theme_t;

extern const ipod_theme_t IPOD_THEMES[];
extern const int IPOD_NTHEMES;

void        ui_set_theme(int i);
int         ui_theme_index(void);
const char *ui_theme_name(void);
uint16_t    ui_bg(void);
uint16_t    ui_fg(void);

/* 0 = stopped, 1 = playing, 2 = paused (status bar icon). */
void ui_set_playstate(int s);

void ui_clear(uint16_t *fb, uint16_t c);
void ui_fill(uint16_t *fb, int x, int y, int w, int h, uint16_t c);
void ui_vgrad(uint16_t *fb, int x, int y, int w, int h, uint16_t c0, uint16_t c1);

int  ui_text(uint16_t *fb, int x, int y, const char *s, uint16_t c);
int  ui_text_w(const char *s);
void ui_text_right(uint16_t *fb, int rx, int y, const char *s, uint16_t c);
void ui_text_center(uint16_t *fb, int cx, int y, const char *s, uint16_t c);
void ui_text_clip(uint16_t *fb, int x, int y, int maxw, const char *s, uint16_t c);

void ui_status_bar(uint16_t *fb, const char *title, int batt_pct);

typedef const char *(*ui_label_fn)(int idx, void *ctx);
typedef int (*ui_arrow_fn)(int idx, void *ctx);

int  ui_visible_rows(void);
void ui_menu(uint16_t *fb, const char *title, int n, int sel, int top,
             ui_label_fn label, ui_arrow_fn arrow, void *ctx);
void ui_menu_row(uint16_t *fb, int row, int n, int sel, int top,
                 ui_label_fn label, ui_arrow_fn arrow, void *ctx);
void ui_menu_scrollbar(uint16_t *fb, int n, int top);

void ui_now_playing(uint16_t *fb, const char *title, const char *artist,
                    const char *album, int idx, int total, int pos_s, int dur_s,
                    const uint16_t *art, int batt_pct, int flags, uint32_t t_ms);

/* Boot splash: Apple logo + progress bar, pct 0..100. */
void ui_boot(uint16_t *fb, int pct);

#endif
