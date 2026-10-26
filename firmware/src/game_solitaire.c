/* game_solitaire.c — Solitaire: Klondike, draw one, cursor-driven. */
#include "game.h"
#include "ipod_ui.h"
#include "of.h"

#include <stdlib.h>

/* Cards are suit * 13 + rank, rank 0 = ace. Suits: spade, heart, diamond, club. */
#define NCARDS  52
#define is_red(c)   ((unsigned)((c) - 13) < 26)

/* Piles: 0 stock, 1 waste, 2..5 foundations (one per suit), 6..12 tableau. */
#define STOCK   0
#define WASTE   1
#define FOUND   2
#define TAB     6
#define NPILES  13

#define CARD_W      UI_S(30)
#define CARD_H      UI_S(40)
#define TOP_Y       UI_S(6)
#define STOCK_X     UI_S(6)
#define WASTE_X     UI_S(39)
#define FOUND_X     UI_S(178)
#define FOUND_DX    UI_S(32)
#define TAB_X       UI_S(6)
#define TAB_DX      UI_S(38)
#define TAB_Y       UI_S(56)
#define FAN         UI_S(14)        /* vertical step between tableau cards */
#define PEEK_H      UI_S(18)        /* height of a covered face-up card */

typedef struct {
    signed char card[NCARDS];
    uint8_t up[NCARDS];             /* face up */
    int n;
} pile_t;

static pile_t piles[NPILES];
static int game_state;              /* 1 = won */
static int cur_pile, cur_idx;       /* cursor */
static int sel_pile, sel_idx;       /* picked-up card, -1 if none */

static void push(pile_t *p, int card, int up)
{
    if (p->n < NCARDS) {
        p->card[p->n] = card;
        p->up[p->n] = up;
        p->n++;
    }
}

static int top_card(const pile_t *p)
{
    return p->n > 0 ? p->card[p->n - 1] : -1;
}

static void clear_sel(void)
{
    sel_pile = -1;
    sel_idx = -1;
}

/* Move cards idx..top of pile `from` onto pile `to` if the rules allow it. */
static int do_move(int from, int idx, int to)
{
    pile_t *src = &piles[from], *dst = &piles[to];

    if (idx < 0 || idx >= src->n) return 0;
    int c = src->card[idx];

    if (to >= FOUND && to < TAB) {
        /* Foundation: single top card, same suit, ace first then ascending. */
        int suit = to - FOUND;
        if (idx != src->n - 1 || c / 13 != suit) return 0;
        if (dst->n == 0 ? c % 13 != 0 : c % 13 != top_card(dst) % 13 + 1) return 0;
    } else if (to >= TAB) {
        /* Tableau: king on empty, else one lower in the other colour on a face-up card. */
        if (dst->n == 0) {
            if (c % 13 != 12) return 0;
        } else {
            int t = top_card(dst);
            if (!dst->up[dst->n - 1] || c % 13 != t % 13 - 1 || is_red(c) == is_red(t))
                return 0;
        }
    } else {
        return 0;
    }

    for (int i = idx; i < src->n; i++) push(dst, src->card[i], 1);
    src->n = idx;
    if (idx > 0 && from >= TAB && !src->up[idx - 1]) src->up[idx - 1] = 1;

    if (piles[FOUND].n + piles[FOUND + 1].n + piles[FOUND + 2].n + piles[FOUND + 3].n == NCARDS)
        game_state = 1;
    return 1;
}

/* Keep cur_idx on a sensible card: the top card for the top row, and a
 * face-up card (or the top one) for the tableau. */
static void fix_cur_idx(void)
{
    const pile_t *p = &piles[cur_pile];
    int n = p->n;

    if (cur_pile < TAB) {
        cur_idx = n > 0 ? n - 1 : 0;
        return;
    }
    if (n == 0) {
        cur_idx = 0;
        return;
    }
    if (cur_idx >= n) cur_idx = n - 1;
    int first = n - 1;
    for (int i = 0; i < n; i++) {
        if (p->up[i]) {
            first = i;
            break;
        }
    }
    if (cur_idx < first) cur_idx = first;
}

