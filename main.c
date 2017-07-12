#define MUSIC 0

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

uint32_t frame_count;

build_t builds[BUILDS_AHEAD];
uint32_t starts[BUILDS_AHEAD];
uint32_t curr_build = 0;

crate_t crates[MAX_CRATES];
uint32_t curr_crate = 0;
int num_crates = 0;

#define CURR_BUILD (builds[curr_build])
#define NEXT_BUILD (builds[(curr_build + 1) % BUILDS_AHEAD])
#define LAST_BUILD (builds[(curr_build + (BUILDS_AHEAD-1)) % BUILDS_AHEAD])

// obj globals
OBJ_ATTR obj_buffer[MAX_OBJS];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;
int active_objs = MIN_OBJS;

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
	
	return (build_t){height, width, gap, style};
}

inline void draw_col(SCR_ENTRY* map, uint32_t col) {
	if (starts[curr_build] > col) {
		return;
	}
	for (int i = 0; i < BUILDS_AHEAD; i++) {
		int bn = (curr_build + i) % BUILDS_AHEAD;
		build_t *b = &builds[bn];
		if ((starts[bn] <= col) && (col < starts[bn] + b->width + b->gap)) {
			uint16_t tile = TILE_TRANSPARENT;
			for (int row = 0; row < WORLD_HEIGHT; row++) {
				if (row > (WORLD_HEIGHT - b->height)) { // TODO: find out why 4
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
				map[se_index_fast(col%64, row, REG_BG0CNT)] = SE_PALBANK(BUILDINGS_PB) | tile;
			}
			return;
		}
	}
}

static inline OBJ_ATTR* new_obj() {
	int i;
	for (i = 0; i < active_objs; i++) {
		if (!OBJ_VISIBLE(obj_buffer[i])) {
			DEBUGFMT("found an empty obj: %d", i);
			return &obj_buffer[i];
		}
	}
	DEBUG("expanding active objs");
	active_objs *= 2;
	if (active_objs > MAX_OBJS) {
		DEBUG("too many objs! resetting");
		swi_call(0x00);
	} else if (OBJ_VISIBLE(obj_buffer[i])) {
		DEBUG("you didn't clean up the objs! resetting");
		swi_call(0x00);
	}
	return &obj_buffer[i];
}

static inline void delete_sprite(sprite_t *s) {
	oam_init(s->obj, 1);
	s->obj = NULL;
	if ((active_objs / 2) < MIN_OBJS) { return; }
	for (int i = active_objs / 2; i < active_objs; i++) {
		if (OBJ_VISIBLE(obj_buffer[i])) {
			return;
		}
	}
	oam_init(&obj_buffer[active_objs / 2], active_objs - (active_objs / 2));
	active_objs /= 2;
}

static inline void place_sprite(sprite_t *s, camera_t *c) {
	bool exist = s->obj != NULL;
	int screen_x = SCREEN_X(*s, *c);
	int screen_y = SCREEN_Y(*s, *c);
	
	DEBUGFMT("sprite in world at %d, %d on screen at %d, %d, exist: %d, height: %d", s->x, s->height, screen_x, screen_y, exist, SPRITE_HEIGHT(*s));
	
	if ((screen_y + SPRITE_HEIGHT(*s) < 0) ||
	    (screen_y > SCREEN_HEIGHT) ||
	    (screen_x + SPRITE_WIDTH(*s) < 0) ||
	    (screen_x > SCREEN_WIDTH)) {
		if (exist) {
			DEBUG("sprite left! deleting it");
			delete_sprite(s);
		}
		return;
	} else {
		if (!exist) {
			DEBUG("sprite on screen and needs to be created");
			s->obj = new_obj();
		}
	}
	obj_set_attr(s->obj,
	             s->shape | ATTR0_REG,
	             s->size,
	             ATTR2_PALBANK(s->palbank) | s->tile);
	obj_set_pos(s->obj, screen_x, screen_y);
}

static inline void set_score(uint32_t score) {
	for (int i = 1; i < 8; i++) {
		obj_set_attr(score_objs[i],
		             ATTR0_TALL | ATTR0_REG,
		             ATTR1_SIZE_8,
		             ATTR2_PALBANK(0) | (TILE_ZERO + 2*(score % 10)));
		score /= 10;
		obj_set_pos(score_objs[i], SCREEN_WIDTH - PIXEL(i+1), 0);
	}
}

int main(void) {
	// set up irqs
	fnptr isr = NULL;
	irq_init(isr);
	irq_add(II_VBLANK, isr);
	
	// set up backgrounds tiles
	dma3_cpy(pal_bg_bank[0], buildingsPal, buildingsPalLen); // load colors into bgpal
	dma3_cpy(pal_bg_bank[1], midgroundPal, midgroundPalLen);
	dma3_cpy(pal_bg_bank[2], backgroundPal, backgroundPalLen);
	// 26-33 as screenblocks. 4 bits per pixel, 64x32 tiles
	// use block 0 as tile charblock
	dma3_cpy(&tile_mem[0][0], buildingsTiles, buildingsTilesLen); // block 1 as midground charblock
	dma3_cpy(&tile_mem[1][0], midgroundTiles, midgroundTilesLen); // block 2 background charblock
	dma3_cpy(&tile_mem[2][0], backgroundTiles, backgroundTilesLen); 

	SCR_ENTRY *bg0_map = se_mem[30];
	SCR_ENTRY *bg1_map = se_mem[28];
	SCR_ENTRY *bg2_map = se_mem[26];

 reset:
	// generate the starting buildings
	curr_build = 0;
	starts[0] = 0;
	builds[0] = generate_build();
	for (int i = 1; i < BUILDS_AHEAD; i++) {
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
	for (int i = 0; i < BG0_WIDTH; i++) {
		for (int j = 0; j < BG0_HEIGHT; j++) {
			bg1_map[se_index_fast(i, j, REG_BG1CNT)] = SE_PALBANK(MIDGROUND_PB) | midgroundMap[64*j+i];
			bg2_map[se_index_fast(i, j, REG_BG2CNT)] = SE_PALBANK(BACKGROUND_PB) | backgroundMap[64*j+i];
		}
	}

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_OBJ | DCNT_OBJ_1D;

	// load in the sprites
	oam_init(obj_buffer, 128);
	memcpy(pal_obj_mem, spritesPal, spritesPalLen);
	memcpy(&tile_mem[4][0], spritesTiles, spritesTilesLen);
	
	// set the starting sprites
	cam = (camera_t){0, 96, 5, 5};
	guy.s.obj = NULL;
	guy.s.x = 30; guy.s.height = PIXEL(CURR_BUILD.height) + 30;
	guy.vx = 0; guy.vy = 0; guy.ax = 0; guy.ax = 0;
	guy.state = RUN; guy.anim = ANIM_RUN;
	guy.s.shape = ATTR0_TALL;
	guy.s.size = ATTR1_SIZE_8;
	guy.s.palbank = 0;
	guy.s.tile = guy.anim.start;
	// score sprites
	for (int i = 0; i < 8; i++) {
		score_objs[i] = new_obj();
		obj_set_attr(score_objs[i],
		             ATTR0_TALL | ATTR0_REG,
		             ATTR1_SIZE_8,
		             ATTR2_PALBANK(0) | TILE_ZERO);
	}
	set_score(0);
	obj_set_attr(score_objs[0], 
	             ATTR0_TALL | ATTR0_REG,
	             ATTR1_SIZE_8,
	             ATTR2_PALBANK(0) | TILE_METER_MARK);
	obj_set_pos(score_objs[0], SCREEN_WIDTH - PIXEL(1), 0);

	// Scroll around some
	int horizon = (SCREEN_WIDTH >> 3);
	int ground = PIXEL(CURR_BUILD.height);

	while(1) {
		VBlankIntrWait();
		key_poll();

		// apply camera x adjustment
		int cam_delta_x = key_tri_horz() * cam.vx;
		cam.x += cam_delta_x;
		guy.s.x += cam_delta_x;
		
		int jump_requested = key_hit(KEY_A);
		int ascent_ended = key_released(KEY_A);

		// things we need to do when the player moves horizontally
		if (cam_delta_x > 0) {
			// TODO: did we hit a crate?
			
			// check if we stepped off the edge
			if ((guy.s.x >> 3) > starts[curr_build] + CURR_BUILD.width) { ground = -100; }
			// check if we just entered a new building
			if ((guy.s.x >> 3) + 1 >= starts[curr_build] + CURR_BUILD.width + CURR_BUILD.gap) {
				// generate new building and advance
				starts[curr_build] = starts[(curr_build + (BUILDS_AHEAD-1)) % BUILDS_AHEAD] + LAST_BUILD.width + LAST_BUILD.gap;
				builds[curr_build] = generate_build();

				// create crate objects if need to
				crates[curr_crate].s.obj = NULL;
				crates[curr_crate].s.x = PIXEL(starts[curr_build]);
				crates[curr_crate].s.height = PIXEL(CURR_BUILD.height);
				crates[curr_crate].s.shape = ATTR0_SQUARE;
				crates[curr_crate].s.size = ATTR1_SIZE_8;
				crates[curr_crate].s.palbank = 0;
				crates[curr_crate].s.tile = TILE_METER_MARK + 1;
				
				curr_build = (curr_build + 1) % BUILDS_AHEAD;
				curr_crate = (curr_crate + 1) % MAX_CRATES;
				num_crates++;

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
		
		// things we need to do when the player moves vertically
		player_state_t new_state = guy.state;
		
		if ((guy.state == FALL) &&
		    (abs((guy.s.height - SPRITE_HEIGHT(guy.s)) - ground) <= GROUND_THRESH)) {
			if (ROLL_THRESH > guy.vy) {
				new_state = ROLL;
			} else {
				new_state = RUN;
			}
			guy.vy = 0;
			guy.ay = 0;
			guy.s.height = ground + SPRITE_HEIGHT(guy.s);
			DEBUGFMT("snapping to ground: %d", ground);
		}

		// update player state
		switch (guy.state) {
		case RUN:
		case ROLL:  // should we start falling
			if (guy.s.height - SPRITE_HEIGHT(guy.s) > ground) {
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
			if (guy.s.height < 0) {
				new_state = DEAD;
				guy.vy = 0;
				guy.ay = 0;
				DEBUG("died! resetting");
				goto reset;
			}
			break;
		default:
			break;
		}

		// get next frame of animation
		frame_count++;
		if (new_state == guy.state) {
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
		guy.s.height += (int)guy.vy;
		DEBUGFMT("new guy height: %d, vel: %d, ground: %d dist: %d", guy.s.height, (int)guy.vy, ground, guy.s.height - SPRITE_HEIGHT(guy.s) - ground);
		
		// apply camera y adjustments
		if ((SCREEN_Y(guy.s, cam) > LOWER_SLACK) ||
		    (SCREEN_Y(guy.s, cam) < UPPER_SLACK)) { 
			cam.y -= (int)guy.vy;
			cam.y = CLAMP(cam.y, 0, PIXEL(WORLD_HEIGHT) - SCREEN_HEIGHT);
		}
		
		// apply player attributes
		guy.s.tile = guy.anim.start + 2*guy.anim.frame;
		place_sprite(&guy.s, &cam);

		// apply crate attributes
		for (int i = 0; i < MAX_CRATES; i++) {
			if (crates[i].s.obj != NULL) {
				if (crates[i].hit) {
					// TODO: make crate fall
				}
				place_sprite(&crates[i].s, &cam);
			}
		}

		set_score(PIXEL(WORLD_HEIGHT) - SCREEN_HEIGHT - ground + cam.y);//cam.x >> 3);

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


