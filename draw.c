#include <stdio.h>
#include "arrays.c"


void column_numbers (void) {
    int i, j;
    for(i = 0; i < 3; i++) {
        printf("\t");
        for(j = 0; j < 128; j++) {
            if(i < 1) {
                if(j < 100) {
                    printf("  "); 
                } else {
                    printf("%d ", j / 100);
                }
            } else if(i < 2) {
                if(j < 10) {
                    printf("  ");
                } else {
                    printf("%d ", (j % 100) / 10);
                } 
            } else {
                printf("%d ", j % 10);
            }
        }
        printf("\n");
    }
}

void send_to_display(const unsigned char output[]) {
    int i, j, k, b, row = 0;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 8; j++) {
            printf("%d\t", row++);
            for(k = 0; k < 128; k++) {
                b = (output[i*128 + k] >> j) & 0x1;
                if(b) {
                    printf("%c%c", 178, 178);
                } else {
                    printf("%c%c", 176, 0);
                }
            }
            printf("\n");
        }
    }
}

void draw_bit (int x, int y) {
    int p = y / 8, B = x + 128*p, b = y - 8*p;
    char c = 0x01 << b;
    display_buffer[B] = c;
}

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

int main (void) {
    int x = 68, y = 24;
    // int z = 67, w = 22;

    column_numbers();
    draw_bit(x, y);
    send_to_display(display_buffer);
    // delay(1000000);
    // draw_bit(z, w);
    // send_to_display(display_buffer);
}