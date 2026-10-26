/* main.c — PocketTunes: an iPod 5G-style music player for openfpgaOS.
 *
 * Tracks live in music.iso (mounted at /music): playlist.tsv lists them,
 * art/<file>.bin holds 200x200 RGB565 album art. MP3s are decoded with
 * dr_mp3 and streamed to the 48 kHz audio FIFO from the main loop.
 *
 * Controls
 *   D-pad      navigate menus; Left/Right = prev/next and Up/Down = volume
 *              in Now Playing
 *   A          select / play          B       back (music keeps playing)
 *   START      play / pause           SELECT  jump to Now Playing
 *   L1 / R1    prev / next track while playing (page up/down in lists
 *              when nothing is playing)
 */
#include "of.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ipod_ui.h"
#include "game.h"

#define DR_MP3_IMPLEMENTATION
#define DR_MP3_NO_STDIO
#define DR_MP3_NO_SIMD
#include "dr_mp3.h"

/* ---- configuration ----------------------------------------------------- */

#define MUSIC_ISO      "music.iso"
#define MUSIC_DIR      "/music"
#define PLAYLIST       "playlist.tsv"

#define MAX_TRACKS     512
#define MAX_NAMES      512           /* distinct artists / albums */
#define NAME_LEN       80
#define NAV_DEPTH      12

#define SAMPLE_RATE    48000
#define DECODE_FRAMES  1024          /* PCM frames decoded per chunk */
#define DECODE_CHUNKS  64            /* max chunks decoded per main-loop pass */
#define CUSHION_SHORT  14400         /* 300 ms buffered: snappy pause/skip */
#define CUSHION_DEEP   33600         /* 700 ms when the screen redraws every frame */

#define FIRST_READ     (64 * 1024)   /* read up front before decoding starts */
#define STREAM_READ    (128 * 1024)  /* read per frame while the rest streams in */
#define FALLBACK_BPS   32000         /* bytes/s (256 kbps) to guess a duration */

#define GAIN_UNITY     256           /* Q8 ReplayGain */
#define VOL_STEP       5
#define VOL_OSD_MS     1500
#define BOOT_MS        1200          /* minimum boot splash duration */

/* ---- library ----------------------------------------------------------- */

typedef struct {
    char file[64];
    char title[NAME_LEN];
    char artist[NAME_LEN];
    char album[NAME_LEN];
    int  dur;                        /* seconds, 0 = unknown */
    int  gain;                       /* Q8, GAIN_UNITY = unity */
} track_t;

static track_t tracks[MAX_TRACKS];
static int     ntracks;
static char    artists[MAX_NAMES][NAME_LEN];
static int     nartists;
static char    albums[MAX_NAMES][NAME_LEN];
static int     nalbums;

static int curlist[MAX_TRACKS];      /* track indices of the open song list */
static int curlen;

static int queue[MAX_TRACKS];        /* play queue */
static int qlen;
static int qpos;

/* ---- navigation -------------------------------------------------------- */

enum { SCR_MENU, SCR_NOW_PLAYING, SCR_GAME };          /* values of `screen` */

enum {                                                 /* menu kinds */
    MENU_MAIN, MENU_SONGS, MENU_ARTISTS, MENU_ALBUMS,
    MENU_ARTIST_SONGS, MENU_ALBUM_SONGS, MENU_SETTINGS, MENU_THEMES,
    MENU_GAMES,
};

typedef struct {
    int screen;                      /* MENU_* */
    int sel, top;
    int arg;                         /* artist / album index for filtered lists */
} nav_t;

static nav_t nav[NAV_DEPTH];
static int   navdepth;
static int   screen;

static const char *const MAIN_ITEMS[] = {
    "Songs", "Artists", "Albums", "Shuffle Songs", "Now Playing", "Games",
    "Settings",
};
#define N_MAIN_ITEMS (int)(sizeof MAIN_ITEMS / sizeof MAIN_ITEMS[0])

/* ---- player ------------------------------------------------------------ */

