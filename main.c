
#include <tonc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "tiles/bg.h"
#include "tiles/sprites.h"

typedef struct {
	uint8_t height;
	uint8_t width;
	uint8_t gap;
	uint8_t style;
} build;

enum player_states {RUNNING, JUMPING, FALLING, ROLLING, DEAD};

uint32_t frame_count;

// bg globals
#define WORLD_HEIGHT 32
#define TERMINAL_VELOCITY 8

build builds[4];
uint32_t starts[4];
uint32_t curr_build = 0;

#define CURR_BUILD (builds[curr_build])
#define LAST_BUILD (builds[(curr_build + 3) % 4])

// obj globals
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

float scroll_speed_x = 5, scroll_speed_y = 5;
int player_x = 10, player_y = 10;
float player_speed_x = 0, player_speed_y = 0;
float player_accel_x = 0, player_accel_y = 0;
enum player_states player_state, new_player_state;
int anim_frame, anim_start, anim_len;

OBJ_ATTR *player_obj;
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
	uint8_t width = 24 + (rand() % 10 - 5);
	uint8_t gap = 15 + (rand() % 8 - 4);
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
			uint16_t tile = TILE_TRANSPARENT;
			for (int row = 0; row < WORLD_HEIGHT; row++) {
				if (row > (WORLD_HEIGHT - b.height)) {
					if (col == starts[bn]) {
						tile = TILE_BUILD_S0_BL;
					} else if ((col > starts[bn]) && (col < starts[bn] + b.width)) {
						tile = TILE_BUILD_S0_BM;
					} else if (col == starts[bn] + b.width) {
						tile = TILE_BUILD_S0_BR;
					}
				} else if (row == (WORLD_HEIGHT - b.height)) {
					if (col == starts[bn]) {
						tile = TILE_BUILD_S0_TL;
					} else if ((col > starts[bn]) && (col < starts[bn] + b.width)) {
						tile = TILE_BUILD_S0_TM;
					} else if (col == starts[bn] + b.width) {
						tile = TILE_BUILD_S0_TR;
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

	scroll_speed_x = 5;
	scroll_speed_y = 5;
	player_x = 10, player_y = 10;
	player_speed_x = 0, player_speed_y = 0;
	player_accel_x = 0, player_accel_y = 0;

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
	player_obj = &obj_buffer[0];
	obj_set_attr(player_obj, 
	             ATTR0_TALL,
	             ATTR1_SIZE_8,
	             ATTR2_PALBANK(0) | TILE_RUNNING_START);
	obj_set_pos(player_obj, player_x, player_y);

	// set score sprites
	for (int i = 0; i < 8; i++) { score_objs[i] = &obj_buffer[1+i]; }
	set_score(0);
	obj_set_attr(score_objs[0], 
	             ATTR0_TALL,
	             ATTR1_SIZE_8,
	             ATTR2_PALBANK(0) | TILE_METER_MARK);
	obj_set_pos(score_objs[0], SCREEN_WIDTH - 8, 0);

	// Scroll around some
	int bg0_x = 0, bg0_y = 0;
	int horizon = (SCREEN_WIDTH >> 3);
	int ground = 8*CURR_BUILD.height;
	int player_height = 32*8 - (bg0_y + player_y + 16);
	player_state = RUNNING;
	anim_frame = 0;
	anim_start = TILE_RUNNING_START;
	anim_len = ANIM_RUNNING_LEN;
	while(1) {
		vid_vsync();
		key_poll();

		int bg0_changed_x = key_tri_horz() * scroll_speed_x;
		int bg0_changed_y = 0;
		if ((abs(player_y - SCREEN_HEIGHT) < 80) ||
		    (player_y < 80)) {
			bg0_changed_y = player_speed_y;
		}
		int jump_requested = key_hit(KEY_A);
		int ascent_ended = key_released(KEY_A);
		
		bg0_x += bg0_changed_x;
		if (bg0_y + bg0_changed_y < 0) {
			bg0_y = 0;
			bg0_changed_y = 0;
		} else if (bg0_y + SCREEN_HEIGHT + bg0_changed_y > 32*8) {
			bg0_y = 32*8 - SCREEN_HEIGHT;
			bg0_changed_y = 0;
		} else {
			bg0_y += bg0_changed_y;
		}
		if (bg0_changed_x > 0) {
			// check if we stepped off the edge
			if (((bg0_x + player_x) >> 3) > starts[curr_build] + CURR_BUILD.width) {
				ground = 0;
			}
			// check if we just entered a new building
			if (((bg0_x + player_x) >> 3) + 1 >= starts[curr_build] + CURR_BUILD.width + CURR_BUILD.gap) {
				// generate new building and advance
				starts[curr_build] = starts[(curr_build + 3) % 4] + LAST_BUILD.width + LAST_BUILD.gap;
				builds[curr_build] = generate_build();
				curr_build = (curr_build + 1) % 4;

				// update ground level
				ground = 8*CURR_BUILD.height;
			}

			// draw just beyond the horizon
			int new_col = ((bg0_x + SCREEN_WIDTH) >> 3) + 1;
			if (new_col > horizon) {
				draw_col(bg0_map, new_col);
				horizon = new_col;
			}
		}

		// update player state
		if (player_state == RUNNING) { // should we start falling
			if (abs(player_height - ground) > 8) {
				new_player_state = FALLING;
				player_accel_y = .3;
			}
			if (jump_requested) {
				new_player_state = JUMPING;
				player_speed_y = -8;
				player_accel_y = .3;
			}
		} else if (player_state == JUMPING) {
			if (player_speed_y > 0) {
				new_player_state = FALLING;
			}
			if (ascent_ended) {
				if (player_speed_y < -4) {
					player_speed_y = -4;
				}
			}
		} else if (player_state == FALLING) { // did we hit the ground
			if (player_height <= 8) {
				new_player_state = DEAD;
				player_speed_y = 0;
				player_accel_y = 0;
				goto reset;
			}
		}
		// snap to ground
		if ((new_player_state != DEAD) &&
		    (new_player_state != JUMPING) &&
		    (abs(player_height - ground) <= 4)) {
			if (player_speed_y == TERMINAL_VELOCITY) {
				new_player_state = ROLLING;
			} else {
				new_player_state = RUNNING;
			}
			player_speed_y = 0;
			player_accel_y = 0;
			// player_height = ground;
			player_y = 32*8 - ground - bg0_y - 16;
		}

		// get next frame of animation
		frame_count++;
		if (player_state == new_player_state) {
			if (player_state != JUMPING) {
				if (frame_count % 2 == 0) {
					anim_frame++;
					anim_frame %= anim_len;
					if ((new_player_state == ROLLING) && (anim_frame == 0)) {
						new_player_state = RUNNING;
					}
				}
			} else {
				
			}
		} else {
			anim_frame = 0;
			if (new_player_state == RUNNING) {
				anim_start = TILE_RUNNING_START;
				anim_len = ANIM_RUNNING_LEN;
			} else if (new_player_state == JUMPING) {
				anim_start = TILE_JUMPING_START;
				anim_len = ANIM_JUMPING_LEN;
			} else if (new_player_state == FALLING) {
				anim_start = TILE_FALLING_START;
				anim_len = ANIM_FALLING_LEN;
			} else if (new_player_state == ROLLING) {
				anim_start = TILE_ROLLING_START;
				anim_len = ANIM_ROLLING_LEN;
			}
			player_state = new_player_state;
		}
		set_score(player_state);
		// apply frame
		obj_set_attr(player_obj, 
		             ATTR0_TALL | ((player_state == DEAD) ? ATTR0_HIDE : 0),
		             ATTR1_SIZE_8,
		             ATTR2_PALBANK(0) | (anim_start + 2*anim_frame));

		// move player
		player_height = 32*8 - (bg0_y + player_y + 16);
		player_speed_y = player_speed_y + player_accel_y;
		player_y += (int)player_speed_y - bg0_changed_y;
		obj_set_pos(player_obj, player_x, player_y);

		// update bg regs
		REG_BG0HOFS = bg0_x;
		REG_BG0VOFS = bg0_y;
		// update oam
		oam_copy(oam_mem, obj_buffer, 9);
	}

	return 0;
}


