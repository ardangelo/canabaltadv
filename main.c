
#include <tonc.h>
#include <krawall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#include "tiles/buildings.h"
#include "tiles/midground.h"
#include "tiles/background.h"
#include "tiles/sprites.h"

#if MUSIC == 1
#include "modules/instruments.h"
#include "modules/modules.h"
#include "modules/samples.h"
#endif

uint32_t frame_count;

build_t builds[4];
uint32_t starts[4];
uint32_t curr_build = 0;

#define CURR_BUILD (builds[curr_build])
#define LAST_BUILD (builds[(curr_build + 3) % 4])

// obj globals
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;
int active_objs = 9 + MAX_CRATES; // 1 for player, 8 for score segments, 2 for crates

camera_t cam;
player_t guy;

OBJ_ATTR *score_objs[8];

inline uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
	uint n= tx + ty*32;
	if(tx >= 32)
		n += 0x03E0;
	if(ty >= 32 && (bgcnt&BG_REG_64x64)==BG_REG_64x64)
		n += 0x0400;
	return n;
}

inline build_t generate_build() {
	uint8_t height = 14 + (rand() % 10 - 5);
	uint8_t width = 50 + (rand() % 10 - 5);
	uint8_t gap = 15 + (rand() % 8 - 4);
	build_style_t style = BUILD_S0;

	build_t b = (build_t){height, width, gap, style, NULL};
	for (int i = 0; i < MAX_CRATES; i++) {
		b.crates[i] = (crate_t){NULL, 0, 0, PIXEL(height), PIXEL(2*i), 0, 0, TILE_METER_MARK};
	}
	
	return b;
}

