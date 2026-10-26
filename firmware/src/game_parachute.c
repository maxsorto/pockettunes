/* game_parachute.c — Parachute: aim a ground turret and shoot down paratroopers and helicopters. */
#include "game.h"
#include "ipod_ui.h"
#include "of.h"

#include <stdlib.h>
#include <string.h>

/* Positions and velocities are fixed point, 16 units per pixel. */
#define FP          16
#define NBULLETS    8
#define NTROOPS     12
#define NAIM        13

/* Speeds in 1/16 px per frame, tuned at 640x480 (UI_SCALE 2). */
#define SPD(v)          ((v) * UI_SCALE / 2)
#define BULLET_SPEED    UI_S(96)    /* times the unit aim vector (256) */

#define GROUND_Y    UI_S(224)
#define LAND_Y      UI_S(220)       /* a troop this low has landed */
#define GUN_X       (UI_W / 2)
#define GUN_Y       UI_S(222)
#define GUN_LEN     UI_S(22)
#define MUZZLE      UI_S(18)        /* bullets spawn this far along the barrel */
#define EDGE        UI_S(14)        /* troops bounce off the screen sides here */

#define SPAWN_START 110
#define SPAWN_MIN   35
#define SPAWN_STEP  8
#define SPEEDUP_FRAMES 360
#define REPEAT_FRAMES  7            /* held left/right turns the gun this often */

typedef struct {
    int alive;
    int x, y, vx, vy;
} bullet_t;

typedef struct {
    int alive;
    int x, y, vx, vy;
    int heli;       /* helicopter instead of a paratrooper */
    int anim;       /* frames alive, drives the rotor flicker */
} troop_t;

/* Unit aim vectors (x256), from hard left to hard right. */
static const int aim_dx[NAIM] = {-247, -221, -181, -128, -66, -34, 0, 34, 66, 128, 181, 221, 247};
static const int aim_dy[NAIM] = {-66, -128, -181, -221, -247, -253, -256, -253, -247, -221, -181, -128, -66};

static bullet_t bullets[NBULLETS];
static troop_t troops[NTROOPS];
static int aim, score, lives, gameover, frame, spawn_interval, spawn_timer;

static void para_reset(void)
{
    memset(bullets, 0, sizeof bullets);
    memset(troops, 0, sizeof troops);
    aim = NAIM / 2;
    score = 0;
    lives = 3;
    gameover = 0;
    frame = 0;
    spawn_interval = SPAWN_START;
    spawn_timer = 40;
}

static inline void plot(uint16_t *fb, int x, int y, uint16_t c)
{
    if ((unsigned)x < UI_W && (unsigned)y < UI_H) fb[y * UI_W + x] = c;
}

static void disc(uint16_t *fb, int cx, int cy, int r, uint16_t c)
{
    for (int dy = -r; dy <= r; dy++)
        for (int dx = -r; dx <= r; dx++)
            if (dx * dx + dy * dy <= r * r) plot(fb, cx + dx, cy + dy, c);
}

