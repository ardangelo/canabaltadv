
#include <stdio.h>
#include <tonc.h>
#include <krawall.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

#include "memory.h"
#include "buildings.h"

#include "modules/modules.h"
#include "modules/samples.h"
#include "modules/instruments.h"

#include "bmp/bg1.h"
#include "bmp/bg2.h"
#include "bmp/platforms.h"

#include "bmp/player.h"
#include "bmp/text.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

volatile int gamelogicRunning = 0;
volatile int kramWorkerCallNeeded = 0;
unsigned short platformsMap[2048] __attribute__((aligned(4))) = {0};

inline int randint(int min, int max) {
	return rand() % (max-min) + min;
}

inline int inl_clamp(int x, int lo, int hi) {
	if (x < lo) { return lo; }
	if (hi < x) { return hi; }
	return x;
}

void vblank() {
	if( !gamelogicRunning ) {
		kramWorkerCallNeeded = 0;
		krapInstProcess();	  // update sfx-instruments
		kramWorker();			// do the stuff
	} else {
		kramWorkerCallNeeded = 1;
	}
}

void game_loop() {
	int i = 0, vcount = 0, bg_x = 0, ground;

	u32 blend = 0x20;
	u32 score = 0;
	u32 digits_tid[SCORE_LEN];

	struct BUILDING *current = malloc(sizeof(struct BUILDING));
	struct BUILDING *next = malloc(sizeof(struct BUILDING));

	struct PLAYER *player = malloc(sizeof(struct PLAYER));
	player->x = 16; player->y = 0; player->state = RUNNING; //player intial state
	player->vel = 0;
	player->tid = 0; player->palbank = 0; player->jumptime = 0;

	struct CAMERA *camera = malloc(sizeof(struct CAMERA));
	camera->x = 0; camera->y = 0; camera->vel = 3;

	int platforms_x = 0, platforms_y = 0;
	
	oam_init(obj_buffer, 128);
	
	generate_building(current);
	draw_building(current, 0, 0, current->length, 1);
	ground = 256-current->height*16 - 96;
	generate_building(next);
	draw_building(next, current->length + current->gap, 0, ENOUGH_BUILDING, 0);
	
	OBJ_ATTR *player_obj = &obj_buffer[0];
	obj_set_attr(player_obj, ATTR0_TALL, ATTR1_SIZE_32, ATTR2_PALBANK(player->palbank) | player->tid);
	obj_set_pos(player_obj, player->x, player->y);

	OBJ_ATTR *meter = &obj_buffer[1];
	obj_set_attr(meter, ATTR0_TALL, ATTR1_SIZE_8, ATTR2_PALBANK(player->palbank) | (316));
	obj_set_pos(meter, (240-8*(SCORE_LEN+1))+8*SCORE_LEN, 0);

	OBJ_ATTR *digits[SCORE_LEN];
	for (i = 0;i<SCORE_LEN;i++) {
		digits[i] = &obj_buffer[i+2];
		obj_set_attr(digits[i], ATTR0_TALL, ATTR1_SIZE_8, ATTR2_PALBANK(player->palbank) | digits_tid[i]);
		obj_set_pos(digits[i], (240-8*(SCORE_LEN+1))+8*i, 0);
	}

	REG_BG3VOFS = 64;

	while(1) {
		VBlankIntrWait();
		key_poll();
		vcount++; //using REG_VCOUNT makes irregular animation, look into it
		if (vcount == 60)
			vcount = 0;

		if (blend) {
			BFN_SET(REG_BLDCNT, 3, BLD_MODE);
    		REG_BLDY= BLDY_BUILD(blend/2);
    		blend--;
		}

		//check for ground and first boundary
		if (current->length*16 < platforms_x + (player->x)) { //in between buildings
			ground = 256;
			//unload map
			//clear_buildings();
			//reset platforms_x to player_x
			//platforms_x = -(player->x+8);
			//draw enough of current building
			//fill rest of map with next building
		}

		//boundary 2: enter next
		if (ground == 256) {
			if ((current->length*16 + current->gap*16 - platforms_x) < player->x+8) {

				if (player->y - 16 > 256-next->height*16 - 96) { //16 for lenience
					player->state = FALLING_TO_DEATH;
				}

				//clear buildings and reset platforms_x to player->x
				clear_buildings();
				platforms_x = -(player->x+8);
				//current = next
				current = next;
				//reset ground
				ground = 256-current->height*16 - 96;
				//place current at beginning
				draw_building(current, 0, 0, current->length, 1);
				//generate next
				generate_building(next);
				//place next
				draw_building(next, current->length + current->gap, 0, ENOUGH_BUILDING, 0);
			}

		}

		if (player->y > 200-16) {
			swi_call(0x0);
		}

		//key handling
		camera->x += 3*key_tri_horz();
		camera->x = inl_clamp(camera->x, 0, 4*256);
		camera->y -= 3*key_tri_vert();
		camera->y = inl_clamp(camera->y, -32, 64);
		if (key_released(KEY_SELECT)) {
			player->y = -50;
			generate_building(current);
			draw_building(current, 0, 0, current->length, 1);
			ground = 256-current->height*16 - 96;
		}
		if ((player->state == RUNNING || player->state == ROLLING) && player->vel >= -3) {
			if (key_hit(KEY_A)) {
				player->state = JUMPING;
				player->tid = JUMPSTART;
				player->vel = 5;
				player->jumptime = 0;
			}
		} else if (player->state == JUMPING) {
			//variable building->height jumping
			if (key_is_down(KEY_A) && player->jumptime < MAXJUMPTIME) {
				player->vel = 5;
				player->jumptime++;
			}
		}

		//animation
		score_to_tid(digits_tid,current->length); //for debug display enter variable here

		if (!(vcount & 0x1)) {//mod has been removed
			player->tid += 8;
			if (player->state == FALLING_TO_DEATH) {
				if (camera->vel)
					camera->vel = 0;
			}
		}
		
		score += (int)(camera->vel/2);
		platforms_x += camera->vel;
		if (platforms_x > 512) {
			platforms_x = 0;
		}

		if (player->state == RUNNING) {
			if (player->tid == RUNSTART+8*RUNFRAMES)
				player->tid = RUNSTART;
		} else if (player->state == JUMPING) { //can your programming language do this?
			if (player->tid == JUMPSTART+8*JUMPFRAMES)
				player->tid = JUMPSTART;
		} else if (player->state == FALLING) {
			if (player->tid == FALLSTART+8*FALLFRAMES)
				player->tid = FALLSTART;
		} else if (player->state == ROLLING) {
			if (player->tid == ROLLSTART+8*ROLLFRAMES) {
				player->state = RUNNING;
				player->tid = RUNSTART;
			}
		}

		//movement
		player->y -= player->vel;
		if (player->y != ground) {
			player->vel -= .5;
		}
		if (player->state != FALLING_TO_DEATH) {
			if (player->y > ground) {
				if (player->vel < -9) {
					player->state = ROLLING;
					player->tid = ROLLSTART;
				} else {
					player->state = RUNNING;
					player->tid = RUNSTART;
				}
				
				player->y = ground;
				player->vel = 0;
			}
		}
		if (player->vel < 0 && player->state == JUMPING) {
			player->state = FALLING;
			player->tid = FALLSTART;
		}

		bg_x++;
		if (bg_x == 4*256)
			bg_x = 0;

		REG_BG1HOFS = platforms_x;
		REG_BG1VOFS = platforms_y + 64 - camera->y;
		REG_BG2HOFS = bg_x;
		REG_BG2VOFS = (256+128-32-camera->y)>>2;
		REG_BG3HOFS = bg_x>>1;
		//REG_BG3VOFS = (256-camera->y)>>2;

		player_obj->attr2= ATTR2_BUILD(player->tid, player->palbank, 0);
		obj_set_pos(player_obj, player->x, player->y + camera->y);

		meter->attr2= ATTR2_BUILD(316, player->palbank, 0);
		obj_set_pos(meter, (240-8*(SCORE_LEN+1))+8*SCORE_LEN, 0);

		for (i = 0;i<SCORE_LEN;i++) {
			digits[i]->attr2= ATTR2_BUILD(digits_tid[i], player->palbank, 0);
			obj_set_pos(digits[i], (240-8*(SCORE_LEN+1))+8*i, 0);
		}
		oam_copy(oam_mem, obj_buffer, 2+SCORE_LEN); 

		gamelogicRunning = 1;
		if( kramWorkerCallNeeded ) {
			krapInstProcess();	  // update sfx-instruments
			kramWorker();			// do the stuff
		}
		gamelogicRunning = 0;
	}
}

