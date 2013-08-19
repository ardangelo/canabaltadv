
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

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

volatile int gamelogicRunning = 0;
volatile int kramWorkerCallNeeded = 0;
unsigned short platformsMap[2048] __attribute__((aligned(4))) = {0};

inline int randint(int min, int max) {
	return rand() % (max-min) + min;
}

inline void set_dtile(int x, int y, int offset) {
	platformsMap[2*x+64*(y+1)] = offset;
	platformsMap[2*x+1+64*(y+1)] = offset+1;
	platformsMap[2*x+64*(y+2)] = offset+2;
	platformsMap[2*x+1+64*(y+2)] = offset+3;
}

void generate_building(struct BUILDING *building) {
	building->style = BS1;
	building->length = randint(5,8);
	building->height = randint(5,8);
	building->gap = randint(2,5);
}

void append_building(struct BUILDING *building, int offset) {
	memset(platformsMap,0,sizeof(platformsMap));
	int i = 0, j = 0;

	set_dtile(offset,16-building->height,building->style + TL);
	for (i=1;i<building->length;i++) {
		set_dtile(offset+i,16-building->height,building->style + TE);
	}
	set_dtile(offset+building->length,16-building->height,building->style + TR);
	for (i=18-building->height;i<32;i+=2) {
		set_dtile(offset,i,building->style + LE);
		for (j=offset+1;j<offset+building->length;j++) {
			set_dtile(j,i,building->style + MI);
		}
		set_dtile(offset+building->length,i,building->style + RE);
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
	int vcount = 0, bg_x = 0, ground;
	int p_x, p_y, p_s;
	float p_v;
	u32 p_tid, p_pb;

	struct BUILDING *current = malloc(sizeof(struct BUILDING));

	int platforms_x = 0, platforms_y = 0;
	
	oam_init(obj_buffer, 128);
	ground = 160-32;
	p_x = 0;
	p_y = 0;
	p_v = 0;
	p_s = RUNNING;
	p_tid = 0;
	p_pb = 0;
	OBJ_ATTR *player = &obj_buffer[0];
	obj_set_attr(player, ATTR0_TALL, ATTR1_SIZE_32, ATTR2_PALBANK(p_pb) | p_tid);
	obj_set_pos(player, p_x, p_y);

	while(1) {
		VBlankIntrWait();
		key_poll();
		vcount++; //using REG_VCOUNT makes irregular animation, look into it
		if (vcount == 60)
			vcount = 0;

		//animation
		if (!(vcount % 2)) {//EWW MOD
			p_tid += 8;
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
			p_s = ROLLING;
			p_tid = ROLLSTART;
			p_y = ground;
			p_v = 0;
		}
		if (p_v < 0 && p_s == JUMPING) {
			p_s = FALLING;
			p_tid = FALLSTART;
		}

		//key handling
		//p_x += key_tri_horz();
		if (key_released(KEY_SELECT)) {
			//swi_call(0x0);
			p_y = -50;
			generate_building(current);
			append_building(current, 0);
			ground = 256-current->height*32-32;
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

		bg_x++;
		if (bg_x == 4*256)
			bg_x = 0;
		REG_BG1HOFS = platforms_x;
		REG_BG1VOFS = platforms_y;
		REG_BG2HOFS = bg_x;
		REG_BG2VOFS = (p_y+32)>>1;
		REG_BG3HOFS = bg_x>>1;
		REG_BG3VOFS = (p_y+64)>>2;

		player->attr2= ATTR2_BUILD(p_tid, p_pb, 0);
		obj_set_pos(player, p_x, p_y);
		oam_copy(oam_mem, obj_buffer, 1); 

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
	kragInit( KRAG_INIT_STEREO );					// init krawall
	krapPlay( &mod_sanic, KRAP_MODE_LOOP, 0 );	// play module

	BLOCK *src, *dst0, *dst1;
	int i;

	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D | DCNT_MODE0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;

	memcpy(pal_bg_bank[0],SharedPal,SharedPalLen);
	memcpy(&tile_mem[0][0],bg1Tiles,bg1TilesLen);
	src= (BLOCK*)bg1Map;
	dst0= (BLOCK*)se_mem[30];
	dst1= (BLOCK*)se_mem[31];
	for(i=0; i<32; i++) {
		*dst0++= *src++;	 *dst0++= *src++;
		*dst1++= *src++;	 *dst1++= *src++;
	}
	REG_BG2CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32;

	memcpy(&tile_mem[1][0],bg2Tiles,bg2TilesLen);
	src= (BLOCK*)bg2Map;
	dst0= (BLOCK*)se_mem[28];
	dst1= (BLOCK*)se_mem[29];
	for(i=0; i<32; i++) {
		*dst0++= *src++;	 *dst0++= *src++;
		*dst1++= *src++;	 *dst1++= *src++;
	}
	REG_BG3CNT = BG_CBB(1) | BG_SBB(28) | BG_4BPP | BG_REG_64x32;

	memcpy(pal_bg_bank[1],platformsPal,platformsPalLen);
	se_mem[26][0] = SE_PALBANK(1);
	memcpy(&tile_mem[2][0],platformsTiles,platformsTilesLen);
	src= (BLOCK*)platformsMap;
	dst0= (BLOCK*)se_mem[26];
	dst1= (BLOCK*)se_mem[27];	//might have to dma this when it gets to dynamic
	for(i=0; i<32; i++) {
		*dst0++= *src++;	 *dst0++= *src++;
		*dst1++= *src++;	 *dst1++= *src++;
	}
	REG_BG1CNT = BG_CBB(2) | BG_SBB(26) | BG_4BPP | BG_REG_64x32;

	memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
	memcpy(pal_obj_mem, playerPal, playerPalLen);
	
	game_loop();

	return 0;
}
