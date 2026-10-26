/* game.h — mini-games under Extras > Games. Music keeps playing while a game
 * runs: main.c pumps audio every frame and calls step() to draw one frame. */
#ifndef GAME_H
#define GAME_H

#include <stdint.h>

typedef struct {
    const char *name;
    void (*reset)(void);
    /* Advance and draw one frame into fb. Returns nonzero to exit the game. */
    int (*step)(uint16_t *fb);
} game_t;

extern const game_t GAME_BRICK;
extern const game_t GAME_PARACHUTE;
extern const game_t GAME_SOLITAIRE;

#endif
