#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "uart.h"
#include "cmd.h"



int main()
{
  sei(); // turns on interrupts
  uart_init();
  cmd_init();

  int x = 15; // default values
  int y = 15;

  enum directions snake_dir = UP;
  int snake_len = 2;
  unsigned char snake_bod[x*y][2];

  char apple_x = 2;
  char apple_y = 2;

  bool game_over = false;


  snake_bod[0][0] = x / 2; // sets first position of head
  snake_bod[0][1] = y / 2;

  snake_bod[1][0] = snake_bod[0][0];    // sets the position of the second peaece
  snake_bod[1][1] = snake_bod[0][1]+1;  // maybe i dont even need this

  //char game_screen[x][y];


  printf("CMD Snek 0.0001v \n");
  /*
  printf("Enter game size (x, y): ");

  while (!line_done) {}

  sscanf(line, "%i %i", &x, &y);
  */

  line_done = true; // disables user input echo


  //lastest_c = 'b';  // so that it says press enter to continue
  printf("press enter to continue \r");
  while (lastest_c != 0x0a) {}
  printf("                        \r");


  // create the game screen

  for(int i = 0; i < y+2; i++)
  {
    printf("|");
    for(int j = 0; j < x; j++)
    {
      if(i == 0 || i == y+1)
        printf("=");
      else
        printf(" ");
    }
    printf("|\n");
  }

  for(int i = 0; i < y+1; i++)
  {  // resets the cursor to field 1:1
    move_cursor(UP);
  }
  move_cursor(RIGHT);
  // ======================

  while(1)
  {   // gameloop essentially

    switch (lastest_c)
    {   // determens the direction of the snake
      case 0x41:  // up
        if(snake_dir != DOWN)
          snake_dir = UP;
        break;
      case 0x42:  // DOWN
        if(snake_dir != UP)
          snake_dir = DOWN;
        break;
      case 0x43:  // RIGHT
        if(snake_dir != LEFT)
          snake_dir = RIGHT;
        break;
      case 0x44:  // Left
        if(snake_dir != RIGHT)
          snake_dir = LEFT;
        break;
      default:
        break;
    }


    for(int i = snake_len-1; i > 0; i--)
    {
      snake_bod[i][0] = snake_bod[i-1][0];
      snake_bod[i][1] = snake_bod[i-1][1];
    }




    switch (snake_dir)
    { // actualy moves the snake head
      case UP:
        snake_bod[0][1] = (snake_bod[0][1]-1) % y; //y moves it to up
        break;
      case DOWN:
        snake_bod[0][1] = (snake_bod[0][1]+1) % y; //y moves it to down
        break;
      case RIGHT:
        snake_bod[0][0] = (snake_bod[0][0]+1) % x; //x
        break;
      case LEFT:
        snake_bod[0][0] = (snake_bod[0][0]-1) % x; //x
        break;
    }

    for(int i = 0; i < y; i++)
    {
      for(int j = 0; j < x; j++)
      {
        printf(" ");
        if(apple_x == j && apple_y == i)
        {
          move_cursor(LEFT);
          printf("$");
        }
        for(int s = 0; s < snake_len; s++)
        {
          if(snake_bod[s][0] == j && snake_bod[s][1] == i)
          {
            if(s == 0)
            {
              move_cursor(LEFT);
              printf("@");
            }
            else
            {
              move_cursor(LEFT);
              printf("%i", snake_bod[0][0]);
            }
          }
        }
      }
      printf("\r");
      move_cursor(RIGHT);
      move_cursor(DOWN);
    }

    for(int i = 0; i < y; i++) // resets the cursor to 1:1 to set it up for the next draw operation
    {
      move_cursor(UP);
    }

    for(int i = 1; i < snake_len; i++){
      if(snake_bod[0][0] == snake_bod[i][0] && snake_bod[0][1] == snake_bod[i][1])
      {
        game_over = true;
      }
    }


    if(apple_x == snake_bod[0][0] && apple_y == snake_bod[0][1]) // check for colision with snakes head
    {
      snake_len++;
      bool colide = true;
      while(colide)
      {
        colide = false;
        apple_x = rand() % x;
        apple_y = rand() % y;
        for(int i = 0; i < snake_len; i++){
          if(apple_x == snake_bod[i][0] && apple_y == snake_bod[i][1])
          {
            colide = true;
          }
        }
      }
    }


    if(game_over){
      printf("Game Over \n");
      move_cursor(RIGHT);
      printf("SCORE: %i \n", snake_len);
      move_cursor(RIGHT);
    }

    while(game_over){

      while(lastest_c != 0x0a){
        printf("Press enter!\r");
        move_cursor(RIGHT);
        _delay_ms(1000);
        printf("Press      !\r");
        move_cursor(RIGHT);
        _delay_ms(1000);
      }
      move_cursor(UP);
      move_cursor(UP);
      game_over = false;
      snake_len = 2;
      snake_bod[0][0] = x / 2;
      snake_bod[0][1] = y / 2;

      snake_bod[1][0] = snake_bod[0][0];  // i might not even need this
      snake_bod[1][1] = snake_bod[0][1]+1;

      // reset the positions of the snake to outside the bounderies
      for(int i = 2; i < x*y; i++){
        snake_bod[i][0] = x;
      }

    }



    _delay_ms(1000);

  } // end of gameloop



}
