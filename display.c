#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"
#include "arrays.c"
/*
	SPI send/recieve protocol
*/
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}
/*
	Send image data to the display from a 512 byte char array
*/
void display_image(int x, const uint8_t *data) {
	int i, j;

	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));

		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

		for(j = 0; j < 128; j++)
			spi_send_recv(~data[i*128 + j]);
	}
}

/*
	For debuggning while working in the terminal. 
	Adds column numbers above the diplay printout.
*/
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
/*
	Modified version of display_image. Sends a printout of the data to the terminal instead of the on chip display. 
*/
void terminal_image(const unsigned char output[]) {
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
/*

    Clears the display_buffer array by writing zeros to it.

*/

void clear_buffer (void) {
    int i;
    for(i = 0; i < 512; i++) {
        display_buffer[i] = 0;
    }
}
