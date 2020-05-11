#include <allegro.h>

#define BLUE (5,209,255)

BITMAP *background;
BITMAP *buffer;

const int WIDTH = 640;
const int HEIGHT = 480;
const int MAXSPEED = 8;

bool gameover = false;
void drawbar(int num);
void erasebar(int num);
void movebar(int num);
void moveup(int num);
void movedown(int num);
void setupbar();
void setupscreen();
void collision();
void setupBalls();
void drawBalls();
void eraseBalls();
void updateBalls();
void resetGame();
void checkWinner();
void getinput();

struct BouncingBall
{
       int color, radius;
       int x,y;
       int velocityX;
       int velocityY;
       int gravity;
       float dt;
};
BouncingBall ball;

class Bar
{
public:

	int x;
	int y;
	int color;
	int speed;
	int dir;
};

//Declare two paddles
Bar bar[2];

void setupscreen()
{
     int ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
     if(ret != 0)
     {
            allegro_message(allegro_error);
            return;
     }
     
     // Draws a red box around play area. Replaced with BITMAP currently
     //rect(screen, 50, 50, 590, 430, makecol(255, 0, 0));
}

MIDI *music;

int dirA;
int dirB;
int width = 150;
int height = 192;
int score[2] = {0, 0};
int hits = 0;