static struct {
    int       active;                /* a track is loaded and decoding */
    int       paused;
    int       eof;                   /* decoder hit the end; waiting for FIFO to drain */
    drmp3     mp3;
    uint64_t  frames;                /* PCM frames written to the FIFO */
    int       dur;                   /* seconds */
    uint16_t *art;                   /* g_artsrc, or NULL if none */
    FILE     *f;                     /* rest of the file still streaming in */
    uint32_t  loaded;                /* bytes of filebuf filled so far */
    uint32_t  size;                  /* file size */
    int       gain;                  /* Q8 track gain */
} P;
#ifndef OF_PC   /* layout as shipped on the 32-bit Pocket */
_Static_assert(sizeof(P) == 32328, "player state layout changed");
#endif

static uint8_t  filebuf[32 * 1024 * 1024];   /* whole MP3 file */
static char     plbuf[160 * 1024];           /* playlist.tsv */
static int16_t  chunk[DECODE_FRAMES * 2];    /* stereo s16 decode buffer */
static uint16_t g_artsrc[ART_SRC * ART_SRC];
static uint16_t g_mfb[UI_W * UI_H];          /* persistent menu framebuffer */

static int      g_ring;                      /* audio FIFO capacity (frames) */
static int      g_target = CUSHION_SHORT;    /* frames to keep buffered */
static int      g_vol = 100;                 /* software volume, 0..100 */
static uint32_t g_vol_until;                 /* volume overlay visible until (ms) */
static int      g_vol_prev;                  /* overlay was visible last frame */
static int      g_ps;                        /* play state: 0 stop, 1 play, 2 pause */

/* What the menu framebuffer currently shows, for incremental redraws. */
static int m_pn = -1, m_pps = -1, m_pth = -1, m_pflt = -1;
static int m_psel = -1, m_ptop = -1, m_pk = -1;

/* ---- games ------------------------------------------------------------- */

static int  mq_reveal;               /* answer shown */
static uint32_t mq_reveal_until;
static int  mq_total, mq_score;
static int  mq_sel, mq_correct;
static int  mq_n;
static int  mq_choice[5];            /* track indices offered */

static void mq_reset(void);
static int  mq_step(uint16_t *fb);

static const game_t GAME_MUSICQUIZ = { "Music Quiz", mq_reset, mq_step };

static const game_t *const GAMES[] = {
    &GAME_BRICK, &GAME_MUSICQUIZ, &GAME_PARACHUTE, &GAME_SOLITAIRE,
};

static const game_t *cur_game;

/* ======================================================================== */

static int cmpstr(const void *a, const void *b)
{
    return strcmp(a, b);
}

/* Append s to a name list unless it is already there. */
static void add_unique(char list[][NAME_LEN], int *n, const char *s)
{
    for (int i = 0; i < *n; i++)
        if (strcmp(list[i], s) == 0)
            return;
    if (*n >= MAX_NAMES)
        return;
    snprintf(list[*n], NAME_LEN, "%s", s);
    (*n)++;
}

/* Open a file from the ISO, trying the ISO 9660 spellings (upper case, ";1"
 * version suffix) and finally the plain and root-relative paths. */
static FILE *open_any(const char *name)
{
    char path[160], up[96];
    FILE *f;

    snprintf(path, sizeof path, "%s/%s", MUSIC_DIR, name);
    if ((f = fopen(path, "rb")))
        return f;

    char *d = up;
    for (const char *s = name; *s; s++)
        *d++ = (*s >= 'a' && *s <= 'z') ? *s - 32 : *s;
    *d = '\0';

    snprintf(path, sizeof path, "%s/%s", MUSIC_DIR, up);
    if ((f = fopen(path, "rb")))
        return f;
    snprintf(path, sizeof path, "%s/%s;1", MUSIC_DIR, up);
    if ((f = fopen(path, "rb")))
        return f;
    if ((f = fopen(name, "rb")))
        return f;
    snprintf(path, sizeof path, "/%s", name);
    return fopen(path, "rb");
}

/* ---- menus ------------------------------------------------------------- */

