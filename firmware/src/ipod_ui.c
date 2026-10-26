/* ipod_ui.c — iPod 5G-style UI rendering. See ipod_ui.h. */
#include "ipod_ui.h"

#include <string.h>

#if UI_SCALE >= 2
#include "font_ipod_2x.h"
#else
#include "font_ipod.h"
#endif
#include "apple_logo.h"

/* Advance used when measuring a character outside the atlas (drawn as '?'). */
#define FP_UNKNOWN_ADV 15

/*                 name            bg      fg      bar_top bar_bot bar_ln  sel_top sel_bot sel_hi  sel_lo  sel_fg  dim     artist  album   frame   well    p_top   p_bot   p_hi    time    b_fill  b_low   b_frame */
const ipod_theme_t IPOD_THEMES[] = {
    { "iPod Video",   0xffff, 0x0000, 0xe71c, 0xc618, 0x94b2, 0x3bf9, 0x1a73, 0x6d5c, 0x11cf, 0xffff, 0x8c71, 0x3186, 0x632c, 0xb596, 0xc618, 0x3bf9, 0x1a73, 0x6d5c, 0x3186, 0x5dab, 0xd186, 0x4a49 },
    { "iPod Classic", 0x0000, 0xffff, 0x4208, 0x2104, 0x4208, 0x3bf9, 0x1a73, 0x6d5c, 0x11cf, 0xffff, 0x8c71, 0xad55, 0x8c71, 0x4208, 0x2945, 0x3bf9, 0x1a73, 0x6d5c, 0xad55, 0x5dab, 0xd186, 0x9cd3 },
    { "iPod Mini",    0xf79e, 0x18e3, 0xd69a, 0xad55, 0x8410, 0x9cd3, 0x630c, 0xbdf7, 0x4208, 0xffff, 0x630c, 0x4208, 0x630c, 0x8410, 0xc618, 0x9cd3, 0x630c, 0xbdf7, 0x4208, 0x52aa, 0xd186, 0x630c },
};
const int IPOD_NTHEMES = sizeof IPOD_THEMES / sizeof IPOD_THEMES[0];

static const ipod_theme_t *T = &IPOD_THEMES[0];
static int g_ti;
static int g_play;

void ui_set_theme(int i)
{
    if (i < 0) i = 0;
    if (i > IPOD_NTHEMES - 1) i = IPOD_NTHEMES - 1;
    g_ti = i;
    T = &IPOD_THEMES[i];
}

int ui_theme_index(void) { return g_ti; }
const char *ui_theme_name(void) { return T->name; }
uint16_t ui_bg(void) { return T->bg; }
uint16_t ui_fg(void) { return T->fg; }
void ui_set_playstate(int s) { g_play = s; }

/* Blend a toward b by t/n per RGB565 channel. */
static uint16_t lerp565(uint16_t a, uint16_t b, int t, int n)
{
    int ar = a >> 11, ag = (a >> 5) & 63, ab = a & 31;
    int br = b >> 11, bg = (b >> 5) & 63, bb = b & 31;
    int r = ar + (br - ar) * t / n;
    int g = ag + (bg - ag) * t / n;
    int bl = ab + (bb - ab) * t / n;
    return (uint16_t)((r << 11) | (g << 5) | bl);
}

void ui_clear(uint16_t *fb, uint16_t c)
{
    if ((c >> 8) == (c & 0xff)) {
        memset(fb, c >> 8, UI_W * UI_H * 2);
        return;
    }
    for (uint16_t *p = fb, *e = fb + UI_W * UI_H; p != e; p++) *p = c;
}

void ui_fill(uint16_t *fb, int x, int y, int w, int h, uint16_t c)
{
    for (int yy = y; yy < y + h; yy++) {
        if ((unsigned)yy >= UI_H) continue;
        uint16_t *row = fb + yy * UI_W;
        for (int xx = x; xx < x + w; xx++)
            if ((unsigned)xx < UI_W) row[xx] = c;
    }
}