void draw_col(SCR_ENTRY* map, uint32_t col) {
	if (starts[curr_build] > col) {
		return;
	}
	for (int i = 0; i < 4; i++) {
		int bn = (curr_build + i) % 4;
		build_t *b = &builds[bn];
		if ((starts[bn] <= col) && (col < starts[bn] + b->width + b->gap)) {
			uint16_t tile = TILE_TRANSPARENT;
			for (int row = 0; row < WORLD_HEIGHT; row++) {
				if (row > (WORLD_HEIGHT - b->height)) {
					if (col == starts[bn]) {
						tile = b->style.bl;
					} else if ((col > starts[bn]) && (col < starts[bn] + b->width)) {
						tile = b->style.bm;
					} else if (col == starts[bn] + b->width) {
						tile = b->style.br;
					}
				} else if (row == (WORLD_HEIGHT - b->height)) {
					if (col == starts[bn]) {
						tile = b->style.tl;
					} else if ((col > starts[bn]) && (col < starts[bn] + b->width)) {
						tile = b->style.tm;
					} else if (col == starts[bn] + b->width) {
						tile = b->style.tr;
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
	// set up irqs
	fnptr isr = NULL;
	irq_init(isr);
	irq_add(II_VBLANK, isr);

	#if MUSIC == 1
	irq_add(II_TIMER1, kradInterrupt);

	kragInit(KRAG_INIT_STEREO);
	krapPlay(&mod_sanic, KRAP_MODE_LOOP, 0);
	#endif
	
	// set up backgrounds tiles
	memcpy(pal_bg_bank[0], buildingsPal, buildingsPalLen); // load colors into bgpal
	memcpy(pal_bg_bank[1], midgroundPal, midgroundPalLen);
	memcpy(pal_bg_bank[2], backgroundPal, backgroundPalLen);
	// 26-33 as screenblocks. 4 bits per pixel, 64x32 tiles
	// use block 0 as tile charblock
	memcpy(&tile_mem[0][0], buildingsTiles, buildingsTilesLen); // block 1 as midground charblock
	memcpy(&tile_mem[1][0], midgroundTiles, midgroundTilesLen); // block 2 background charblock
	memcpy(&tile_mem[2][0], backgroundTiles, backgroundTilesLen); 

	SCR_ENTRY *bg0_map = se_mem[30];
	SCR_ENTRY *bg1_map = se_mem[28];
	SCR_ENTRY *bg2_map = se_mem[26];

 reset:

	cam = (camera_t){0, 0, 5, 5};
	guy = (player_t){NULL, 30, 10, 150, 0, 0, 0, 0, RUN, ANIM_RUN, 0, 0, 0};
	
	// generate the starting buildings
	curr_build = 0;
	starts[0] = 0;
	builds[0] = generate_build();
	for (int i = 1; i < 4; i++) {
		starts[i] = starts[i-1] + builds[i-1].width + builds[i-1].gap;
		builds[i] = generate_build();
	}

	// fill in the initial bg0
	REG_BG0CNT = BG_PRIO(0) | BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32; // apply bg settings
	for (int col = 0; col <= (SCREEN_WIDTH >> 3); col++) {
		draw_col(bg0_map, col);
	}

	// fill in the midground bg1 and background bg2
	REG_BG1CNT = BG_PRIO(1) | BG_CBB(1) | BG_SBB(28) | BG_4BPP | BG_REG_64x32;
	REG_BG2CNT = BG_PRIO(2) | BG_CBB(2) | BG_SBB(26) | BG_4BPP | BG_REG_64x32;
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 32; j++) {
			bg1_map[se_index_fast(i, j, REG_BG1CNT)] = SE_PALBANK(1) | midgroundMap[64*j+i];
			bg2_map[se_index_fast(i, j, REG_BG2CNT)] = SE_PALBANK(2) | backgroundMap[64*j+i];
		}
	}

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_OBJ | DCNT_OBJ_1D;

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
	int ground = PIXEL(CURR_BUILD.height);

	while(1) {
		VBlankIntrWait();

		#if MUSIC == 1
		krapInstProcess();
		kramWorker();
		#endif
		
		key_poll();

		int cam_delta_x = key_tri_horz() * cam.vx;
		int cam_delta_y = 0;
		if ((guy.y < UPPER_SLACK) || (guy.y > (SCREEN_HEIGHT - LOWER_SLACK))) { 
			cam_delta_y =- guy.vy;
		}
		int jump_requested = key_hit(KEY_A);
		int ascent_ended = key_released(KEY_A);
		
		cam.x += cam_delta_x;
		cam.y += cam_delta_y;
		cam.y = CLAMP(cam.y, 0, PIXEL(WORLD_HEIGHT) - SCREEN_HEIGHT);
		
		if (cam_delta_x > 0) {
			// did we hit a crate?
			for (int i = 0; (i < MAX_CRATES) && CURR_BUILD.crates[i].height; i++) {
				crate_t *c = &CURR_BUILD.crates[i];
				if (!c->hit &&
				    (abs(guy.x - c->x) <= PIXEL(1)) &&
				    (abs(guy.y - c->y) <= PIXEL(2))) {
					c->vy = CRATE_HIT_VY;
					c->hit = 1;
				}
			}
			
			// check if we stepped off the edge
			if (((cam.x + guy.x) >> 3) > starts[curr_build] + CURR_BUILD.width) { ground = 0; }
			// check if we just entered a new building
			if (((cam.x + guy.x) >> 3) + 1 >= starts[curr_build] + CURR_BUILD.width + CURR_BUILD.gap) {
				// kill crate object if need to
				for (int i = 0; (i < MAX_CRATES) && CURR_BUILD.crates[i].height; i++) {
					if (CURR_BUILD.crates[i].obj) {
						obj_set_attr(CURR_BUILD.crates[i].obj, 
						             ATTR0_TALL | ATTR0_HIDE,
						             ATTR1_SIZE_8,
						             ATTR2_PALBANK(0));
						CURR_BUILD.crates[i].obj = NULL;
					}
				}
				
				// generate new building and advance
				starts[curr_build] = starts[(curr_build + 3) % 4] + LAST_BUILD.width + LAST_BUILD.gap;
				builds[curr_build] = generate_build();
				curr_build = (curr_build + 1) % 4;

				// create crate objects if need to
				for (int i = 0; (i < MAX_CRATES) && CURR_BUILD.crates[i].height; i++) {
					crate_t *c = &CURR_BUILD.crates[i];
					if (1) {//c->y) {
						c->obj = &obj_buffer[CRATE_OBJ_START + i];
						obj_set_attr(c->obj, 
						             ATTR0_TALL | 0,//ATTR0_HIDE,
						             ATTR1_SIZE_8,
						             ATTR2_PALBANK(0) | c->style);
						c->x = starts[curr_build] + c->offset;
						c->height = PIXEL(CURR_BUILD.height);
					}
				}

				// update ground level
				ground = PIXEL(CURR_BUILD.height);
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
		switch (guy.state) {
		case RUN:
		case ROLL:  // should we start falling
			if (abs(guy.height - ground) > 0) {
				new_state = FALL;
				guy.ay = GRAV;
			}
			if (jump_requested) {
				new_state = JUMP;
				guy.vy = JUMP_START_VEL;
				guy.ay = GRAV;
			}
			break;
		case JUMP:
			if (guy.vy < 0) { new_state = FALL; }
			if (ascent_ended) { guy.vy = MIN(guy.vy, JUMP_END_VEL); }
			break;
		case FALL: // did we hit the ground
			if (guy.height <= DEATH_BOUNDARY) {
				new_state = DEAD;
				guy.vy = 0;
				guy.ay = 0;
				goto reset;
			}
			break;
		default: break;
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

		// move player
		guy.vy += guy.ay;
		guy.height += (int)guy.vy;
		
		// snap to ground
		if ((guy.state == FALL) &&
		    (abs(guy.height - ground) <= GROUND_THRESH)) {
			if (ROLL_THRESH > guy.vy) {
				new_state = ROLL;
			} else {
				new_state = RUN;
			}
			guy.vy = 0;
			guy.ay = 0;
			guy.height = ground;
		}

		// calculate position on screen
		guy.y = PIXEL(BG0_HEIGHT) - (cam.y + guy.height + PIXEL(2));

		// apply player attributes
		obj_set_attr(guy.obj, 
		             ATTR0_TALL | ((guy.state == DEAD) ? ATTR0_HIDE : 0),
		             ATTR1_SIZE_8,
		             ATTR2_PALBANK(0) | (guy.anim.start + 2*guy.anim.frame));
		obj_set_pos(guy.obj, guy.x, guy.y);

		// apply crate attributes
		for (int i = 0; (i < MAX_CRATES) && CURR_BUILD.crates[i].height; i++) {
			crate_t *c = &CURR_BUILD.crates[i];
			if (c->obj) {
				if (c->hit) {
					if (c->vy > CRATE_TERMINAL_VELOCITY) {
						c->vy -= CRATE_GRAV;
						c->y += c->vy;
						c->x += CRATE_HIT_VX;
					}
				} else {
					c->y = PIXEL(BG0_HEIGHT) - (cam.y + c->height + PIXEL(2));
				}
				// I think there's something wrong with this, it starts messing with the spawn position of the box
				c->x -= cam_delta_x;//((starts[curr_build] + PIXEL(c->offset)) - cam.x) % PIXEL(32);

				if (c->y > SCREEN_HEIGHT) {
					obj_set_attr(c->obj, 
					             ATTR0_TALL | ATTR0_HIDE,
					             ATTR1_SIZE_8,
					             0);
					c->obj = NULL;
				} else {
					obj_set_pos(c->obj,
					            c->x,
					            c->y);
				}
			}
		}
		
		set_score(CURR_BUILD.crates[0].y);//cam.x >> 3);

		// update bg regs
		REG_BG0HOFS = cam.x;
		REG_BG0VOFS = cam.y;
		REG_BG1HOFS = cam.x * BG1_SCROLL_RATE;
		REG_BG1VOFS = cam.y * BG1_SCROLL_RATE + BG1_YOFFS;
		REG_BG2HOFS = cam.x * BG2_SCROLL_RATE;
		REG_BG2VOFS = cam.y * BG2_SCROLL_RATE + BG2_YOFFS;
		// update oam
		oam_copy(oam_mem, obj_buffer, active_objs);
	}

	return 0;
}