static void nav_push(int kind, int arg)
{
    if (navdepth >= NAV_DEPTH)
        return;
    nav[navdepth++] = (nav_t){ kind, 0, 0, arg };

    switch (kind) {
    case MENU_SONGS:
        curlen = 0;
        for (int i = 0; i < ntracks; i++)
            curlist[curlen++] = i;
        break;
    case MENU_ARTIST_SONGS:
        curlen = 0;
        for (int i = 0; i < ntracks; i++)
            if (strcmp(tracks[i].artist, artists[arg]) == 0)
                curlist[curlen++] = i;
        break;
    case MENU_ALBUM_SONGS:
        curlen = 0;
        for (int i = 0; i < ntracks; i++)
            if (strcmp(tracks[i].album, albums[arg]) == 0)
                curlist[curlen++] = i;
        break;
    }
}

static int frame_count(const nav_t *d)
{
    switch (d->screen) {
    case MENU_MAIN:     return N_MAIN_ITEMS;
    case MENU_ARTISTS:  return nartists;
    case MENU_ALBUMS:   return nalbums;
    case MENU_SETTINGS: return 1;
    case MENU_THEMES:   return IPOD_NTHEMES;
    case MENU_GAMES:    return 4;
    default:            return curlen;
    }
}

static const char *label_of(int i, void *ctx)
{
    static char buf[48];
    const nav_t *d = ctx;

    switch (d->screen) {
    case MENU_MAIN:
        return MAIN_ITEMS[i];
    case MENU_ARTISTS:
        return artists[i];
    case MENU_ALBUMS:
        return albums[i];
    case MENU_SETTINGS:
        snprintf(buf, sizeof buf, "Theme: %s", ui_theme_name());
        return buf;
    case MENU_THEMES:
        snprintf(buf, sizeof buf, "%s%s", IPOD_THEMES[i].name,
                 i == ui_theme_index() ? "  *" : "");
        return buf;
    case MENU_GAMES:
        return GAMES[i]->name;
    default:
        return tracks[curlist[i]].title;
    }
}

/* Rows that open a submenu get a ">" arrow. */
static int arrow_of(int i, void *ctx)
{
    const nav_t *d = ctx;

    switch (d->screen) {
    case MENU_MAIN:
        return (unsigned)i <= 2 || i == 5 || i == 6;
    case MENU_ARTISTS:
    case MENU_ALBUMS:
    case MENU_SETTINGS:
        return 1;
    default:
        return 0;
    }
}

static const char *menu_title(const nav_t *d)
{
    switch (d->screen) {
    case MENU_MAIN:         return "iPod";
    case MENU_SONGS:        return "Songs";
    case MENU_ARTISTS:      return "Artists";
    case MENU_ALBUMS:       return "Albums";
    case MENU_ARTIST_SONGS: return artists[d->arg];
    case MENU_ALBUM_SONGS:  return albums[d->arg];
    case MENU_SETTINGS:     return "Settings";
    case MENU_THEMES:       return "Theme";
    case MENU_GAMES:        return "Games";
    default:                return "";
    }
}

/* Draw the current menu into g_mfb and present it. A single-step selection
 * change only repaints the two affected rows and the scrollbar; anything
 * else (scroll, new menu, theme, play state) repaints the whole menu. */
static void render_menu(void)
{
    nav_t *d = &nav[navdepth - 1];
    int n  = frame_count(d);
    int th = ui_theme_index();

    if (m_psel < 0 || m_pk != d->screen || m_ptop != d->top ||
        m_pflt != d->arg || m_pth != th || m_pps != g_ps || m_pn != n) {
        ui_menu(g_mfb, menu_title(d), n, d->sel, d->top, label_of, arrow_of, d);
    } else if (m_psel != d->sel) {
        ui_menu_row(g_mfb, m_psel - m_ptop, n, d->sel, m_ptop,
                    label_of, arrow_of, d);
        ui_menu_row(g_mfb, d->sel - d->top, n, d->sel, d->top,
                    label_of, arrow_of, d);
        ui_menu_scrollbar(g_mfb, n, d->top);
    }

    memcpy(of_video_surface16(), g_mfb, sizeof g_mfb);
    of_video_flip();

    m_pk   = d->screen;
    m_ptop = d->top;
    m_psel = d->sel;
    m_pflt = d->arg;
    m_pps  = g_ps;
    m_pn   = n;
    m_pth  = th;
}

/* ---- player ------------------------------------------------------------ */