void ui_vgrad(uint16_t *fb, int x, int y, int w, int h, uint16_t c0, uint16_t c1)
{
    int n = h < 2 ? 2 : h;
    for (int i = 0; i < h; i++) {
        if ((unsigned)(y + i) >= UI_H) continue;
        uint16_t c = lerp565(c0, c1, i, n - 1);
        uint16_t *row = fb + (y + i) * UI_W;
        for (int xx = x; xx < x + w; xx++)
            if ((unsigned)xx < UI_W) row[xx] = c;
    }
}

/* ---- text ---------------------------------------------------------------- */

static int glyph_of(int ch)
{
    unsigned g = (unsigned)(ch - FP_FIRST) & 0xff;
    return g < FP_COUNT ? (int)g : '?' - FP_FIRST;
}

static int adv_of(int ch)
{
    unsigned g = (unsigned)(ch - FP_FIRST) & 0xff;
    return g < FP_COUNT ? FP_FONT[g][0] : FP_UNKNOWN_ADV;
}

/* Anti-aliased glyph: coverage > 11 is drawn, >= 248 is solid. */
static void ui_char(uint16_t *fb, int x, int y, int ch, uint16_t c)
{
    const uint8_t *g = FP_FONT[glyph_of(ch)];
    int w = g[1];
    const uint8_t *rowp = g + 2;
    uint16_t *dst = fb + y * UI_W + x;
    for (int r = 0; r < FP_H; r++, rowp += FP_MAXW, dst += UI_W) {
        if ((unsigned)(y + r) >= UI_H || w == 0) continue;
        for (int i = 0; i < w; i++) {
            int cov = rowp[i];
            if (cov <= 11 || (unsigned)(x + i) >= UI_W) continue;
            dst[i] = cov >= 248 ? c : lerp565(dst[i], c, cov, 255);
        }
    }
}

int ui_text_w(const char *s)
{
    int w = 0;
    for (; *s; s++) w += adv_of((unsigned char)*s);
    return w;
}

int ui_text(uint16_t *fb, int x, int y, const char *s, uint16_t c)
{
    for (; *s; s++) {
        ui_char(fb, x, y, (unsigned char)*s, c);
        x += adv_of((unsigned char)*s);
    }
    return x;
}

void ui_text_right(uint16_t *fb, int rx, int y, const char *s, uint16_t c)
{
    if (!*s) return;
    ui_text(fb, rx - ui_text_w(s), y, s, c);
}

void ui_text_center(uint16_t *fb, int cx, int y, const char *s, uint16_t c)
{
    if (!*s) return;
    ui_text(fb, cx - ui_text_w(s) / 2, y, s, c);
}

/* Draw s in maxw pixels, truncating with ".." when it doesn't fit. */
void ui_text_clip(uint16_t *fb, int x, int y, int maxw, const char *s, uint16_t c)
{
    if (ui_text_w(s) <= maxw) {
        ui_text(fb, x, y, s, c);
        return;
    }
    int end = x + maxw;
    for (; *s; s++) {
        int a = adv_of((unsigned char)*s);
        if (x + a + UI_S(8) > end) break;
        ui_char(fb, x, y, (unsigned char)*s, c);
        x += a;
    }
    ui_text(fb, x, y, "..", c);
}

/* Horizontally scrolling text inside [NP_TX, NP_TX+NP_TW): pause, scroll
 * left at 17 px/s (1x), pause, scroll back. */
