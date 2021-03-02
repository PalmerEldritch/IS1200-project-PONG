// #include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"
#include "structs.c"
#include "arrays.c"
void draw_paddle (struct Paddle* p) {
    int i;
    for (i = 0; i < p->y_bottom; i++) {
        draw_bit((p->x), i);
    }
}
int main (void) {
    struct Paddle p1;

    p1.paddle_id = 1;
    p1.x = 0;
    p1.y_top = 0;
    p1.y_bottom = p1.y_top + 8;
    printf("%d\n", display_buffer[0]);
    draw_paddle(&p1);
    
    printf("%d", display_buffer[0]);
    return 0;

}