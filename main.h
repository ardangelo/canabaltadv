#ifndef _MAIN_H_
#define _MAIN_H_

#include "engine.h"

/*
#define DEBUG(str) (nocash_puts(str))
#define DEBUGFMT(fmt, ...) do {	  \
		asprintf(&dbg_str, fmt, __VA_ARGS__); \
		nocash_puts(dbg_str); \
		free(dbg_str); \
	} while (0)
*/

#define DEBUG(fmt, ...)
#define DEBUGFMT(fmt, ...)

// data structs
typedef struct {
	uint frame, start, len;
} animation_t;

typedef enum {
	RUN, JUMP, FALL, ROLL, DEAD
} player_state_t;
typedef struct {
	sprite_t s;
	float vx, vy, ax, ay;
	player_state_t state;
	animation_t anim;
} player_t;

typedef struct {
	sprite_t s;
	float vy, vx, ax, ay;
	uint hit, style;
	bool valid;
} crate_t;

typedef struct {
	byte tl, tm, tr, bl, bm, br;
} build_style_t;

#define BUILDS_AHEAD 4
#define MAX_CRATES 8
typedef struct {
	uint8_t height;
	uint8_t width;
	uint8_t gap;
	build_style_t style;
} build_t;

// bg globals
#define BG0_HEIGHT 32
#define BG0_WIDTH 64
#define BUILDINGS_PB 0
#define MIDGROUND_PB 1
#define BACKGROUND_PB 2

// tunables
#define UPPER_SLACK 30
#define LOWER_SLACK 90

#define GRAV -.2
#define TERMINAL_VELOCITY 30*GRAV
#define JUMP_START_VEL 6
#define JUMP_END_VEL 3
#define ROLL_THRESH .9*TERMINAL_VELOCITY
#define GROUND_THRESH 4

#define CRATE_GRAV -.12
#define CRATE_HIT_VX 6
#define CRATE_HIT_VY 2

#define BG1_SCROLL_RATE .5
#define BG1_YOFFS 30
#define BG2_SCROLL_RATE .25
#define BG2_YOFFS 50

// animation stuff

#define TILE_METER_MARK 0
#define TILE_ZERO 2

#define ANIM_RUN (animation_t){0, 22, 16}
#define ANIM_JUMP (animation_t){0, 54, 4}
#define ANIM_FALL (animation_t){0, 62, 6}
#define ANIM_ROLL (animation_t){0, 74, 11}

#define TILE_TRANSPARENT 0
#define BUILD_S0 (build_style_t){1,2,3,4,5,6}
#define TILE_SKY 7

#endif
