
#include <stdio.h>
#include <tonc.h>
#include <krawall.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

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

inline void set_dtile(int x, int y, int offset) {

	platformsMap[2*x+64*(y)] = offset;
	platformsMap[2*x+1+64*(y)] = offset+1;
	platformsMap[2*x+64*(y+1)] = offset+2;
	platformsMap[2*x+1+64*(y+1)] = offset+3;
}

inline int inl_clamp(int x, int lo, int hi) {
	if (x < lo) { return lo; }
	if (hi < x) { return hi; }
	return x;
}

inline void score_to_tid(u32 *tid_array, int score) {
	int i;
	int pow10 = 1; //otherwise it goes too fast, change this to 1 if you want it as a debug display
	for (i = SCORE_LEN-1;i>=0;i--) {
		tid_array[i] = 37*8 + (int)((score/pow10)%10)*2;
		pow10 *= 10;
	}
}

inline unsigned int init_bg(
	TILE* tile_mem_addr, const unsigned int* tiles, const unsigned int tileslen, 
	const short unsigned int* map, int screenentrybegin, char charbaseblock) {

	BLOCK *src, *dst0, *dst1;
	int i;

	memcpy(tile_mem_addr,tiles,tileslen);
	src= (BLOCK*)map;
	dst0= (BLOCK*)se_mem[screenentrybegin];
	dst1= (BLOCK*)se_mem[screenentrybegin + 1];
	for(i=0; i<32; i++) {
		*dst0++= *src++;	 *dst0++= *src++;
		*dst1++= *src++;	 *dst1++= *src++;
	}
	return BG_CBB(charbaseblock) | BG_SBB(screenentrybegin) | BG_4BPP | BG_REG_64x32;
}

void generate_building(struct BUILDING *building) {
	building->style = BS1;
	building->length = randint(11,13);
	building->height = randint(6,9);
	building->gap = randint(3,6);
}

void clear_buildings() {

	memset(platformsMap,0,sizeof(platformsMap));
}

