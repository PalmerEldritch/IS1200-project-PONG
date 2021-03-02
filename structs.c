// #include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"

struct Paddle
{
    int paddle_id;
    int x;
    int y_top;
    int y_bottom;
};
