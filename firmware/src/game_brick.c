/* game_brick.c — Brick: Breakout-style paddle and ball game. */
#include "game.h"
#include "ipod_ui.h"
#include "of.h"

#include <stdlib.h>
#include <string.h>

/* Positions and velocities are 24.8 fixed point (ball_x, ball_y, ball_vx/vy). */
#define BALL_SPEED  UI_S(0x300)     /* vertical speed, 3 px/frame at 1x */
#define BALL_R      UI_S(2)
#define PADDLE_SPD  UI_S(5)
#define PADDLE_W    UI_S(46)
#define PADDLE_H    UI_S(6)
#define PADDLE_Y    UI_S(222)
#define PADDLE_X0   UI_S(137)       /* start position */
#define WALL        UI_S(8)         /* side margin the ball and paddle stay inside */
#define TOP         UI_S(24)        /* playfield top, just under the HUD rule */

#define ROWS        5
#define COLS        8
#define BRICK_X     UI_S(10)
#define BRICK_Y     UI_S(40)
#define BRICK_H     UI_S(12)
#define BRICK_GAP   UI_S(2)
#define ROW_H       (BRICK_H + UI_S(2))

#define BG_TOP      0x108a

enum { ST_SERVE, ST_PLAY, ST_OVER, ST_WIN };

static uint16_t rowcol[ROWS];
static uint8_t bricks[ROWS][COLS];
static int score, lives, state, paused, paddle_x, brick_w, bricks_left;
static int ball_x, ball_y, ball_vx, ball_vy;

static void serve(void)
{
    paddle_x = PADDLE_X0;
    ball_x = (UI_W / 2) << 8;
    ball_y = (PADDLE_Y - 2 * BALL_R - 1) << 8;
    ball_vx = 0;
    ball_vy = 0;
    state = ST_SERVE;
}

static void brick_reset(void)
{
    rowcol[0] = 0xf908;
    rowcol[1] = 0xfd06;
    rowcol[2] = 0xe746;
    rowcol[3] = 0x464c;
    rowcol[4] = 0x431f;
    score = 0;
    lives = 3;
    paused = 0;
    brick_w = (UI_W - 2 * BRICK_X - (COLS - 1) * BRICK_GAP) / COLS;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++) bricks[r][c] = 1;
    bricks_left = ROWS * COLS;
    serve();
}

static void draw_overlay_center(uint16_t *fb, const char *title, const char *sub, uint16_t tc)
{
    ui_fill(fb, UI_S(50), UI_S(85), UI_S(220), UI_S(70), 0x0004);
    ui_fill(fb, UI_S(50), UI_S(85), UI_S(220), UI_S(1), 0xa512);
    ui_fill(fb, UI_S(50), UI_S(154), UI_S(220), UI_S(1), 0xa512);
    ui_fill(fb, UI_S(50), UI_S(85), UI_S(1), UI_S(70), 0xa512);
    ui_fill(fb, UI_S(269), UI_S(85), UI_S(1), UI_S(70), 0xa512);
    ui_text_center(fb, UI_W / 2, UI_S(99), title, tc);
    ui_text_center(fb, UI_W / 2, UI_S(125), sub, 0xffff);
}

/* Decimal digits of v (at most 7); "0" for zero, empty for negative. */
static void fmt_int(char *out, int v)
{
    char tmp[8];
    int n = 0;

    if (v == 0) {
        strcpy(out, "0");
        return;
    }
    while (v > 0 && n < 7) {
        tmp[n++] = '0' + v % 10;
        v /= 10;
    }
    for (int i = 0; i < n; i++) out[i] = tmp[n - 1 - i];
    out[n] = '\0';
}

/* Move the ball one frame and handle walls, paddle, bricks and misses. */
static void move_ball(void)
{
    ball_x += ball_vx;
    int bx = ball_x / 256;
    int ny = ball_y + ball_vy;

    if (bx - BALL_R <= WALL) {
        ball_vx = -ball_vx;
        bx = WALL + BALL_R;
        ball_x = bx << 8;
    } else if (bx + BALL_R >= UI_W - WALL) {
        ball_vx = -ball_vx;
        bx = UI_W - WALL - BALL_R;
        ball_x = bx << 8;
    }

    if (ny / 256 - BALL_R <= TOP) {
        ball_vy = -ball_vy;
        ball_y = (TOP + BALL_R) << 8;
        return;
    }
    ball_y = ny;
    int by = ny / 256;

    if (ball_vy > 0 && by + BALL_R >= PADDLE_Y && by - BALL_R <= PADDLE_Y + PADDLE_H) {
        if (bx + BALL_R >= paddle_x && bx - BALL_R <= paddle_x + PADDLE_W) {
            /* Bounce angle follows where the ball hit the paddle. */
            ball_y = (PADDLE_Y - BALL_R - 1) << 8;
            ball_vy = -BALL_SPEED;
            ball_vx = (bx - (paddle_x + PADDLE_W / 2)) * BALL_SPEED / (PADDLE_W / 2);
            return;
        }
    } else if (by + BALL_R > BRICK_Y && by - BALL_R < BRICK_Y + ROWS * ROW_H) {
        int hit = 0;
        for (int r = 0; r < ROWS && !hit; r++) {
            int ry = BRICK_Y + r * ROW_H;
            if (by + BALL_R <= ry || by - BALL_R >= ry + BRICK_H) continue;
            for (int c = 0; c < COLS; c++) {
                int cx = BRICK_X + c * (brick_w + BRICK_GAP);
                if (!bricks[r][c] || bx + BALL_R <= cx || bx - BALL_R >= cx + brick_w)
                    continue;
                /* Side hit if the ball is further out horizontally than vertically. */
                int dy = abs(by - (ry + BRICK_H / 2));
                int dx = abs(bx - (cx + brick_w / 2));
                if (dy * (brick_w / 2) < dx * (BRICK_H / 2))
                    ball_vx = -ball_vx;
                else
                    ball_vy = -ball_vy;
                bricks[r][c] = 0;
                score += (ROWS - r) * 10;
                if (--bricks_left == 0) state = ST_WIN;
                hit = 1;
                break;
            }
        }
    }

    if (by > UI_H) {
        if (--lives < 1)
            state = ST_OVER;
        else
            serve();
    }
}

