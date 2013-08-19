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

#define MAXJUMPVEL 12

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

//grit bg1.bmp bg2.bmp -gTff00ff -gB4 -ftc -mRtpf -pS
//grit platforms.bmp -gTff00ff -gB4 -ftc