/* Suit symbol, 7x7 dots of UI_S(1) px. */
static void draw_pip(uint16_t *fb, int x, int y, int suit, uint16_t c)
{
    /* One byte per row, bit 6 = leftmost. */
    static const uint8_t club[7] = {0x1c, 0x1c, 0x6b, 0x7f, 0x6b, 0x08, 0x1c};
    static const uint8_t spade[7] = {0x08, 0x1c, 0x3e, 0x7f, 0x7f, 0x2a, 0x1c};
    static const uint8_t diamond[7] = {0x08, 0x1c, 0x3e, 0x7f, 0x3e, 0x1c, 0x08};
    static const uint8_t heart[7] = {0x36, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 0x08};
    const uint8_t *bm;

    switch (suit) {
    case 0: bm = spade; break;
    case 1: bm = heart; break;
    case 2: bm = diamond; break;
    default: bm = club; break;
    }
    for (int r = 0; r < 7; r++) {
        for (int b = 6; b >= 0; b--) {
            if (!(bm[r] >> b & 1)) continue;
            int px = x + (6 - b) * UI_S(1);
            for (int yy = y + r * UI_S(1); yy < y + (r + 1) * UI_S(1); yy++) {
                if (yy >= UI_H) continue;
                for (int dx = 0; dx < UI_S(1); dx++) fb[yy * UI_W + px + dx] = c;
            }
        }
    }
}

/* Card back: white border, blue face, diagonal hatching. */
static void draw_facedown(uint16_t *fb, int x, int y)
{
    ui_fill(fb, x, y, CARD_W, CARD_H, 0xffff);
    ui_fill(fb, x + UI_S(1), y + UI_S(1), CARD_W - UI_S(2), CARD_H - UI_S(2), 0x211a);
    for (int yy = y + UI_S(3); yy < y + CARD_H - UI_S(3); yy++) {
        if (yy >= UI_H) continue;
        for (int xx = x + UI_S(3); xx < x + CARD_W - UI_S(3); xx++)
            if ((xx + yy) % UI_S(2) == 0) fb[yy * UI_W + xx] = 0x429f;
    }
}

static void draw_outline(uint16_t *fb, int x, int y, int w, int h, uint16_t c)
{
    ui_fill(fb, x - UI_S(2), y - UI_S(2), w + UI_S(4), UI_S(2), c);
    ui_fill(fb, x - UI_S(2), y + h, w + UI_S(4), UI_S(2), c);
    ui_fill(fb, x - UI_S(2), y - UI_S(2), UI_S(2), h + UI_S(4), c);
    ui_fill(fb, x + w, y - UI_S(2), UI_S(2), h + UI_S(4), c);
}

