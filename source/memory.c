#include <tonc.h>
#include "memory.h"

inline void updateVRAMFromMap(unsigned short* mapPtr, int bank0, int bank1) {
	int i;
	//might need to move this to DMA
	BLOCK *src, *dst0, *dst1;
	src= (BLOCK*)mapPtr;
	dst0= (BLOCK*)se_mem[bank0];
	dst1= (BLOCK*)se_mem[bank1];

	for(i=0; i<32; i++) {
		*dst0++= *src++;	 *dst0++= *src++;
		*dst1++= *src++;	 *dst1++= *src++;
	}	
}

inline unsigned int init_bg(
	TILE* tile_mem_addr, const unsigned int* tiles, const unsigned int tileslen, 
	const short unsigned int* map, int screenentrybegin, char charbaseblock) {
	memcpy(tile_mem_addr,tiles,tileslen);

	updateVRAMFromMap(map, screenentrybegin, screenentrybegin+1);

	return BG_CBB(charbaseblock) | BG_SBB(screenentrybegin) | BG_4BPP | BG_REG_64x32;
}