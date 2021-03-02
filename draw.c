#include <stdint.h>
#include <stdio.h>
#include "init.h"

/*
	Takes two integera as x,y-coordinates and draws the corresponding pixel to the display_buffer array.
*/

/*
	Draws a paddle to the display_buffer array.
*/
void draw_paddle (Paddle p) {
    int i, y_max = p.y_top + 8;
    for (i = p.y_top; i < y_max; i++) {
        draw_bit((p.x), i);
    }
}

void draw_ball (Ball b){
	draw_bit(b.x, b.y);
}
