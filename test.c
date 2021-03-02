// #include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"
#include "arrays.c"
int main (void) {
    Paddle p1;

    p1.paddle_id = 1;
    p1.x = 0;
    p1.y_top = 0;
    draw_paddle(p1);
    printf("%x\n", display_buffer[0]);
    clear_buffer(); 
    p1.y_top = 1;
    draw_paddle(p1);
    printf("%x %x", display_buffer[0],display_buffer[128]);
    return 0;

}