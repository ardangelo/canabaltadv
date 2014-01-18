//animation start frames
#define RUNNING 0
#define RUNSTART 0
#define RUNFRAMES 16

#define JUMPING 1
#define JUMPSTART 16*8
#define JUMPFRAMES 4

#define FALLING 2
#define FALLSTART 20*8
#define FALLFRAMES 6

#define ROLLING 3
#define ROLLSTART 26*8
#define ROLLFRAMES 11

#define FALLING_TO_DEATH 8

//settings
#define MAXJUMPTIME 10
#define SCORE_LEN 8
#define MAP_HEIGHT 32
#define MAP_LENGTH 64

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

struct PLAYER { //add obj_attr to this eventually
	int x, y, state;
	float vel;
	u32 tid, palbank, jumptime;
};

struct CAMERA {
	int x, y, vel;
};

//grit bg1.bmp bg2.bmp -gTff00ff -gB4 -mRtpf -pS -ftc
//grit platforms.bmp -gTff00ff -gB4 -ftc
//grit text.bmp player.bmp -ftc -pS -gTFF00FF