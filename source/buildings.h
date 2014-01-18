#ifndef _BUILDINGS_H
#define _BUILDINGS_H_ 

#define LEN_MIN 7
#define LEN_MAX 13//32dT - enoughdT - gapmaxdT
#define HEIGHT_MIN 6
#define HEIGHT_MAX 9
#define GAP_MIN 4
#define GAP_MAX 6
#define ENTIRE_BUILDING 0
#define ENOUGH_BUILDING 10//32dT - space before player in tiles. if we ever switch to camera movement on x plane this must be adjusted

//building tile style data
#define BS1 8

#define TL 12
#define TE 16
#define TR 20
#define LE 0
#define MI 4
#define RE 8

struct BUILDING {
	int style;
	int length;
	int height;
	int gap;
};

inline void set_dtile(int x, int y, int offset);

inline void score_to_tid(u32 *tid_array, int score);

inline void generate_building(struct BUILDING *building);

inline void clear_buildings();

void draw_building(struct BUILDING *building, int locationOffset, int drawStart, int drawStop, int drawEdge);

#endif