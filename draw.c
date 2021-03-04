#include <stdint.h>
#include <stdio.h>
#include "init.h"

/*
	Draws a paddle to the display_buffer array.
*/
void draw_paddle (Paddle p) {
    int i, y_max = p.y_top + 8;
    for (i = p.y_top; i < y_max; i++) {
        draw_bit((p.x), i);
    }
}

void draw_ball (Ball b) {
	draw_bit(b.x, b.y);
}

void draw_score (int p, int n) {
    int i;
    switch (p)
    {
    case 1:
        for(i = 0; i < 8; i++) {
            display_buffer[52 + i] = numbers[n * 8 + i];
        }
        break;
    
    case 2:
        for(i = 0; i < 8; i++) {
            display_buffer[68 + i] = numbers[n * 8 + i];
        }
        break;

    default:
        break;
    }
}
