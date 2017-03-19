
#include <tonc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#include "tiles/bg.h"
#include "tiles/sprites.h"

uint32_t frame_count;

build builds[4];
uint32_t starts[4];
uint32_t curr_build = 0;

#define CURR_BUILD (builds[curr_build])
#define LAST_BUILD (builds[(curr_build + 3) % 4])

// obj globals
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

camera cam;
player guy;

OBJ_ATTR *score_objs[8];

inline uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
	uint n= tx + ty*32;
	if(tx >= 32)
		n += 0x03E0;
	if(ty >= 32 && (bgcnt&BG_REG_64x64)==BG_REG_64x64)
		n += 0x0400;
	return n;
}

inline build generate_build() {
	uint8_t height = 14 + (rand() % 10 - 5);
	uint8_t width = 50 + (rand() % 10 - 5);
	uint8_t gap = 15 + (rand() % 8 - 4);
	build_style style = BUILD_S0;
	
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
			uint16_t tile = TILE_TRANSPARENT;
			for (int row = 0; row < WORLD_HEIGHT; row++) {
				if (row > (WORLD_HEIGHT - b.height)) {
					if (col == starts[bn]) {
						tile = b.style.bl;
					} else if ((col > starts[bn]) && (col < starts[bn] + b.width)) {
						tile = b.style.bm;
					} else if (col == starts[bn] + b.width) {
						tile = b.style.br;
					}
				} else if (row == (WORLD_HEIGHT - b.height)) {
					if (col == starts[bn]) {
						tile = b.style.tl;
					} else if ((col > starts[bn]) && (col < starts[bn] + b.width)) {
						tile = b.style.tm;
					} else if (col == starts[bn] + b.width) {
						tile = b.style.tr;
					}
				} else {
					tile = TILE_TRANSPARENT;
				}
				map[se_index_fast(col%64, row, REG_BG0CNT)] = SE_PALBANK(0) | tile;
			}
			return;
		}
	}
}

static inline void set_score(uint32_t score) {
	for (int i = 1; i < 8; i++) {
		obj_set_attr(score_objs[i],
		             ATTR0_TALL,
		             ATTR1_SIZE_8,
		             ATTR2_PALBANK(0) | (TILE_ZERO + 2*(score % 10)));
		score /= 10;
		obj_set_pos(score_objs[i], SCREEN_WIDTH - 8*(i+1), 0);
	}
}

