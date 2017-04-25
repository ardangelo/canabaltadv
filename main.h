// data structs
typedef struct {
	int x, y;
	float vx, vy;
} camera_t;

typedef struct {
	uint frame, start, len;
} animation_t;

typedef struct {
	OBJ_ATTR *obj;
	uint x, y, height;
	float vx, vy, ax, ay;
	enum {RUN, JUMP, FALL, ROLL, DEAD} state;
	animation_t anim;
	uint anim_start, anim_frame, anim_len;
} player_t;

typedef struct {
	OBJ_ATTR *obj;
	uint x, y, height, offset; // offset is the offset from the left edge of the building
	float vy;
	uint hit, style;
} crate_t;

typedef struct {
	byte tl, tm, tr, bl, bm, br;
} build_style_t;

#define MAX_CRATES 8
typedef struct {
	uint8_t height;
	uint8_t width;
	uint8_t gap;
	build_style_t style;
	crate_t crates[MAX_CRATES];
} build_t;

// graphics info
#define PIXEL(x) (x*8)

// bg globals
#define WORLD_HEIGHT 32
#define BG0_HEIGHT 32
#define BG0_WIDTH 64

// tunables
#define UPPER_SLACK 40
#define LOWER_SLACK 80

#define GRAV -.2
#define TERMINAL_VELOCITY 30*GRAV
#define JUMP_START_VEL -30*GRAV
#define JUMP_END_VEL -13*GRAV
#define DEATH_BOUNDARY 8
#define ROLL_THRESH .9*TERMINAL_VELOCITY
#define GROUND_THRESH 4

#define CRATE_OBJ_START 10
#define CRATE_GRAV -.12
#define CRATE_TERMINAL_VELOCITY 30*CRATE_GRAV
#define CRATE_HIT_VY -1
#define CRATE_HIT_VX 4

#define BG1_SCROLL_RATE .5
#define BG1_YOFFS 30
#define BG2_SCROLL_RATE .25
#define BG2_YOFFS 50

// animation stuff

#define TILE_METER_MARK 0
#define TILE_ZERO 2

#define ANIM_RUN (animation_t){0, 22, 16}
#define ANIM_JUMP (animation_t){0, 54, 4}
#define ANIM_FALL (animation_t){0, 62, 6}
#define ANIM_ROLL (animation_t){0, 74, 11}

#define TILE_TRANSPARENT 0
#define BUILD_S0 (build_style_t){1,2,3,4,5,6}
#define TILE_SKY 7