/* Load art/<file-without-extension>.bin, or the placeholder. */
static void load_art(const track_t *t)
{
    char base[64], path[72];

    snprintf(base, sizeof base, "%s", t->file);
    char *dot = strrchr(base, '.');
    if (dot)
        *dot = '\0';
    snprintf(path, sizeof path, "art/%s.bin", base);

    FILE *f = open_any(path);
    if (!f)
        f = open_any("art/placeholder.bin");
    P.art = NULL;
    if (f) {
        size_t n = fread(g_artsrc, 2, ART_SRC * ART_SRC, f);
        fclose(f);
        if (n == ART_SRC * ART_SRC)
            P.art = g_artsrc;
    }
}

/* Start playing queue[qpos]. Only the first FIRST_READ bytes are read here;
 * player_pump() streams in the rest while the track plays. */
static void player_load_current(void)
{
    if (P.active)
        drmp3_uninit(&P.mp3);
    if (P.f) {
        fclose(P.f);
        P.f = NULL;
    }

    const track_t *t = &tracks[queue[qpos]];
    P.active = 0;
    P.loaded = 0;
    P.size   = 0;
    P.eof    = 0;
    P.paused = 0;
    P.frames = 0;

    load_art(t);

    P.gain = t->gain;
    if (P.gain < 1)
        P.gain = GAIN_UNITY;

    P.f = open_any(t->file);
    if (!P.f)
        return;

    fseek(P.f, 0, SEEK_END);
    uint32_t size = ftell(P.f);
    fseek(P.f, 0, SEEK_SET);
    if (size - 1 >= sizeof filebuf) {        /* empty or too big */
        fclose(P.f);
        P.f = NULL;
        return;
    }

    P.size   = size;
    P.loaded = fread(filebuf, 1, size < FIRST_READ ? size : FIRST_READ, P.f);
    if (P.loaded >= P.size) {
        fclose(P.f);
        P.f = NULL;
    }

    if (!drmp3_init_memory_with_metadata(&P.mp3, filebuf, P.size,
                                         NULL, NULL, NULL)) {
        if (P.f) {
            fclose(P.f);
            P.f = NULL;
        }
        return;
    }

    P.dur = t->dur;
    if (P.dur < 1)
        P.dur = P.size / FALLBACK_BPS;
    P.active = 1;
}

static void play_next(void)
{
    if (qlen) {
        qpos = (qpos + 1) % qlen;
        player_load_current();
    }
}

static void play_prev(void)
{
    if (qlen) {
        qpos = (qpos - 1 + qlen) % qlen;
        player_load_current();
    }
}

/* Keep the audio FIFO topped up to g_target frames. Called every frame. */
static void player_pump(void)
{
    if (!P.active || P.paused)
        return;

    /* Progressive load: stream the rest of the file in behind the decoder. */
    if (P.f && P.loaded < P.size) {
        size_t want = P.size - P.loaded;
        if (want > STREAM_READ)
            want = STREAM_READ;
        size_t got = fread(filebuf + P.loaded, 1, want, P.f);
        P.loaded += got;
        if (P.loaded >= P.size || got == 0) {
            fclose(P.f);
            P.f = NULL;
        }
    }

    if (P.eof) {
        /* Decoder finished: advance once the FIFO has drained. */
        if (of_audio_free() >= g_ring - DECODE_FRAMES)
            play_next();
        return;
    }

    for (int i = 0; i < DECODE_CHUNKS; i++) {
        if (of_audio_free() < DECODE_FRAMES)
            break;
        if (g_ring - of_audio_free() >= g_target)
            break;

        drmp3_uint64 n = drmp3_read_pcm_frames_s16(&P.mp3, DECODE_FRAMES, chunk);
        if (n == 0) {
            P.eof = 1;
            break;
        }

        /* Track gain and volume folded into one Q8 multiply. */
        int mul = P.gain * g_vol / 100;
        if (mul != GAIN_UNITY) {
            for (int k = 0; k < (int)n * 2; k++) {
                int v = chunk[k] * mul >> 8;
                if (v > 32767)  v = 32767;
                if (v < -32768) v = -32768;
                chunk[k] = (int16_t)v;
            }
        }

        of_audio_write(chunk, (int)n);
        P.frames += n;
        if (n < DECODE_FRAMES) {
            P.eof = 1;
            break;
        }
    }
}