void append_building(struct BUILDING *building, int offset) {
	int i = 0, j = 0;

	set_dtile(offset, 32-2*building->height, building->style + TL);
	for (i = 1;i<building->length;i++) {
		set_dtile(offset+i, 32-2*building->height, building->style + TE);
	}
	set_dtile(offset+building->length, 32-2*building->height, building->style + TR);
	for (i = 1;i<building->height;i++) {
		set_dtile(offset, 32-2*building->height+2*i, building->style + LE);
		for (j = 1;j<building->length;j++) {
			set_dtile(offset+j, 32-2*building->height+2*i, building->style + MI);
		}
		set_dtile(offset+building->length, 32-2*building->height+2*i, building->style + RE);
	}

	//might need to move this to DMA
	BLOCK *src, *dst0, *dst1;
	src= (BLOCK*)platformsMap;
	dst0= (BLOCK*)se_mem[26];
	dst1= (BLOCK*)se_mem[27];

	for(i=0; i<32; i++) {
		*dst0++= *src++;	 *dst0++= *src++;
		*dst1++= *src++;	 *dst1++= *src++;
	}	
	
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
	int p_x = 10, p_y = 0, p_s = RUNNING;
	float p_v = 0;
	u32 p_tid = 0, p_pb = 0;
	int c_x = 0, c_y = 0;
	u32 blend = 0x20;
	u32 score = 0;
	u32 digits_tid[SCORE_LEN];

	struct BUILDING *current = malloc(sizeof(struct BUILDING));
	struct BUILDING *next = malloc(sizeof(struct BUILDING));

	int platforms_x = 0, platforms_y = 0;
	
	oam_init(obj_buffer, 128);
	
	generate_building(current);
	append_building(current, 0);
	ground = 256-current->height*16 - 96;
	generate_building(next);
	append_building(next, current->length + current->gap);
	
	OBJ_ATTR *player = &obj_buffer[0];
	obj_set_attr(player, ATTR0_TALL, ATTR1_SIZE_32, ATTR2_PALBANK(p_pb) | p_tid);
	obj_set_pos(player, p_x, p_y);

	OBJ_ATTR *meter = &obj_buffer[1];
	obj_set_attr(meter, ATTR0_TALL, ATTR1_SIZE_8, ATTR2_PALBANK(p_pb) | (316));
	obj_set_pos(meter, (240-8*(SCORE_LEN+1))+8*SCORE_LEN, 0);

	OBJ_ATTR *digits[SCORE_LEN];
	for (i = 0;i<SCORE_LEN;i++) {
		digits[i] = &obj_buffer[i+2];
		obj_set_attr(digits[i], ATTR0_TALL, ATTR1_SIZE_8, ATTR2_PALBANK(p_pb) | digits_tid[i]);
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

		//check for ground
		if (current->length*16 < platforms_x + (p_x+12)) {
			ground = 256;
		}

		if (ground == 256) {
			if ((current->length*16 + current->gap*16 - platforms_x) < p_x+8) {

				//clear buildings and reset platforms_x to p_x
				clear_buildings();
				platforms_x = -(p_x+8);
				//current = next
				current = next;
				//reset ground
				ground = 256-current->height*16 - 96;
				//place current at beginning
				append_building(current,0);
				//generate next
				generate_building(next);
				//place next
				append_building(next, current->length + current->gap);
			}
		}

		if (p_y > 200-16) {
			swi_call(0x0);
		}

		//key handling
		c_x += 3*key_tri_horz();
		c_x = inl_clamp(c_y, 0, 4*256);
		c_y -= 3*key_tri_vert();
		c_y = inl_clamp(c_y, -32, 64);
		if (key_released(KEY_SELECT)) {
			p_y = -50;
			generate_building(current);
			append_building(current, 0);
			ground = 256-current->height*16 - 96;
		}
		if (p_s == RUNNING || p_s == ROLLING) {
			if (key_hit(KEY_A)) {
				p_s = JUMPING;
				p_tid = JUMPSTART;
				p_v = 6;
			}
		} else if (p_s == JUMPING) {
			//variable building->height jumping
		}

		//animation
		score_to_tid(digits_tid,score);

		if (!(vcount % 2)) {//EWW MOD
			p_tid += 8;
		}
		
		score += 3;
		platforms_x += 3;
		if (platforms_x > 512) {
			platforms_x = 0;
		}

		if (p_s == RUNNING) {
			if (p_tid == RUNSTART+8*RUNFRAMES)
				p_tid = RUNSTART;
		} else if (p_s == JUMPING) { //can your programming language do this?
			if (p_tid == JUMPSTART+8*JUMPFRAMES)
				p_tid = JUMPSTART;
		} else if (p_s == FALLING) {
			if (p_tid == FALLSTART+8*FALLFRAMES)
				p_tid = FALLSTART;
		} else if (p_s == ROLLING) {
			if (p_tid == ROLLSTART+8*ROLLFRAMES) {
				p_s = RUNNING;
				p_tid = RUNSTART;
			}
		}

		//movement
		p_y -= p_v;
		if (p_y != ground) {
			p_v -= .5;
		}
		if (p_y > ground) {
			if (p_v < -7) {
				p_s = ROLLING;
				p_tid = ROLLSTART;
			} else {
				p_s = RUNNING;
				p_tid = RUNSTART;
			}
			
			p_y = ground;
			p_v = 0;
		}
		if (p_v < 0 && p_s == JUMPING) {
			p_s = FALLING;
			p_tid = FALLSTART;
		}

		bg_x++;
		if (bg_x == 4*256)
			bg_x = 0;

		REG_BG1HOFS = platforms_x;
		REG_BG1VOFS = platforms_y + 64 - c_y;
		REG_BG2HOFS = bg_x;
		REG_BG2VOFS = (256+128-32-c_y)>>2;
		REG_BG3HOFS = bg_x>>1;
		//REG_BG3VOFS = (256-c_y)>>2;

		player->attr2= ATTR2_BUILD(p_tid, p_pb, 0);
		obj_set_pos(player, p_x, p_y + c_y);

		meter->attr2= ATTR2_BUILD(316, p_pb, 0);
		obj_set_pos(meter, (240-8*(SCORE_LEN+1))+8*SCORE_LEN, 0);

		for (i = 0;i<SCORE_LEN;i++) {
			digits[i]->attr2= ATTR2_BUILD(digits_tid[i], p_pb, 0);
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
