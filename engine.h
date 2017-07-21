#ifndef _ENGINE_H_
#define _ENGINE_H_

char *dbg_str;

/*
#define ENGINE_DEBUG(str) (nocash_puts(str))
#define ENGINE_DEBUGFMT(fmt, ...) do {	  \
		asprintf(&dbg_str, fmt, __VA_ARGS__); \
		nocash_puts(dbg_str); \
		free(dbg_str); \
	} while (0)
*/

#define ENGINE_DEBUG(fmt, ...)
#define ENGINE_DEBUGFMT(fmt, ...)

// types
typedef struct {
	int x, y;
	float vx, vy;
} camera_t;

typedef struct {
	OBJ_ATTR *obj;
	int x, height;
	uint16_t shape, size;
	short palbank, tile;
} sprite_t;

// protos
void init_sprites();
void copy_objs();
OBJ_ATTR* new_obj();
void place_sprite(sprite_t *s, camera_t *c);
void delete_sprite(sprite_t *s);
void copy_sprites();

// allocations
#define MIN_OBJS 16
#define MAX_OBJS 128

// graphics info
#define WORLD_HEIGHT 32
#define SCREEN_HEIGHT 160
#define SCREEN_WIDTH 240
#define PIXEL(x) ((x)*8)
#define SCREEN_X(s, c) ((s).x - (c).x)
#define SCREEN_Y(s, c) (PIXEL(WORLD_HEIGHT) - (s).height - (c).y)
#define OBJ_VISIBLE(obj) (((obj).attr0 & 0xFF00) != ATTR0_HIDE)
/*
shape\size  0000  4000  8000  C000 
0000         8x8 16x16 32x32 64x64 
4000        16x8  32x8 32x16 64x32 
8000        8x16  8x32 16x32 32x64 */
static uint16_t attr_widths[3] = { 0x6543, 0x6554, 0x5433 };
static uint16_t attr_heights[3] = { 0x6543, 0x5433, 0x6554 };
// idx = (s).shape >> 14; offs = ((s).size >> 14) << 2;
// final = 1 << (attr_arr[idx] >> offs) & 0xF;
#define SPRITE_WIDTH(s) (1 << ((attr_widths[(s).shape >> 14] >> ((s).size >> 12)) & 0xF))
#define SPRITE_HEIGHT(s) (1 << ((attr_heights[(s).shape >> 14] >> ((s).size >> 12)) & 0xF))

#endif