static int brick_step(uint16_t *fb)
{
    if (of_btn_pressed(OF_BTN_B)) return 1;

    if (of_btn_pressed(OF_BTN_START) && state < ST_OVER) paused = !paused;

    if (state == ST_OVER || state == ST_WIN) {
        if (of_btn_pressed(OF_BTN_A)) brick_reset();
    } else if (!paused) {
        if (of_btn(OF_BTN_LEFT)) paddle_x -= PADDLE_SPD;
        if (of_btn(OF_BTN_RIGHT)) paddle_x += PADDLE_SPD;
        if (paddle_x < WALL)
            paddle_x = WALL;
        else if (paddle_x > UI_W - WALL - PADDLE_W)
            paddle_x = UI_W - WALL - PADDLE_W;

        if (state == ST_SERVE) {
            ball_x = (paddle_x + PADDLE_W / 2) << 8;
            ball_y = (PADDLE_Y - 2 * BALL_R - 1) << 8;
            if (of_btn_pressed(OF_BTN_A)) {
                ball_vx = (rand() & 1) ? BALL_SPEED / 2 : -BALL_SPEED / 2;
                ball_vy = -BALL_SPEED;
                state = ST_PLAY;
            }
        } else {
            move_ball();
        }
    }

    /* HUD */
    char num[8], buf[24];
    ui_vgrad(fb, 0, 0, UI_W, UI_H, BG_TOP, 0x0002);
    fmt_int(num, score);
    strcpy(buf, "SCORE ");
    strcat(buf, num);
    ui_text(fb, UI_S(8), UI_S(3), buf, 0xffff);
    strcpy(buf, "LIVES ");
    buf[6] = '0' + (lives < 0 ? 0 : lives);
    buf[7] = '\0';
    ui_text_right(fb, UI_S(312), UI_S(3), buf, 0xfe54);
    ui_fill(fb, 0, UI_S(23), UI_W, UI_S(1), 0xa512);

    /* Bricks: body in the row colour, light top edge, dark bottom edge. */
    for (int r = 0; r < ROWS; r++) {
        int y = BRICK_Y + r * ROW_H;
        for (int c = 0; c < COLS; c++) {
            if (!bricks[r][c]) continue;
            int x = BRICK_X + c * (brick_w + BRICK_GAP);
            ui_fill(fb, x, y, brick_w, BRICK_H, rowcol[r]);
            ui_fill(fb, x, y, brick_w, UI_S(1), 0xffff);
            ui_fill(fb, x, y + BRICK_H - UI_S(1), brick_w, UI_S(1), 0x1086);
        }
    }

    /* Paddle with highlight, shadow and clipped-off corners. */
    ui_fill(fb, paddle_x, PADDLE_Y, PADDLE_W, PADDLE_H, 0xa65f);
    ui_fill(fb, paddle_x + UI_S(1), PADDLE_Y, PADDLE_W - UI_S(2), UI_S(1), 0xffff);
    ui_fill(fb, paddle_x + UI_S(1), PADDLE_Y + PADDLE_H - UI_S(1), PADDLE_W - UI_S(2), UI_S(1), 0x430e);
    for (int i = 0; i < 2; i++) {
        unsigned x = paddle_x + i * (PADDLE_W - 1);
        if (x < UI_W) {
            fb[PADDLE_Y * UI_W + x] = BG_TOP;
            fb[(PADDLE_Y + PADDLE_H - 1) * UI_W + x] = BG_TOP;
        }
    }

    /* Ball */
    int bx = ball_x / 256, by = ball_y / 256;
    for (int y = by - BALL_R; y < by + BALL_R; y++) {
        if ((unsigned)y >= UI_H) continue;
        for (int x = bx - BALL_R; x < bx + BALL_R; x++)
            if ((unsigned)x < UI_W) fb[y * UI_W + x] = 0xff9f;
    }

    if (state == ST_SERVE && !paused)
        ui_text_center(fb, UI_W / 2, UI_S(188), "PRESS A TO LAUNCH", 0xe712);
    if (paused)
        draw_overlay_center(fb, "PAUSED", "START to resume", 0xffff);
    if (state == ST_OVER)
        draw_overlay_center(fb, "GAME OVER", "A restart   B exit", 0xf988);
    if (state == ST_WIN)
        draw_overlay_center(fb, "YOU WIN", "A restart   B exit", 0xe74a);
    return 0;
}

const game_t GAME_BRICK = {"Brick", brick_reset, brick_step};