static void shuffle_all(void)
{
    int order[MAX_TRACKS];

    if (ntracks < 1)
        return;
    for (int i = 0; i < ntracks; i++)
        order[i] = i;
    for (int i = ntracks - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    qlen = ntracks;
    for (int i = 0; i < qlen; i++)
        queue[i] = order[i];
    qpos = 0;
    player_load_current();
}

/* ---- Now Playing ------------------------------------------------------- */

/* Does any of the title/artist/album lines overflow and marquee-scroll? */
static int np_scrolling(void)
{
    if (!P.active)
        return 0;
    const track_t *t = &tracks[queue[qpos]];
    return ui_text_w(t->title) > NP_TW || ui_text_w(t->artist) > NP_TW ||
           ui_text_w(t->album) > NP_TW;
}

static void render_np(uint32_t t_ms)
{
    uint16_t *fb = of_video_surface16();

    if (!P.active) {
        ui_clear(fb, ui_bg());
        ui_status_bar(fb, "Now Playing", 100);
        ui_text(fb, UI_S(9), UI_S(110), "Nothing playing", ui_fg());
    } else {
        const track_t *t = &tracks[queue[qpos]];
        ui_now_playing(fb, t->title, t->artist, t->album, qpos + 1, qlen,
                       (int)(P.frames / SAMPLE_RATE), P.dur, P.art, 100,
                       P.paused, t_ms);

        if (of_time_ms() < g_vol_until) {
            char pct[8];
            ui_fill(fb, UI_S(8), UI_S(186), UI_S(304), UI_S(45), ui_bg());
            ui_text(fb, UI_S(16), UI_S(192), "Volume", ui_fg());
            snprintf(pct, sizeof pct, "%d%%", g_vol);
            ui_text_right(fb, UI_S(304), UI_S(192), pct, ui_fg());
            ui_fill(fb, UI_S(17), UI_S(213), UI_S(286), UI_S(11), ui_fg());
            ui_fill(fb, UI_S(18), UI_S(214), UI_S(284), UI_S(9), ui_bg());
            ui_fill(fb, UI_S(18), UI_S(214), g_vol * UI_S(284) / 100, UI_S(9),
                    ui_fg());
        }
    }
    of_video_flip();
}

/* ---- Music Quiz -------------------------------------------------------- */

#define MQ_CHOICES   5
#define MQ_HILITE    0x3bf9
#define MQ_RIGHT     0x2fec
#define MQ_WRONG     0xf986
#define MQ_HINT      0x8c71
#define MQ_REVEAL_MS 1500

/* Pick a random answer plus up to four distinct decoys, shuffle them and
 * start playing the answer. */
static void mq_new(void)
{
    int answer = rand() % ntracks;

    mq_choice[0] = answer;
    mq_n = 1;
    while (mq_n < MQ_CHOICES && mq_n < ntracks) {
        int c = rand() % ntracks;
        int dup = 0;
        for (int i = 0; i < mq_n; i++)
            dup |= mq_choice[i] == c;
        if (!dup)
            mq_choice[mq_n++] = c;
    }
    for (int i = mq_n; i > 1; i--) {
        int j = rand() % i;
        int tmp = mq_choice[i - 1];
        mq_choice[i - 1] = mq_choice[j];
        mq_choice[j] = tmp;
    }

    mq_correct = 0;
    for (int i = 0; i < mq_n; i++)
        if (mq_choice[i] == answer)
            mq_correct = i;
    mq_sel = 0;
    mq_reveal = 0;

    queue[0] = answer;
    qlen = 1;
    qpos = 0;
    player_load_current();
}

static void mq_reset(void)
{
    mq_score = 0;
    mq_total = 0;
    if (ntracks > 0)
        mq_new();
}

static int mq_step(uint16_t *fb)
{
    char buf[32];

    if (of_btn_pressed(OF_BTN_B))
        return 1;

    if (ntracks < 2) {
        ui_clear(fb, ui_bg());
        ui_status_bar(fb, "Music Quiz", 100);
        ui_text(fb, UI_S(9), UI_S(110), "Need more songs", ui_fg());
        return 0;
    }

    if (!mq_reveal) {
        if (of_btn_pressed(OF_BTN_DOWN) && mq_sel < mq_n - 1)
            mq_sel++;
        if (of_btn_pressed(OF_BTN_UP) && mq_sel > 0)
            mq_sel--;
        if (of_btn_pressed(OF_BTN_A)) {
            mq_total++;
            if (mq_sel == mq_correct)
                mq_score++;
            mq_reveal = 1;
            mq_reveal_until = of_time_ms() + MQ_REVEAL_MS;
        }
    } else if (of_time_ms() >= mq_reveal_until || of_btn_pressed(OF_BTN_A)) {
        mq_new();
    }

    ui_clear(fb, ui_bg());
    ui_status_bar(fb, "Music Quiz", 100);
    snprintf(buf, 28, "Score %d / %d", mq_score, mq_total);
    ui_text(fb, UI_S(9), UI_S(28), buf, ui_fg());
    ui_text(fb, UI_S(9), UI_S(50), "Guess the song:", ui_fg());

    for (int i = 0; i < mq_n; i++) {
        int y = UI_S(76) + i * UI_S(30);
        uint16_t c = ui_fg();
        if (i == mq_sel) {
            if (!mq_reveal) {
                ui_fill(fb, 0, y - UI_S(4), UI_W, UI_S(26), MQ_HILITE);
                c = 0xffff;
            } else {
                c = i == mq_correct ? MQ_RIGHT : MQ_WRONG;
            }
        } else if (mq_reveal && i == mq_correct) {
            c = MQ_RIGHT;
        }
        ui_text_clip(fb, UI_S(12), y, UI_S(296), tracks[mq_choice[i]].title, c);
    }

    ui_text_center(fb, UI_S(160), UI_S(224),
                   mq_reveal ? "A: next      B: exit" : "Up/Down + A      B: exit",
                   MQ_HINT);
    return 0;
}

/* ---- startup ----------------------------------------------------------- */

/* Parse playlist.tsv: file, title, artist, album[, dur[, gain]].
 * Over-long fields are truncated to fit track_t on purpose. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-truncation"
static void load_playlist(void)
{
    FILE *f = open_any(PLAYLIST);
    if (!f)
        return;
    size_t len = fread(plbuf, 1, sizeof plbuf - 1, f);
    fclose(f);
    plbuf[len] = '\0';

    char *line = plbuf;
    while (*plbuf && ntracks < MAX_TRACKS) {
        char *nl = strchr(line, '\n');
        if (nl)
            *nl = '\0';
        char *cr = strchr(line, '\r');
        if (cr)
            *cr = '\0';

        char *field[6] = { line };
        int nf = 1;
        for (char *p = line; *p; p++) {
            if (*p == '\t') {
                *p = '\0';
                field[nf++] = p + 1;
                if (nf == 6)
                    break;
            }
        }

        if (nf >= 4) {
            track_t *t = &tracks[ntracks++];
            snprintf(t->file,   sizeof t->file,   "%s", field[0]);
            snprintf(t->title,  sizeof t->title,  "%s", field[1]);
            snprintf(t->artist, sizeof t->artist, "%s", field[2]);
            snprintf(t->album,  sizeof t->album,  "%s", field[3]);
            t->dur  = nf > 4 ? atoi(field[4]) : 0;
            t->gain = nf > 5 ? atoi(field[5]) : GAIN_UNITY;
            add_unique(artists, &nartists, t->artist);
            add_unique(albums, &nalbums, t->album);
        }

        if (!nl || nl[1] == '\0')
            break;
        line = nl + 1;
    }

    qsort(artists, nartists, NAME_LEN, cmpstr);
    qsort(albums, nalbums, NAME_LEN, cmpstr);
}
#pragma GCC diagnostic pop

static void video_setup(void)
{
    of_video_mode_t mode = { UI_W, UI_H, 0, OF_VIDEO_MODE_RGB565, 0 };

    of_video_init();
    if (of_video_set_mode(&mode) != 0)       /* older OS: 320x240 RGB565 */
        of_video_set_color_mode(OF_VIDEO_MODE_RGB565);
    of_video_set_display_mode(OF_DISPLAY_FRAMEBUFFER);
}

