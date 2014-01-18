#ifndef _MAIN_H_
#define _MAIN_H_

unsigned short platformsMap[2048] __attribute__((aligned(4)));

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

#endif