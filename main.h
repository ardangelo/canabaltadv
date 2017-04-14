// data structs
typedef struct camera {
	int x, y;
	float vx, vy;
} camera;

typedef struct animation {
	int frame, start, len;
} animation;

typedef struct player {
	OBJ_ATTR *obj;
	int x, y, height;
	float vx, vy, ax, ay;
	enum {RUN, JUMP, FALL, ROLL, DEAD} state;
	animation anim;
	int anim_start, anim_frame, anim_len;
} player;

typedef struct {
	byte tl, tm, tr, bl, bm, br;
} build_style;

typedef struct {
	uint8_t height;
	uint8_t width;
	uint8_t gap;
	build_style style;
} build;

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

// animation stuff

#define TILE_METER_MARK 0
#define TILE_ZERO 2

#define ANIM_RUN (animation){0, 22, 16}
#define ANIM_JUMP (animation){0, 54, 4}
#define ANIM_FALL (animation){0, 62, 6}
#define ANIM_ROLL (animation){0, 74, 11}

#define TILE_TRANSPARENT 0
#define BUILD_S0 (build_style){1,2,3,4,5,6}
#define TILE_SKY 7
