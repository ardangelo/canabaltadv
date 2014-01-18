#import <tonc.h>
#import "main.h"
#import "buildings.h"

inline void set_dtile(int x, int y, int offset) {

	//(0,0) is at bottom left of screen now

	platformsMap[2*x +   MAP_LENGTH * (MAP_HEIGHT -  2*y     )] = offset;
	platformsMap[2*x + 1+MAP_LENGTH * (MAP_HEIGHT -  2*y     )] = offset+1;
	platformsMap[2*x +   MAP_LENGTH * (MAP_HEIGHT - (2*y - 1))] = offset+2;
	platformsMap[2*x + 1+MAP_LENGTH * (MAP_HEIGHT - (2*y - 1))] = offset+3;
}

inline void score_to_tid(u32 *tid_array, int score) {
	int i;
	int pow10 = 1; //otherwise it goes too fast, change this to 1 if you want it as a debug display
	for (i = SCORE_LEN-1;i>=0;i--) {
		tid_array[i] = 37*8 + (int)((score/pow10)%10)*2;
		pow10 *= 10;
	}
}

inline void generate_building(struct BUILDING *building) {
	building->style = BS1;
	building->length = LEN_MAX; //randint(LEN_MIN,LEN_MAX);
	building->height = HEIGHT_MAX; //randint(HEIGHT_MIN,HEIGHT_MAX);
	building->gap = GAP_MAX; //randint(GAP_MIN,GAP_MAX);
}

inline void clear_buildings() {
	memset(platformsMap,0,sizeof(platformsMap));
}

/* drawStart specifies the point on the theoretical building to start drawing at offset, likewise for drawStop but for ending
*/
void draw_building(struct BUILDING *building, int locationOffset, int drawStart, int drawStop, int drawEdge) {
	int i,j;

	//if drawstart == 0
	if (drawStart == 0) {
		//draw top left corner
		set_dtile(locationOffset, building->height, building->style+TL);
	}
	//for drawstart+1 to drawstop
	for (i = 1; i < drawStop-drawStart; i++) {
		//draw top edge
		set_dtile(locationOffset+i, building->height, building->style+TE);
	}
	//if drawedge draw top right corner
	if (drawEdge) {
		set_dtile(locationOffset+(drawStop-drawStart), building->height, building->style+TR);
	}
	//for 1 to height
	for (i = 1; i < building->height; i++) {
		//if drawstart == 0
		if (drawStart == 0) {
			//draw left edge
			set_dtile(locationOffset, i, building->style+LE);
		}
		//for drawstart+1 to drawstop
		for (j = 1; j < drawStop-drawStart; j++) {
			//draw middle block
			set_dtile(locationOffset+j, i, building->style+MI);
		}
		//if drawedge draw right edge block
		if (drawEdge) {
			set_dtile(locationOffset+(drawStop-drawStart), i, building->style+RE);
		}
	}

	updateVRAMFromMap(platformsMap, 26, 27);
}