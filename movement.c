#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"

int direction = 1;  // Horizontal direction, left or right.
float k = 1;        // Slope of the balls trajectory. Can be seen as the balls speed. Higher value -> steeper slope -> higher speed. 

/* 
  Check conditions for impacts with the walls, paddles or if out and moves the ball one step ahead accordingly
*/
void move_ball(Ball *b, Paddle *p1, Paddle *p2)
{
  int p1y = p1->y_top;
  int p2y = p2->y_top;

  /* 
    Detect vertical bounce
  */
  if ((b->y < 1) || (b->y > 30))
  {
    k = k * -1;
  }

  /* 
    Check impact with paddle 2 and adjust ball direction. If out, adjust score and reset ball to mid point.
  */
  if ((b->x == 126) && (direction == 1))
  {
    if (((b->y) >= (p2->y_top)) && ((b->y) <= (p2->y_top) + 8))
    {
      direction = direction * -1;

      if (k > 0)
      {
        k = k * ((1 + (b->y) - (p2y)) / 4);
      }
      else
      {
        k = k * ((1 + (b->y) - (p2y)) / 4);
      }
    }
    else
    {
      b->x = 64;
      b->y = 16;
      k = 1;
      p1->score = p1->score + 1;
      delay(8000000);
    }
  }

  /* 
    Check impact with paddle 1 and adjust ball direction. If out, adjust score and reset ball to mid point.
  */
  if ((b->x == 1) && (direction == -1))
  {
    if (((b->y) >= (p1->y_top)) && ((b->y) <= (p1->y_top) + 8))
    {
      direction = direction * -1;
      if (k > 0)
      {
        k = k * ((1 + (b->y) - (p1y)) / 4);
      }
      else
      {
        k = k * (((p1y + 8) - (b->y)) / 4);
      }
    }
    else
    {
      b->x = 64;
      b->y = 16;
      k = 1;
      p2->score = p2->score + 1;
      delay(8000000);
    }
  }

  /* 
    Move the ball one step ahead
  */
  b->x = b->x + direction;
  b->y = b->y + k;
}

/* 
  Moves paddle 1 up or down if the corresponding button is pressed
*/
void move_paddle_p1(Paddle *p)
{
  if (btn4() && (p->y_top) > 0)
  {
    p->y_top = (p->y_top) - 1;
  }
  else if (btn3() && (p->y_top) < 24)
  {
    p->y_top = (p->y_top) + 1;
  }
}

/* 
  Moves paddle 2 up or down if the corresponding button is pressed
*/
void move_paddle_p2(Paddle *p)
{
  if (btn2() && (p->y_top) > 0)
  {
    p->y_top = (p->y_top) - 1;
  }
  else if (btn1() && (p->y_top) < 24)
  {
    p->y_top = (p->y_top) + 1;
  }
}

/* 
  Functions for checking if any of the buttons are pressed. Returns a 1 of true.
*/
int btn4(void)
{
  return ((PORTD & 0x00000080) >> 7) & 0x1;
}

int btn3(void)
{
  return ((PORTD & 0x00000040) >> 6) & 0x1;
}

int btn2(void)
{
  return ((PORTD & 0x00000020) >> 5) & 0x1;
}

int btn1(void)
{
  return ((PORTF & 0x00000002) >> 1) & 0x1;
}