static void ui_marquee(uint16_t *fb, int y, const char *s, uint16_t c, uint32_t t_ms)
{
    const int x0 = NP_TX, win = NP_TW, hold = 1200;
    int w = ui_text_w(s);
    if (!*s) return;
    if (w <= win) {
        ui_text(fb, x0, y, s, c);
        return;
    }
    int over = w - win;
    unsigned dur = (unsigned)(over * 1000) / UI_S(17);
    int cycle = (int)dur + hold;
    if (cycle) t_ms %= (unsigned)(cycle * 2);
    int off = 0;
    if (t_ms >= (unsigned)hold) {
        if ((int)t_ms < cycle)
            off = (int)(t_ms - hold) * over / (int)dur;
        else if ((int)t_ms >= (int)dur + 2 * hold)
            off = over - (int)(t_ms - (dur + 2 * hold)) * over / (int)dur;
        else
            off = over;
    }
    int x = x0 - off;
    for (; *s; s++) {
        int g = glyph_of((unsigned char)*s);
        const uint8_t *gl = FP_FONT[g];
        int gw = gl[1];
        if (x + gw > x0) {
            if (x > x0 + win - 1) return;
            const uint8_t *rowp = gl + 2;
            uint16_t *dst = fb + y * UI_W + x;
            for (int r = 0; r < FP_H; r++, rowp += FP_MAXW, dst += UI_W)
                for (int i = 0; i < gw; i++) {
                    int cov = rowp[i];
                    if (cov <= 11 || (unsigned)(x + i - x0) >= (unsigned)win) continue;
                    dst[i] = cov >= 248 ? c : lerp565(dst[i], c, cov, 255);
                }
        }
        x += gl[0];
        if (x > x0 + win - 1) return;
    }
}

/* ---- chrome -------------------------------------------------------------- */

void ui_status_bar(uint16_t *fb, const char *title, int batt_pct)
{
    for (int i = 0; i < UI_BAR_H; i++) {
        uint16_t c = lerp565(T->bar_top, T->bar_bot, i, UI_BAR_H - 1);
        for (int x = 0; x < UI_W; x++) fb[i * UI_W + x] = c;
    }
    for (int x = 0; x < UI_W * UI_S(1); x++) fb[UI_S(20) * UI_W + x] = T->bar_line;

    if (title && *title)
        ui_text_center(fb, UI_W / 2, UI_S(1), title, T->fg);

    /* play / pause glyph */
    const int ix = UI_S(272), iy = UI_S(6);
    if (g_play == 1) {
        const int h = UI_S(9) / 2;   /* half-height of the triangle */
        for (int r = 0; r < 2 * h - 1; r++) {
            int w = r < h ? 2 * (r + 1) : 2 * (2 * h - 1 - r);
            for (int i = 0; i < w; i++) fb[(iy + r) * UI_W + ix + i] = T->fg;
        }
    } else if (g_play == 2) {
        ui_fill(fb, ix, iy, UI_S(3), UI_S(9), T->fg);
        ui_fill(fb, ix + UI_S(5), iy, UI_S(3), UI_S(9), T->fg);
    }

    /* battery */
    ui_fill(fb, UI_S(288), UI_S(6), UI_S(24), UI_S(10), T->batt_frame);
    ui_fill(fb, UI_S(289), UI_S(7), UI_S(22), UI_S(8), T->bg);
    ui_fill(fb, UI_S(312), UI_S(8), UI_S(2), UI_S(6), T->batt_frame);
    int pct = batt_pct > 100 ? 100 : batt_pct < 0 ? 0 : batt_pct;
    uint16_t fc = batt_pct < 16 ? T->batt_low : T->batt_fill;
    int fw = pct * UI_S(20) / 100;
    if (fw > 0) ui_fill(fb, UI_S(290), UI_S(8), fw, UI_S(6), fc);
}

/* ---- menus --------------------------------------------------------------- */

int ui_visible_rows(void) { return UI_ROWS; }