int main(void) {

	memcpy(pal_bg_mem, bgPal, bgPalLen); // load colors into bgpal

	// use block 0 as charblock, 26-33 as screenblocks. 4 bits per pixel, 64x32 tiles
	memcpy(&tile_mem[0][0], bgTiles, bgTilesLen); // load tiles into charblocks
	SCR_ENTRY *bg0_map = se_mem[30];
	SCR_ENTRY *bg1_map = se_mem[26];

 reset:

	cam = (camera){0, 0, 5, 5};
	guy = (player){NULL, 10, 10, 150, 0, 0, 0, 0, RUN, ANIM_RUN, 0, 0, 0};
	
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

	// fill in the initial bg0
	REG_BG0CNT = BG_PRIO(0) | BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32; // apply bg settings
	for (int col = 0; col <= (SCREEN_WIDTH >> 3); col++) {
		draw_col(bg0_map, col);
	}

	// fill in the scenery bg1
	REG_BG1CNT = BG_PRIO(1) | BG_CBB(0) | BG_SBB(26) | BG_4BPP | BG_REG_64x32;
	for (int i = 0; i < 32*64; i++) {
		bg1_map[i] = SE_PALBANK(0) | TILE_SKY;
	}
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;;

	// load in the sprites
	oam_init(obj_buffer, 128);
	memcpy(pal_obj_mem, spritesPal, spritesPalLen);
	memcpy(&tile_mem[4][0], spritesTiles, spritesTilesLen);

	// set player sprite attrs
	guy.obj = &obj_buffer[0];
	obj_set_attr(guy.obj, 
	             ATTR0_TALL,
	             ATTR1_SIZE_8,
	             ATTR2_PALBANK(0) | guy.anim.start);
	obj_set_pos(guy.obj, guy.x, guy.y);

	// set score sprites
	for (int i = 0; i < 8; i++) { score_objs[i] = &obj_buffer[1+i]; }
	set_score(0);
	obj_set_attr(score_objs[0], 
	             ATTR0_TALL,
	             ATTR1_SIZE_8,
	             ATTR2_PALBANK(0) | TILE_METER_MARK);
	obj_set_pos(score_objs[0], SCREEN_WIDTH - 8, 0);

	// Scroll around some
	int horizon = (SCREEN_WIDTH >> 3);
	int ground = TILE2PIXEL(CURR_BUILD.height);

	while(1) {
		vid_vsync();
		key_poll();

		int cam_delta_x = key_tri_horz() * cam.vx;
		int cam_delta_y = 0;
		if ((guy.y < 40) || (guy.y > (SCREEN_HEIGHT - 80))) {
			cam_delta_y =- guy.vy;
		}
		int jump_requested = key_hit(KEY_A);
		int ascent_ended = key_released(KEY_A);
		
		cam.x += cam_delta_x;
		cam.y += cam_delta_y;
		cam.y = CLAMP(cam.y, 0, 32*8 - SCREEN_HEIGHT);
		
		if (cam_delta_x > 0) {
			// check if we stepped off the edge
			if (((cam.x + guy.x) >> 3) > starts[curr_build] + CURR_BUILD.width) {
				ground = 0;
			}
			// check if we just entered a new building
			if (((cam.x + guy.x) >> 3) + 1 >= starts[curr_build] + CURR_BUILD.width + CURR_BUILD.gap) {
				// generate new building and advance
				starts[curr_build] = starts[(curr_build + 3) % 4] + LAST_BUILD.width + LAST_BUILD.gap;
				builds[curr_build] = generate_build();
				curr_build = (curr_build + 1) % 4;

				// update ground level
				ground = 8*CURR_BUILD.height;
			}

			// draw just beyond the horizon
			int new_col = ((cam.x + SCREEN_WIDTH) >> 3) + 1;
			if (new_col > horizon) {
				draw_col(bg0_map, new_col);
				horizon = new_col;
			}
		}

		// update player state
		int new_state;
		if (guy.state == RUN || guy.state == ROLL) { // should we start falling
			if (abs(guy.height - ground) > 0) {
				new_state = FALL;
				guy.ay = GRAV;
			}
			if (jump_requested) {
				new_state = JUMP;
				guy.vy = -30*GRAV;
				guy.ay = GRAV;
			}
		} else if (guy.state == JUMP) {
			if (guy.vy < 0) {
				new_state = FALL;
			}
			if (ascent_ended) {
				guy.vy = MIN(guy.vy, -13*GRAV);
			}
		} else if (guy.state == FALL) { // did we hit the ground
			if (guy.height <= 8) {
				new_state = DEAD;
				guy.vy = 0;
				guy.ay = 0;
				goto reset;
			}
		}

		// get next frame of animation
		frame_count++;
		if (guy.state == new_state) {
			if (frame_count % 2 == 0) {
				guy.anim.frame++;
				guy.anim.frame %= guy.anim.len;
				if ((guy.state == ROLL) && (guy.anim.frame == 0)) {
					new_state = RUN;
					guy.anim = ANIM_RUN;
				}
			}
		} else {
			switch (new_state) {
			case RUN:
				guy.anim = ANIM_RUN; break;
			case JUMP:
				guy.anim = ANIM_RUN; break;
			case FALL:
				guy.anim = ANIM_FALL; break;
			case ROLL:
				guy.anim = ANIM_ROLL; break;
			default: break;
			}
			guy.state = new_state;
		}
		set_score(cam.x >> 3);

		// move player
		guy.vy += guy.ay;
		guy.height += (int)guy.vy;
		
		// snap to ground
		if ((guy.state == FALL) &&
		    (abs(guy.height - ground) <= 4)) {
			if (.9*TERMINAL_VELOCITY > guy.vy) {
				new_state = ROLL;
			} else {
				new_state = RUN;
			}
			guy.vy = 0;
			guy.ay = 0;
			// guy.height = ground;
			guy.height = ground;
		}

		// calculate position on screen
		guy.y = TILE2PIXEL(BG0_HEIGHT) - (cam.y + guy.height + 16);

		// apply player attributes
		obj_set_attr(guy.obj, 
		             ATTR0_TALL | ((guy.state == DEAD) ? ATTR0_HIDE : 0),
		             ATTR1_SIZE_8,
		             ATTR2_PALBANK(0) | (guy.anim.start + 2*guy.anim.frame));
		obj_set_pos(guy.obj, guy.x, guy.y);

		// update bg regs
		REG_BG0HOFS = cam.x;
		REG_BG0VOFS = cam.y;
		// update oam
		oam_copy(oam_mem, obj_buffer, 9);
	}

	return 0;
}


