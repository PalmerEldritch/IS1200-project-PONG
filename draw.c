#include <stdint.h>
#include <stdio.h>
#include "init.h"
#include "arrays.c"
/*
	Takes two integera as x,y-coordinates and draws the corresponding pixel to the display_buffer array.
*/
void draw_bit (int x, int y) {
    int p = y / 8, B = x + 128*p, b = y - 8*p;
    char c = 0x01 << b;
    display_buffer[B] = display_buffer[B] | c;
}

/*
	Draws a paddle to the display_buffer array.
*/
void draw_paddle (Paddle p) {
    int i, y_max = p.y_top + 8;
    for (i = p.y_top; i < y_max; i++) {
        draw_bit((p.x), i);
    }
}