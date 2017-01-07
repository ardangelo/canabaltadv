
#include <tonc.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "tiles/bg.h"
#include "tiles/sprites.h"

#define SCR_AT(x,y) ((((x%64 >= 32) ? 32*32 : 0) + (32*y) + x%32) % (64*32))

int main(void) {

	memcpy(pal_bg_mem, bgPal, bgPalLen); // load colors into bgpal

	// use block 0 as charblock, 30/31 as screenblocks. 4 bits per pixel, 64x32 tiles
	memcpy(&tile_mem[0][0], bgTiles, bgTilesLen); // load tiles into charblocks
	SCR_ENTRY *bg0_map = se_mem[30];
	for (int i = 0; i <= (SCREEN_WIDTH >> 3); i++) { // fill in the initial map
		bg0_map[SCR_AT(i, (int)(rand() % 16))] = SE_PALBANK(0) | TILE_BUILD_S0;
	}
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32; // apply bg settings
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	// Scroll around some
	int x = 0;
	int horizon = (SCREEN_WIDTH >> 3);
	while(1) {
		vid_vsync();
		key_poll();

		int changed = key_tri_horz();
		x += changed;
		if (changed > 0) {
			int new_col = ((x + SCREEN_WIDTH) >> 3) + 1;
			if (new_col > horizon) {
				int h = rand() % 16;
				for (int i = 0; i < 16; i++) {
					bg0_map[SCR_AT(new_col, i)] = SE_PALBANK(0) | ((i == h)?TILE_BUILD_S0:TILE_SKY_S0);
				}
				horizon = new_col;
			}
		}

		REG_BG0HOFS= x;
		//REG_BG0VOFS= y;
	}

	return 0;
}


