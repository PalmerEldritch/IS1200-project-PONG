#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"

int direction = 1;
float k = 1;
int p1_score = 0, p2_score = 0;

void move_ball (Ball *b, Paddle *p1, Paddle *p2)
{
  int p1y = p1->y_top;
  int p2y = p2->y_top;
//Detect vertical bounce
  if((b->y < 1) || (b->y > 30))
  {
    k = k *-1;
  }

// Check if ball will bounce on paddle2


  if((b->x == 126) && (direction == 1))
  {
    if(((b->y) >= (p2->y_top)) && ((b->y) <= (p2->y_top) + 8))
    {
      direction = direction * -1;

      if(k > 0)
      {
      k = k * (((b->y) - p2y) / 4);
      }
      else{
        k = k * (((p2y + 8) - (b->y)) / 4);
      }
    }else{
      b->x = 64;
      b->y = 16;
      p1_score++;
      delay(8000000);
    }
  }

  // Check if ball will bounce on paddle1
    if((b->x == 1) && (direction == -1))
    {
      if(((b->y) >= (p1->y_top)) && ((b->y) <= (p1->y_top) + 8))
      {
        direction = direction * -1;
        if(k > 0)
        {
        k = k * (((b->y) - p2y) / 4);
        }
        else{
          k = k * (((p2y + 8) - (b->y)) / 4);
        }
      }else{
        b->x = 64;
        b->y = 16;
        p2_score++;
        delay(8000000);
      }
    }

//Move ball
    b->x = b->x + 1*direction;
    b->y = b->y + k;
}
void move_paddle_p1 (Paddle *p)
{
  if(btn4() && (p->y_top) > 0){
    p->y_top = (p->y_top) - 1;
  }
  else if(btn3() && (p->y_top) < 24){
    p->y_top = (p->y_top) + 1;
  }
}

void move_paddle_p2 (Paddle *p)
{
  if(btn2() && (p->y_top) > 0){
    p->y_top = (p->y_top) - 1;
  }
  else if(btn1() && (p->y_top) < 24){
    p->y_top = (p->y_top) + 1;
  }
}



int btn4 (void)
{
  return ((PORTD & 0x00000080) >> 7) & 0x1;
}
int btn3 (void)
{
  return ((PORTD & 0x00000040) >> 6) & 0x1;
}
int btn2 (void)
{
  return ((PORTD & 0x00000020) >> 5) & 0x1;
}
int btn1 (void)
{
  return ((PORTF & 0x00000002) >> 1) & 0x1;
}
