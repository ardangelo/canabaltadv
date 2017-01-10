
#include <tonc.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "tiles/bg.h"
#include "tiles/sprites.h"

typedef struct {
	uint8_t height;
	uint8_t width;
	uint8_t gap;
	uint8_t style;
} build;

// bg globals
#define WORLD_HEIGHT 32

build builds[4];
uint32_t starts[4];
uint32_t curr_build = 0;

#define CURR_BUILD (builds[curr_build])
#define LAST_BUILD (builds[(curr_build + 3) % 4])

// obj globals
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

uint32_t speed = 2;
uint32_t player_x = 10;
uint32_t player_y = 10;

inline uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
	uint n= tx + ty*32;
	if(tx >= 32)
		n += 0x03E0;
	if(ty >= 32 && (bgcnt&BG_REG_64x64)==BG_REG_64x64)
		n += 0x0400;
	return n;
}

inline build generate_build() {
	uint8_t height = 20 + (rand() % 16 - 8);
	uint8_t width = 24 + (rand() % 10 - 5);
	uint8_t gap = 10 + (rand() % 8 - 4);
	uint8_t style = 0;
	
	build r = {height, width, gap, style};
	return r;
}

void draw_col(SCR_ENTRY* map, uint32_t col) {
	if (starts[curr_build] > col) {
		return;
	}
	for (int i = 0; i < 4; i++) {
		int bn = (curr_build + i) % 4;
		build b = builds[bn];
		if ((starts[bn] <= col) && (col < starts[bn] + b.width + b.gap)) {
			for (int row = 0; row < WORLD_HEIGHT; row++) {
				if ((row > (WORLD_HEIGHT - b.height)) && (col < starts[bn] + b.width)) {
					map[se_index_fast(col%64, row, REG_BG0CNT)] = SE_PALBANK(0) | TILE_BUILD_S0;
				} else {
					map[se_index_fast(col%64, row, REG_BG0CNT)] = SE_PALBANK(0) | TILE_SKY_S0;
				}
			}
			return;
		}
	}
}

int main(void) {

	memcpy(pal_bg_mem, bgPal, bgPalLen); // load colors into bgpal

	// use block 0 as charblock, 30-33 as screenblocks. 4 bits per pixel, 64x64 tiles
	memcpy(&tile_mem[0][0], bgTiles, bgTilesLen); // load tiles into charblocks
	SCR_ENTRY *bg0_map = se_mem[30];

	// generate the starting buildings
	curr_build = 0;
	starts[0] = 0;
	builds[0] = generate_build();
	starts[1] = starts[0] + builds[0].width + builds[0].gap;
	builds[1] = generate_build();
	starts[2] = starts[1] + builds[1].width + builds[1].gap;
	builds[2] = generate_build();
	starts[3] = starts[2] + builds[2].width + builds[2].gap;
	builds[3] = generate_build();

	// fill in the initial map
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32; // apply bg settings
	for (int col = 0; col <= (SCREEN_WIDTH >> 3); col++) {
		draw_col(bg0_map, col);
	}
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;;

	// load in the sprites
	oam_init(obj_buffer, 128);
	memcpy(pal_obj_mem, spritesPal, spritesPalLen);
	memcpy(&tile_mem[4][0], spritesTiles, spritesTilesLen);

	// set player sprite attrs
	OBJ_ATTR *player = &obj_buffer[0];
	obj_set_attr(player, 
	             ATTR0_TALL,
	             ATTR1_SIZE_8,
	             ATTR2_PALBANK(0) | 0);
	obj_set_pos(player, player_x, player_y);

	// Scroll around some
	int bg0_x = 0, bg0_y = 0;
	int horizon = (SCREEN_WIDTH >> 3);
	while(1) {
		vid_vsync();
		key_poll();

		bg0_y += key_tri_vert();

		int changed = key_tri_horz();
		bg0_x += changed * speed;
		if (changed > 0) {
			// generate new building if the current one is out of sight
			if ((bg0_x >> 3) - 1 > starts[curr_build] + CURR_BUILD.width + CURR_BUILD.gap) {
				starts[curr_build] = starts[(curr_build + 3) % 4] + LAST_BUILD.width + LAST_BUILD.gap;
				builds[curr_build] = generate_build();
				curr_build = (curr_build + 1) % 4;
			}

			// draw just beyond the horizon
			int new_col = ((bg0_x + SCREEN_WIDTH) >> 3) + 1;
			if (new_col > horizon) {
				draw_col(bg0_map, new_col);
				horizon = new_col;
			}
		}

		// update bg regs
		REG_BG0HOFS = bg0_x;
		REG_BG0VOFS = bg0_y;
		// update oam
		oam_copy(oam_mem, obj_buffer, 1);
	}

	return 0;
}