/* Bresenham line, clipped per pixel. */
static void line(uint16_t *fb, int x0, int y0, int x1, int y1, uint16_t c)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    for (;;) {
        plot(fb, x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

/* "SCORE n" into buf. */
static inline void score_text(char *buf)
{
    char tmp[12];
    int n = 0, v = score;

    if (v == 0) tmp[n++] = '0';
    while (v > 0) {
        tmp[n++] = '0' + v % 10;
        v /= 10;
    }
    strcpy(buf, "SCORE ");
    for (int i = 0; i < n; i++) buf[6 + i] = tmp[n - 1 - i];
    buf[6 + n] = '\0';
}

static void spawn_troop(void)
{
    for (int i = 0; i < NTROOPS; i++) {
        troop_t *t = &troops[i];
        if (t->alive) continue;
        t->alive = 1;
        t->heli = rand() % 100 < 35;
        t->x = (rand() % UI_S(280) + UI_S(20)) * FP;
        t->y = UI_S(8) * FP;
        t->anim = 0;
        int dir = (rand() & 1) ? 1 : -1;
        if (t->heli) {
            t->vx = SPD((rand() & 15) + 16) * dir;
            t->vy = SPD((rand() & 7) + 8);
        } else {
            t->vx = SPD(rand() % 12) * dir;
            t->vy = SPD(rand() % 12 + 14);
        }
        break;
    }
}

static void draw_heli(uint16_t *fb, const troop_t *t)
{
    int x = t->x / FP, y = t->y / FP;

    ui_fill(fb, x - UI_S(7), y - UI_S(3), UI_S(14), UI_S(7), 0x429f);     /* body */
    ui_fill(fb, x - UI_S(9), y - UI_S(1), UI_S(5), UI_S(4), 0x2198);      /* cockpit */
    ui_fill(fb, x + UI_S(6), y - UI_S(1), UI_S(9), UI_S(3), 0x2198);      /* tail boom */
    ui_fill(fb, x + UI_S(14), y - UI_S(4), UI_S(2), UI_S(6), 0x429f);     /* tail fin */
    line(fb, x - UI_S(6), y + UI_S(5), x + UI_S(6), y + UI_S(5), 0x2198); /* skid */
    /* Rotor alternates between long and short every 3 frames. */
    int r = (t->anim / 3 & 1) ? UI_S(12) : UI_S(7);
    line(fb, x - r, y - UI_S(5), x + r, y - UI_S(5), 0xd69a);
    plot(fb, x, y - UI_S(6), 0xd69a);
    plot(fb, x, y - UI_S(4), 0xd69a);
}

static void draw_trooper(uint16_t *fb, const troop_t *t)
{
    int x = t->x / FP, y = t->y / FP;

    /* Striped dome canopy, one column at a time, with a solid bottom rim. */
    for (int i = -UI_S(8); i <= UI_S(8); i++) {
        uint16_t c = (i & UI_S(4)) ? 0xfbce : 0xe108;
        int h = ((256 - i * i) * UI_S(7)) >> 8;
        for (int yy = y - UI_S(14); yy >= y - UI_S(14) - h; yy--) plot(fb, x + i, yy, c);
        plot(fb, x + i, y - UI_S(13), 0xe108);
    }
    line(fb, x - UI_S(6), y - UI_S(13), x, y - UI_S(4), 0xa514);
    line(fb, x + UI_S(6), y - UI_S(13), x, y - UI_S(4), 0xa514);
    disc(fb, x, y, UI_S(3), 0x33c8);
    plot(fb, x, y + UI_S(4), 0x33c8);
    plot(fb, x, y + UI_S(5), 0x33c8);
}

static int para_step(uint16_t *fb)
{
    char buf[24];

    if (of_btn_pressed(OF_BTN_B)) return 1;

    if (gameover) {
        if (!of_btn_pressed(OF_BTN_A)) {
            ui_vgrad(fb, 0, 0, UI_W, UI_H, 0x108a, 0x4218);
            ui_text_center(fb, UI_W / 2, UI_S(70), "GAME OVER", 0xfa94);
            score_text(buf);
            ui_text_center(fb, UI_W / 2, UI_S(105), buf, 0xffff);
            ui_text_center(fb, UI_W / 2, UI_S(150), "A = RESTART", 0xa654);
            ui_text_center(fb, UI_W / 2, UI_S(172), "B = EXIT", 0x4508);
            return 0;
        }
        para_reset();
    }
    frame++;
    spawn_timer--;

    /* Aim: one step per press, auto-repeat while held. */
    if (of_btn_pressed(OF_BTN_LEFT) && aim > 0) aim--;
    if (of_btn_pressed(OF_BTN_RIGHT) && aim < NAIM - 1) aim++;
    if (frame % REPEAT_FRAMES == 0) {
        if (of_btn(OF_BTN_LEFT) && aim > 0) aim--;
        if (of_btn(OF_BTN_RIGHT) && aim < NAIM - 1) aim++;
    }

    if (of_btn_pressed(OF_BTN_A | OF_BTN_X)) {
        for (int i = 0; i < NBULLETS; i++) {
            bullet_t *b = &bullets[i];
            if (b->alive) continue;
            b->alive = 1;
            b->x = (GUN_X + aim_dx[aim] * MUZZLE / 256) * FP;
            b->y = (GUN_Y + aim_dy[aim] * MUZZLE / 256) * FP;
            b->vx = aim_dx[aim] * BULLET_SPEED / 256;
            b->vy = aim_dy[aim] * BULLET_SPEED / 256;
            break;
        }
    }

    if (spawn_timer <= 0) {
        spawn_troop();
        spawn_timer = spawn_interval;
    }
    if (frame % SPEEDUP_FRAMES == 0 && spawn_interval > SPAWN_MIN) {
        spawn_interval -= SPAWN_STEP;
        if (spawn_interval < SPAWN_MIN) spawn_interval = SPAWN_MIN;
    }

    for (int i = 0; i < NBULLETS; i++) {
        bullet_t *b = &bullets[i];
        if (!b->alive) continue;
        b->x += b->vx;
        b->y += b->vy;
        int px = b->x / FP, py = b->y / FP;
        if (px < -UI_S(4) || px > UI_W + UI_S(4) || py < -UI_S(4) || py > UI_H + UI_S(4))
            b->alive = 0;
    }

    for (int i = 0; i < NTROOPS; i++) {
        troop_t *t = &troops[i];
        if (!t->alive) continue;
        t->x += t->vx;
        t->y += t->vy;
        t->anim++;
        if (t->x / FP < EDGE) {
            t->x = EDGE * FP;
            t->vx = -t->vx;
        } else if (t->x / FP > UI_W - EDGE) {
            t->x = (UI_W - EDGE) * FP;
            t->vx = -t->vx;
        }
        if (t->y / FP >= LAND_Y) {
            t->alive = 0;
            if (--lives <= 0) {
                lives = 0;
                gameover = 1;
            }
        }
    }

    for (int i = 0; i < NBULLETS; i++) {
        bullet_t *b = &bullets[i];
        if (!b->alive) continue;
        for (int j = 0; j < NTROOPS; j++) {
            troop_t *t = &troops[j];
            if (!t->alive) continue;
            int hw = t->heli ? UI_S(12) : UI_S(9);
            int hh = t->heli ? UI_S(8) : UI_S(16);
            if (abs(b->x / FP - t->x / FP) <= hw && abs(b->y / FP - t->y / FP) <= hh) {
                score += t->heli ? 25 : 10;
                b->alive = 0;
                t->alive = 0;
                break;
            }
        }
    }

    /* Sky and ground */
    ui_vgrad(fb, 0, 0, UI_W, UI_H, 0x331f, 0xa61f);
    ui_fill(fb, 0, GROUND_Y + UI_S(2), UI_W, UI_S(14), 0x3246);
    ui_fill(fb, 0, GROUND_Y, UI_W, UI_S(2), 0x534a);

    for (int i = 0; i < NTROOPS; i++) {
        if (!troops[i].alive) continue;
        if (troops[i].heli)
            draw_heli(fb, &troops[i]);
        else
            draw_trooper(fb, &troops[i]);
    }

    /* Turret */
    ui_fill(fb, GUN_X - UI_S(16), GROUND_Y, UI_S(32), UI_S(14), 0x738e);
    ui_fill(fb, GUN_X - UI_S(10), GUN_Y - UI_S(4), UI_S(20), UI_S(8), 0xb596);
    disc(fb, GUN_X, GUN_Y, UI_S(6), 0xb596);
    int ex = aim_dx[aim] * GUN_LEN / 256;
    int ey = GUN_Y + aim_dy[aim] * GUN_LEN / 256;
    line(fb, GUN_X, GUN_Y, GUN_X + ex, ey, 0xe71c);
    line(fb, GUN_X - UI_S(1), GUN_Y, GUN_X - UI_S(1) + ex, ey, 0xe71c);
    line(fb, GUN_X + UI_S(1), GUN_Y, GUN_X + UI_S(1) + ex, ey, 0xe71c);
    disc(fb, GUN_X + ex, ey, UI_S(1), 0xffff);

    for (int i = 0; i < NBULLETS; i++) {
        if (!bullets[i].alive) continue;
        int x = bullets[i].x / FP, y = bullets[i].y / FP;
        disc(fb, x, y, UI_S(2), 0xff94);
        plot(fb, x, y, 0xffff);
    }

    /* HUD with drop shadow */
    score_text(buf);
    ui_text(fb, UI_S(7), UI_S(7), buf, 0x0000);
    ui_text(fb, UI_S(6), UI_S(6), buf, 0xffff);
    strcpy(buf, "LIVES ");
    buf[6] = '0' + (lives < 0 ? 0 : lives);
    buf[7] = '\0';
    ui_text_right(fb, UI_S(314), UI_S(7), buf, 0x0000);
    ui_text_right(fb, UI_S(313), UI_S(6), buf, 0xffff);
    return 0;
}

const game_t GAME_PARACHUTE = {"Parachute", para_reset, para_step};