/* Hold the boot splash for BOOT_MS, filling the progress bar. */
static void boot_splash(void)
{
    uint32_t t0 = of_time_ms();

    for (;;) {
        uint32_t pct = (of_time_ms() - t0) * 100 / BOOT_MS;
        if (pct > 100)
            pct = 100;
        ui_boot(of_video_surface16(), pct);
        of_video_flip();
        if (pct == 100)
            break;
        usleep(16000);
    }
}

static void no_tracks(void)
{
    uint16_t *fb = of_video_surface16();

    ui_clear(fb, ui_bg());
    ui_status_bar(fb, "PocketTunes", 100);
    ui_text(fb, UI_S(9), UI_S(110), "No tracks found in music.iso", ui_fg());
    of_video_flip();
    for (;;)
        usleep(100000);
}

/* ---- main loop --------------------------------------------------------- */

/* Menu selection with A. */
static void menu_select(nav_t *d)
{
    int sel = d->sel;

    switch (d->screen) {
    case MENU_MAIN:
        switch (sel) {
        case 0: nav_push(MENU_SONGS, 0);    break;
        case 1: nav_push(MENU_ARTISTS, 0);  break;
        case 2: nav_push(MENU_ALBUMS, 0);   break;
        case 3: shuffle_all();              /* fall through */
        case 4:
            if (P.active)
                screen = SCR_NOW_PLAYING;
            break;
        case 5: nav_push(MENU_GAMES, 0);    break;
        case 6: nav_push(MENU_SETTINGS, 0); break;
        }
        break;
    case MENU_ARTISTS:
        nav_push(MENU_ARTIST_SONGS, sel);
        break;
    case MENU_ALBUMS:
        nav_push(MENU_ALBUM_SONGS, sel);
        break;
    case MENU_SETTINGS:
        nav_push(MENU_THEMES, 0);
        break;
    case MENU_THEMES:
        ui_set_theme(sel);
        break;
    case MENU_GAMES:
        cur_game = GAMES[sel];
        cur_game->reset();
        screen = SCR_GAME;
        break;
    default:                                /* a song list: queue it all */
        if (curlen > 0) {
            memcpy(queue, curlist, curlen * sizeof curlist[0]);
            qlen = curlen;
            if (sel < 0)
                sel = 0;
            else if (sel >= curlen)
                sel = curlen - 1;
            qpos = sel;
            player_load_current();
        }
        screen = SCR_NOW_PLAYING;
        break;
    }
}