int main() {

	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_TIMER1, kradInterrupt);
	irq_add(II_VBLANK, vblank);

	REG_BLDCNT = BLD_BUILD(BLD_OBJ | BLD_BG0 | BLD_BG1 | BLD_BG2 | BLD_BG3, BLD_BG3, 3);
	BFN_SET(REG_BLDCNT, 3, BLD_MODE);
    REG_BLDY= BLDY_BUILD(15);

	REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D | DCNT_MODE0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;

	memcpy(pal_bg_bank[0],SharedPal,SharedPalLen);
	REG_BG2CNT = init_bg(&tile_mem[0][0],bg1Tiles,bg1TilesLen,bg1Map,30,0);
	REG_BG3CNT = init_bg(&tile_mem[1][0],bg2Tiles,bg2TilesLen,bg2Map,28,1);

	memcpy(pal_bg_bank[1],platformsPal,platformsPalLen);
	REG_BG1CNT = init_bg(&tile_mem[2][0],platformsTiles,platformsTilesLen,platformsMap,26,2);

	memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
	memcpy(&tile_mem[4][37*8], textTiles, textTilesLen);
	memcpy(pal_obj_mem, SharedObjPal, SharedObjPalLen);

	kragInit( KRAG_INIT_STEREO );					// init krawall
	krapPlay( &mod_sanic, KRAP_MODE_LOOP, 0 );	// play module
	
	game_loop();

	return 0;
}