/* Face-up card. A covered (not full) card only shows its top strip. */
static void draw_faceup(uint16_t *fb, int x, int y, int card, int full)
{
    static const char *const r[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    uint16_t c = is_red(card) ? 0xe0c6 : 0x1082;
    int h = full ? CARD_H : PEEK_H;

    ui_fill(fb, x, y, CARD_W, h, 0x630c);
    ui_fill(fb, x + UI_S(1), y + UI_S(1), CARD_W - UI_S(2), h - UI_S(2), 0xffff);
    ui_text(fb, x + UI_S(2), y - UI_S(4), r[card % 13], c);
    draw_pip(fb, x + UI_S(21), y + UI_S(3), card / 13, c);
    if (full) draw_pip(fb, x + UI_S(12), y + UI_S(17), card / 13, c);
}

static void draw_empty(uint16_t *fb, int x, int y)
{
    ui_fill(fb, x, y, CARD_W, CARD_H, 0x43cc);
    ui_fill(fb, x + UI_S(1), y + UI_S(1), CARD_W - UI_S(2), CARD_H - UI_S(2), 0x0a05);
}

static void sol_reset(void)
{
    int deck[NCARDS];

    for (int i = 0; i < NCARDS; i++) deck[i] = i;
    for (int i = NCARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = deck[i];
        deck[i] = deck[j];
        deck[j] = t;
    }
    for (int i = 0; i < NPILES; i++) piles[i].n = 0;

    /* Deal 1..7 cards to the tableau, top card face up; the rest is the stock. */
    int k = 0;
    for (int col = 0; col < 7; col++)
        for (int i = 0; i <= col; i++) push(&piles[TAB + col], deck[k++], i == col);
    while (k < NCARDS) push(&piles[STOCK], deck[k++], 0);

    cur_pile = TAB;
    cur_idx = piles[TAB].n - 1;
    clear_sel();
    game_state = 0;
}

static int sol_step(uint16_t *fb)
{
    if (game_state == 1) {
        ui_vgrad(fb, 0, 0, UI_W, UI_H, 0x138a, 0x0144);
        ui_text_center(fb, UI_W / 2, UI_S(92), "YOU WIN", 0xffff);
        ui_text_center(fb, UI_W / 2, UI_S(124), "A: new game", 0xe71c);
        ui_text_center(fb, UI_W / 2, UI_S(144), "B: exit", 0xe71c);
        if (of_btn_pressed(OF_BTN_A)) sol_reset();
        return of_btn_pressed(OF_BTN_B);
    }

    /* B drops the picked-up card, or exits when nothing is picked up. */
    if (of_btn_pressed(OF_BTN_B)) {
        if (sel_pile < 0) return 1;
        clear_sel();
    }

    if (of_btn_pressed(OF_BTN_LEFT)) {
        if (cur_pile < TAB) {
            if (cur_pile > STOCK) cur_pile--;
        } else if (cur_pile > TAB) {
            cur_pile--;
        }
        fix_cur_idx();
    }
    if (of_btn_pressed(OF_BTN_RIGHT)) {
        if (cur_pile < TAB) {
            if (cur_pile < TAB - 1) cur_pile++;
        } else if (cur_pile < NPILES - 1) {
            cur_pile++;
        }
        fix_cur_idx();
    }

    /* Up/down walk the face-up run of a tableau pile, then hop between rows. */
    if (of_btn_pressed(OF_BTN_UP) && cur_pile >= TAB) {
        const pile_t *p = &piles[cur_pile];
        int first = 0;
        while (first < p->n && !p->up[first]) first++;
        if (first < p->n && first < cur_idx && sel_pile < 0) {
            cur_idx--;
        } else {
            cur_pile -= TAB;
            if (cur_pile > TAB - 1) cur_pile = TAB - 1;
            fix_cur_idx();
        }
    }
    if (of_btn_pressed(OF_BTN_DOWN)) {
        if (cur_pile < TAB) {
            cur_pile += TAB;
            fix_cur_idx();
        } else if (cur_idx < piles[cur_pile].n - 1 && sel_pile < 0) {
            cur_idx++;
        }
    }

    if (of_btn_pressed(OF_BTN_A)) {
        pile_t *p = &piles[cur_pile];
        if (cur_pile == STOCK) {
            pile_t *w = &piles[WASTE];
            if (p->n > 0) {
                p->n--;
                push(w, p->card[p->n], 1);
            } else if (w->n > 0) {
                /* Turn the waste back over into the stock. */
                for (int i = w->n - 1; i >= 0; i--) push(p, w->card[i], 0);
                w->n = 0;
            }
            if (sel_pile >= 0) clear_sel();
        } else if (sel_pile < 0) {
            /* Pick up: the top card of waste/foundation, or a face-up tableau card. */
            if (p->n != 0) {
                if (cur_pile < TAB) {
                    sel_pile = cur_pile;
                    sel_idx = p->n - 1;
                } else if (p->up[cur_idx]) {
                    sel_pile = cur_pile;
                    sel_idx = cur_idx;
                }
            }
        } else if (sel_pile == cur_pile) {
            clear_sel();
        } else if (do_move(sel_pile, sel_idx, cur_pile)) {
            clear_sel();
            fix_cur_idx();
        }
    }

    /* X sends the top card of the selected (or cursor) pile to its foundation. */
    if (of_btn_pressed(OF_BTN_X)) {
        int from = sel_pile >= 0 ? sel_pile : cur_pile;
        int n = piles[from].n;
        if (from != STOCK && n > 0 && do_move(from, n - 1, piles[from].card[n - 1] / 13 + FOUND)) {
            if (sel_pile >= 0) clear_sel();
            fix_cur_idx();
        }
    }

    /* Table */
    ui_vgrad(fb, 0, 0, UI_W, UI_H, 0x1308, 0x09c4);
    if (piles[STOCK].n > 0) {
        draw_facedown(fb, STOCK_X, TOP_Y);
    } else {
        draw_empty(fb, STOCK_X, TOP_Y);
        ui_text_center(fb, STOCK_X + CARD_W / 2, UI_S(17), "O", 0xa514);
    }
    if (piles[WASTE].n > 0)
        draw_faceup(fb, WASTE_X, TOP_Y, top_card(&piles[WASTE]), 1);
    else
        draw_empty(fb, WASTE_X, TOP_Y);
    for (int s = 0; s < 4; s++) {
        int x = FOUND_X + s * FOUND_DX;
        const pile_t *p = &piles[FOUND + s];
        if (p->n > 0) {
            draw_faceup(fb, x, TOP_Y, top_card(p), 1);
        } else {
            draw_empty(fb, x, TOP_Y);
            draw_pip(fb, x + UI_S(12), TOP_Y + UI_S(17), s, 0x7450);
        }
    }

    for (int col = 0; col < 7; col++) {
        const pile_t *p = &piles[TAB + col];
        int x = TAB_X + col * TAB_DX;
        if (p->n == 0) {
            draw_empty(fb, x, TAB_Y);
            continue;
        }
        for (int i = 0; i < p->n; i++) {
            int y = TAB_Y + i * FAN;
            int last = i == p->n - 1;
            if (p->up[i]) {
                draw_faceup(fb, x, y, p->card[i], last);
            } else if (last) {
                draw_facedown(fb, x, y);
            } else {
                /* Covered card back: only the strip above the next card shows. */
                ui_fill(fb, x, y, CARD_W, UI_S(16), 0xffff);
                ui_fill(fb, x + UI_S(1), y + UI_S(1), CARD_W - UI_S(2), UI_S(14), 0x211a);
                for (int yy = y + UI_S(3); yy < y + FAN; yy++) {
                    if (yy >= UI_H) continue;
                    for (int xx = x + UI_S(3); xx < x + CARD_W - UI_S(3); xx++)
                        if ((xx + yy) % UI_S(2) == 0) fb[yy * UI_W + xx] = 0x429f;
                }
            }
        }
    }

    /* Selection: outline the picked-up run. */
    if (sel_pile >= 0) {
        int x, y = TOP_Y, h = CARD_H;
        if (sel_pile == WASTE) {
            x = WASTE_X;
        } else if (sel_pile >= FOUND && sel_pile < TAB) {
            x = FOUND_X + (sel_pile - FOUND) * FOUND_DX;
        } else {
            int last = piles[sel_pile].n > 0 ? piles[sel_pile].n - 1 : 0;
            int s = sel_idx > 0 ? sel_idx : 0;
            if (s > last) s = last;
            x = TAB_X + (sel_pile - TAB) * TAB_DX;
            y = TAB_Y + s * FAN;
            h = CARD_H + (last - s) * FAN;
        }
        draw_outline(fb, x, y, CARD_W, h, 0xff88);
    }

    /* Cursor */
    {
        int x, y = TOP_Y;
        if (cur_pile == STOCK) {
            x = STOCK_X;
        } else if (cur_pile == WASTE) {
            x = WASTE_X;
        } else if (cur_pile < TAB) {
            x = FOUND_X + (cur_pile - FOUND) * FOUND_DX;
        } else {
            int n = piles[cur_pile].n;
            x = TAB_X + (cur_pile - TAB) * TAB_DX;
            y = TAB_Y;
            if (n != 0) y += (cur_idx < n ? cur_idx : n - 1) * FAN;
        }
        draw_outline(fb, x, y, CARD_W, CARD_H, 0x479f);
    }

    ui_text(fb, UI_S(6), UI_S(224), "A:pick/move  B:cancel/exit  X:->foundation", 0xa596);
    return 0;
}

const game_t GAME_SOLITAIRE = {"Solitaire", sol_reset, sol_step};