int main(void)
{
    video_setup();
    ui_boot(of_video_surface16(), 0);
    of_video_flip();

    of_audio_init();
    g_ring = of_audio_free();
    of_audio_stream_open(SAMPLE_RATE);

    of_iso_mount(MUSIC_ISO, MUSIC_DIR);
    load_playlist();

    srand(of_time_ms() | 1);
    boot_splash();
    if (ntracks == 0)
        no_tracks();

    nav[0] = (nav_t){ MENU_MAIN, 0, 0, 0 };
    navdepth = 1;

    int rows       = ui_visible_rows();
    int dirty      = 1;           /* menu needs a redraw */
    int prev_ps    = -1;
    int np_pos     = -2;          /* last drawn NP position (s); -2 = force */
    int last_qpos  = -1;
    uint32_t track_t0 = 0;        /* when the shown track started (marquee clock) */

    for (;;) {
        of_input_poll();

        /* Deeper cushion when the screen redraws every frame (games,
         * scrolling marquee) so drawing can't starve the audio. */
        if (screen == SCR_GAME || (screen == SCR_NOW_PLAYING && np_scrolling()))
            g_target = CUSHION_DEEP;
        else
            g_target = CUSHION_SHORT;
        player_pump();

        g_ps = !P.active ? 0 : P.paused ? 2 : 1;
        ui_set_playstate(g_ps);
        if (g_ps != prev_ps) {
            dirty |= screen == SCR_MENU;
            np_pos = -2;
        }
        prev_ps = g_ps;

        /* Transport keys work on every screen except inside a game. */
        if (screen != SCR_GAME && P.active) {
            if (of_btn_pressed(OF_BTN_START)) {
                dirty |= screen == SCR_MENU;
                P.paused = !P.paused;
                np_pos = -2;
            }
            if (of_btn_pressed(OF_BTN_SELECT)) {
                screen = SCR_NOW_PLAYING;
                np_pos = -2;
            }
            if (of_btn_pressed(OF_BTN_R1)) {
                play_next();
                np_pos = -2;
            }
            if (of_btn_pressed(OF_BTN_L1) && P.active) {
                play_prev();
                np_pos = -2;
            }
        }

        if (screen == SCR_MENU) {
            nav_t *d = &nav[navdepth - 1];
            int n = frame_count(d);

            if (of_btn_pressed(OF_BTN_DOWN) && d->sel < n - 1) {
                d->sel++;
                dirty = 1;
            }
            if (of_btn_pressed(OF_BTN_UP) && d->sel > 0) {
                d->sel--;
                dirty = 1;
            }
            if (!P.active) {                  /* L1/R1 page through lists */
                if (of_btn_pressed(OF_BTN_R1)) {
                    d->sel += rows;
                    if (d->sel >= n)
                        d->sel = n - 1;
                    dirty = 1;
                }
                if (of_btn_pressed(OF_BTN_L1)) {
                    d->sel -= rows;
                    if (d->sel < 0)
                        d->sel = 0;
                    dirty = 1;
                }
            }
            if (dirty) {                      /* keep the selection visible */
                if (d->sel < d->top)
                    d->top = d->sel;
                if (d->sel >= d->top + rows)
                    d->top = d->sel - rows + 1;
            }

            if (of_btn_pressed(OF_BTN_A)) {
                menu_select(d);
                if (screen != SCR_MENU)
                    np_pos = -2;
                dirty = 1;
            }
            if (of_btn_pressed(OF_BTN_B) && navdepth > 1) {
                navdepth--;
                dirty = 1;
            }

            if (screen == SCR_MENU && dirty) {
                render_menu();
                dirty = 0;
            }
            usleep(5000);
        } else if (screen == SCR_NOW_PLAYING) {
            if (of_btn_pressed(OF_BTN_B)) {
                screen = SCR_MENU;
                usleep(8000);
                dirty = 1;
                continue;
            }

            if (of_btn_pressed(OF_BTN_RIGHT)) {
                np_pos = -2;
                play_next();
            }
            if (of_btn_pressed(OF_BTN_LEFT)) {
                np_pos = -2;
                play_prev();
            }
            if (of_btn_pressed(OF_BTN_UP)) {
                g_vol += VOL_STEP;
                if (g_vol > 100)
                    g_vol = 100;
                g_vol_until = of_time_ms() + VOL_OSD_MS;
            }
            if (of_btn_pressed(OF_BTN_DOWN)) {
                g_vol -= VOL_STEP;
                if (g_vol < 0)
                    g_vol = 0;
                g_vol_until = of_time_ms() + VOL_OSD_MS;
            }

            /* The marquee clock restarts on a new track and holds still
             * while the file is still streaming in. */
            if (qpos != last_qpos)
                track_t0 = of_time_ms();
            int loading = P.f && P.loaded < P.size;
            if (loading)
                track_t0 = of_time_ms();
            uint32_t t_ms = of_time_ms() - track_t0;
            int pos = P.active ? (int)(P.frames / SAMPLE_RATE) : 0;

            uint32_t now = of_time_ms();
            if (now < g_vol_until || g_vol_prev) {
                /* Volume overlay up (or just closed): redraw at ~30 fps. */
                render_np(t_ms);
                g_vol_prev = now < g_vol_until;
                usleep(33000);
                np_pos = -2;
            } else if (P.active && np_scrolling() && !loading) {
                render_np(t_ms);
                usleep(40000);
            } else {
                /* Static screen: redraw only when the elapsed second ticks. */
                if (np_pos != pos) {
                    render_np(t_ms);
                    np_pos = pos;
                }
                usleep(8000);
            }
            last_qpos = qpos;
        } else {
            uint16_t *fb = of_video_surface16();
            if (cur_game && cur_game->step(fb)) {
                screen = SCR_MENU;
                dirty = 1;
            }
            of_video_flip();
            usleep(16000);
        }
    }
}