void ui_menu_row(uint16_t *fb, int row, int n, int sel, int top,
                 ui_label_fn label, ui_arrow_fn arrow, void *ctx)
{
    int extra = n <= UI_ROWS ? UI_S(5) : 0;   /* no scrollbar: wider text */
    int idx = top + row;
    int y0 = UI_BAR_H + row * UI_ROW_H;

    for (int y = y0; y < y0 + UI_ROW_H; y++)
        if ((unsigned)y < UI_H)
            for (int x = 0; x < UI_W; x++) fb[y * UI_W + x] = T->bg;
    if (idx >= n || idx < 0) return;

    uint16_t tc;
    if (idx == sel) {
        for (int i = 0; i < UI_ROW_H; i++) {
            if ((unsigned)(y0 + i) >= UI_H) continue;
            uint16_t c = lerp565(T->sel_top, T->sel_bot, i, UI_ROW_H - 1);
            for (int x = 0; x < UI_W; x++) fb[(y0 + i) * UI_W + x] = c;
        }
        for (int i = UI_S(1); i < UI_S(2); i++)
            if ((unsigned)(y0 + i) < UI_H)
                for (int x = 0; x < UI_W; x++) fb[(y0 + i) * UI_W + x] = T->sel_hi;
        for (int i = UI_ROW_H - UI_S(1); i < UI_ROW_H; i++)
            if ((unsigned)(y0 + i) < UI_H)
                for (int x = 0; x < UI_W; x++) fb[(y0 + i) * UI_W + x] = T->sel_lo;
        tc = T->sel_fg;
    } else {
        tc = T->fg;
    }

    int has_arrow = arrow ? arrow(idx, ctx) : 0;
    const char *s = label(idx, ctx);
    if (!s) s = "";
    int ty = y0 + UI_S(5) + UI_SCALE / 2;
    if (has_arrow) {
        ui_text_clip(fb, UI_S(9), ty, UI_S(284) + extra, s, tc);
        ui_char(fb, UI_S(293) + extra, ty, '>', idx == sel ? T->sel_fg : T->dim);
    } else {
        ui_text_clip(fb, UI_S(9), ty, UI_S(294) + extra, s, tc);
    }
}

void ui_menu_scrollbar(uint16_t *fb, int n, int top)
{
    if (n <= UI_ROWS) return;
    const int x = UI_S(315), w = UI_S(5), y0 = UI_BAR_H, track = UI_H - UI_BAR_H;
    ui_fill(fb, x, y0, w, track, T->well);
    int th = track * UI_ROWS / n;
    if (th < UI_S(16)) th = UI_S(16);
    int ty = y0 + (track - th) * top / (n - UI_ROWS);
    ui_fill(fb, x, ty, w, th, T->dim);
}

void ui_menu(uint16_t *fb, const char *title, int n, int sel, int top,
             ui_label_fn label, ui_arrow_fn arrow, void *ctx)
{
    ui_clear(fb, T->bg);
    for (int r = 0; r < UI_ROWS && top + r < n; r++)
        ui_menu_row(fb, r, n, sel, top, label, arrow, ctx);
    if (n > UI_ROWS) ui_menu_scrollbar(fb, n, top);
    ui_status_bar(fb, title, 100);
}

/* ---- now playing --------------------------------------------------------- */

static void fmt_time(char *b, int secs)
{
    int s = secs < 0 ? 0 : secs;
    int m = s / 60;
    s %= 60;
    if (secs >= 600) *b++ = '0' + m / 10 % 10;
    *b++ = '0' + m % 10;
    *b++ = ':';
    *b++ = '0' + s / 10;
    *b++ = '0' + s % 10;
    *b = 0;
}

static char *put_int(char *b, int v)
{
    char tmp[12];
    int n = 0;
    do { tmp[n++] = '0' + v % 10; v /= 10; } while (v);
    while (n) *b++ = tmp[--n];
    return b;
}

