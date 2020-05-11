#include "functions.h"

int main()
{
    allegro_init();
    install_keyboard();
    install_timer();
    setupscreen();
    setupbar();
    setupBalls();
    drawBalls();
    
    srand(time(NULL));
    
    // Installs Sound Driver
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
    {
                                      // Print error message
                                      allegro_message("Error Initializing Sound\n%s\n", allegro_error);
                                      return(1);
    }
    
    // Loads the MIDI file
    music = load_midi("rickroll.mid");
    if(!music)
    {
              allegro_message("Error Loading Audio Files!");
              return 1;
    }
    
    // Plays the Music
    if(play_midi(music, 0) != 0)
    {
                        allegro_message("Error playing Song\n%s", allegro_error);
                        return 1;
    }
    
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    background = load_bitmap("background.bmp", NULL);
    
    // main loop
    while (score[0] != 5 && score[1] != 5 && !key[KEY_ESC])
    {
          blit(background, buffer, 0,0,0,0, background->w, background->h); // background points to width and height
          textprintf_ex(buffer, font, 12, 465, BLUE, -1, "P1 Score: %d            -          Hits: %d           -        P2 Score: %d", score[0], hits, score[1]);
          textprintf_ex(buffer, font, 260, 10, BLUE, -1, " ALLEGRO PONG ");
          eraseBalls();
          
          erasebar(0);
          erasebar(1);
          
          movebar(0);
          movebar(1);
          
          drawbar(0);
          drawbar(1);
          rest(3);
          
          if(keypressed())
          {
                          getinput();
          }
          
          acquire_screen();
          updateBalls();
          collision();
          drawBalls();
          checkWinner();
          blit(buffer, screen, 0,0,0,0,buffer->w, buffer->h); // buffer pointing to width and height
          release_screen();
          
          /*while(keypressed())
          {
                             switch(readkey() >> 8)
                             {
                                              case KEY_ESC:
                                                   score[1] = score[2] = 5;
                                                   break;
                             }
          }*/
          
    }
    destroy_bitmap(background);
    destroy_bitmap(buffer);
    allegro_exit();
    return 0;
}
END_OF_MAIN()


// Wall Collisions
void collision()
{
     // Ball hits the top boundary
     if (ball.y -10 < 50)
     {
                ball.velocityY = -ball.velocityY;
     }
     
     // Ball hits the bottom boundary
     if (ball.y +ball.radius > 425)
     {
                ball.velocityY = -ball.velocityY;
     }
     
     // Ball hits the right boundary
     if (ball.x +ball.radius > 600)
     {
                readkey(); // Pauses game when someone scores
                ball.velocityX = -ball.velocityX;
                hits++;
                score[0]++;
     }
     
     // Ball hits the left boundary
     if (ball.x - ball.radius < 40)
     {
                readkey(); // Pauses game when someone scores
                ball.velocityX = -ball.velocityX;
                hits++;
                score[1]++;
     }
     
     // Ball hits the left bar
     if (ball.x - ball.radius < 105 && ball.y - ball.radius < bar[0].y+30 && ball.y - ball.radius > bar[0].y-80)
     {
                ball.velocityX = -ball.velocityX;
                hits++;
     }     
     
     // Ball hits the right bar
     if (ball.x - ball.radius > 525 && ball.y - ball.radius < bar[1].y+30 && ball.y - ball.radius > bar[1].y-60)
     {
                ball.velocityX = -ball.velocityX;
                hits++;
     }
}

void setupbar()
{
	//Set up the left bar first
	bar[0].x = 90;
	bar[0].y = 255;
	bar[0].color = 8;
	bar[0].speed = 0;
	bar[0].dir = 1;


	//Set up the right bar
	bar[1].x = 540;
	bar[1].y = 255;
	bar[1].color = 8;
	bar[1].speed = 0;
	bar[1].dir = 3;
}

//Draws the bars on screen
void drawbar(int num)
{
	int x = bar[num].x;
	int y = bar[num].y;
	int barColor = bar[num].color;

	//Draw the paddles
	rectfill(buffer, x+15, y+30, x, y-50, barColor);
}

//Erase the bar from screen
void erasebar(int num)
{
     //Capture the bar in a rectangle
	int bottom = bar[num].y+30;
	int top = bar[num].x+15;
	int left = bar[num].y-50;
	int right = bar[num].x;
	
	//Erase the bar
	rectfill(buffer, top, bottom, right, left, 0);
}

void movebar(int num)
{
	int dir = bar[num].dir;
	int speed = bar[num].speed;

	//Update the bar positions based on direction
	switch(dir)
	{
	   case 1:
		   bar[num].y+= speed;

	   case 3:
		   bar[num].y+= speed;
	}

	//Keep the paddles within the screen
	if(bar[num].y+50> SCREEN_H-35)
	{
		bar[num].y = SCREEN_H-85;
		bar[num].speed = 0;
	}

	if(bar[num].y < 105)
	{
		bar[num].y = 105;
		bar[num].speed = 0;
	}
}

void getinput()
{
	if(key[KEY_ESC])
		gameover = 1;

//Controls for Right bar
	//Move Up
	if(key[KEY_UP])
		moveup(1);

	//Move Down
	if(key[KEY_DOWN])
		movedown(1);

	
//Controls for the Left bar
	//move Up
	if(key[KEY_W])
		moveup(0);

	//move Down
	if(key[KEY_S])
		movedown(0);
}


void movedown(int num)
{
	bar[num].speed++;
	if(bar[num].speed > MAXSPEED)
		bar[num].speed = MAXSPEED;
}

void moveup(int num)
{
	bar[num].speed--;
	if(bar[num].speed < -MAXSPEED)
		bar[num].speed = -MAXSPEED;
}

void setupBalls()
{ 
     ball.color= 0; 
     ball.radius = 6; // Ball Size
     ball.x= 310; // Ball starts in center of X
     ball.y= 225; // Ball starts in Center of Y
     ball.velocityX = 2;
     ball.velocityY = 1.9;
     ball.gravity = 0;
     ball.dt = 1;
}

void drawBalls()
{
     circlefill(screen, ball.x, ball.y, ball.radius, ball.color);
}

void eraseBalls()
{
     circlefill(screen, ball.x, ball.y, ball.radius, 0); 
}

void updateBalls()
{
     ball.velocityY = ball.velocityY + ball.gravity*ball.dt;
     ball.x = ball.x + ball.velocityX * ball.dt;
     ball.y = ball.y + ball.velocityY * ball.dt;
}

void resetGame()
{
     // Clear keyboard buffer that holds previously declared keyboard inputs before reading key inputs
     clear_keybuf();
     readkey();
     
     // Clear background
     clear_to_color (buffer, makecol(5, 209, 255));
     
     // Reset ball position
     ball.x = 310;
     ball.y = 225;
     
     //Reset paddle position
     bar[0].x = 90;
     bar[0].y = 255;
     
     bar[1].x = 540;
     bar[1].y = 255;
     
     ball.velocityX = 2;
     hits = 0; 
      
}

// Stops at 5 Points. ESC to exit, any other key to continue 
void checkWinner()
{
     if (score[0] ==5)
     {           
          clear_keybuf();
          readkey();
          score[0] = 0;
          score[1] = 0;
          resetGame();
     }  
   else
        if(score[1] == 5)
        {   
           clear_keybuf();
           readkey();
           score[0] = 0;
           score[1] = 0;
           resetGame();
        }        
}

