#include <stdint.h>
#include <stdio.h>
// #include <pic32mx.h>
#include "structs.c"

void draw_paddle (struct Paddle* p) {
    int i;
    for (i = 0; i < p->y_bottom; i++) {
        draw_bit((p->x), i);
    }
}