void ui_now_playing(uint16_t *fb, const char *title, const char *artist,
                    const char *album, int idx, int total, int pos_s, int dur_s,
                    const uint16_t *art, int batt_pct, int flags, uint32_t t_ms)
{
    (void)flags;
    ui_clear(fb, T->bg);
    ui_status_bar(fb, "Now Playing", batt_pct);

    /* album art, framed */
    ui_fill(fb, ART_X - UI_S(1), ART_Y - UI_S(1), ART_SZ + UI_S(2), ART_SZ + UI_S(2), T->art_frame);
    if (art) {
        for (int y = 0; y < ART_SZ; y++)
            memcpy(fb + (ART_Y + y) * UI_W + ART_X, art + y * ART_SZ, ART_SZ * 2);
    } else {
        /* placeholder: an eighth note on the well colour */
        ui_fill(fb, ART_X, ART_Y, ART_SZ, ART_SZ, T->well);
        ui_fill(fb, UI_S(67), UI_S(54), UI_S(4), UI_S(46), T->fg);
        ui_fill(fb, UI_S(53), UI_S(92), UI_S(18), UI_S(14), T->fg);
        ui_fill(fb, UI_S(67), UI_S(52), UI_S(16), UI_S(5), T->fg);
    }

    ui_marquee(fb, UI_S(48), title ? title : "", T->fg, t_ms);
    ui_marquee(fb, UI_S(72), artist ? artist : "", T->np_artist, t_ms);
    ui_marquee(fb, UI_S(96), album ? album : "", T->np_album, t_ms);

    char buf[32], *p = put_int(buf, idx);
    memcpy(p, " of ", 4);
    p = put_int(p + 4, total);
    *p = 0;
    ui_text_right(fb, UI_S(312), UI_S(26), buf, T->np_album);

    /* scrubber track */
    const int sx = UI_S(18), sw = UI_S(284), sy = UI_S(214), sh = UI_S(9);
    ui_fill(fb, sx, sy, sw, sh, T->well);
    ui_fill(fb, sx, sy, sw, UI_S(1), T->bar_line);
    ui_fill(fb, sx, sy + sh - UI_S(1), sw, UI_S(1), T->bar_line);

    char tb[12];
    fmt_time(tb, pos_s);
    ui_text(fb, UI_S(16), UI_S(192), tb, T->time);

    if (dur_s <= 0) return;
    int fw = 0;
    if (pos_s >= 0) {
        int p2 = pos_s > dur_s ? dur_s : pos_s;
        fw = p2 * sw / dur_s;
        if (fw) ui_vgrad(fb, sx, sy, fw, sh, T->prog_top, T->prog_bot);
    }
    if (fw) {
        ui_fill(fb, sx, sy + UI_S(1), fw, UI_S(1), T->prog_hi);
    }
    /* knob */
    int kx = sx - UI_S(1) + fw, kw = UI_S(3);
    ui_fill(fb, kx, sy - UI_S(2), kw, UI_S(13), 0xffff);
    ui_fill(fb, kx, sy - UI_S(2), kw, UI_S(1), T->prog_bot);
    ui_fill(fb, kx, sy + sh + UI_S(1), kw, UI_S(1), T->prog_bot);

    tb[0] = '-';
    fmt_time(tb + 1, dur_s - pos_s);
    ui_text_right(fb, UI_S(304), UI_S(192), tb, T->time);
}

/* ---- boot ---------------------------------------------------------------- */

void ui_boot(uint16_t *fb, int pct)
{
    memset(fb, 0, UI_W * UI_H * 2);
    const int lx = UI_S(137), ly = UI_S(66);
    for (int y = 0; y < APPLE_H; y++)
        for (int x = 0; x < APPLE_W; x++) {
            unsigned v = APPLE_COV[y * APPLE_W + x];
            if (v < 8) continue;
            uint16_t c = 0xffff;
            if (v < 248) {
                unsigned r5 = v * 31 / 255;
                c = (uint16_t)(r5 | (v * 63 / 255) << 5 | r5 << 11);
            }
            for (int dy = 0; dy < UI_SCALE; dy++)
                for (int dx = 0; dx < UI_SCALE; dx++)
                    fb[(ly + y * UI_SCALE + dy) * UI_W + lx + x * UI_SCALE + dx] = c;
        }

    ui_fill(fb, UI_S(107), UI_S(175), UI_S(106), UI_S(8), 0x4208);
    ui_fill(fb, UI_S(108), UI_S(176), UI_S(104), UI_S(6), 0x18e3);
    if (pct > 100) pct = 100;
    if (pct < 0) pct = 0;
    int fw = pct * UI_S(104) / 100;
    if (fw > 0) ui_fill(fb, UI_S(108), UI_S(176), fw, UI_S(6), 0xdefb);
}
