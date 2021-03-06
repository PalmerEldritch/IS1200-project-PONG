#ifndef STRUCTS_H
#define STRUCTS_H

/*
  Structure definitions for the paddles and ball
*/
typedef struct Paddle
{
    int id;
    float x;
    float y_top;
    int score;
}Paddle;

typedef struct Ball{
  float x;
  float y;
}Ball;

#endif
