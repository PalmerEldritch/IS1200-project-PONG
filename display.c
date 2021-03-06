#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"

/*
	SPI send/recieve protocol
*/
uint8_t spi_send_recv(uint8_t data)
{
    while (!(SPI2STAT & 0x08))
        ;
    SPI2BUF = data;
    while (!(SPI2STAT & 0x01))
        ;
    return SPI2BUF;
}

/*
	Send image data to the display from a 512 byte char array
*/
void display_image(int x, const uint8_t *data)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(x & 0xF);
        spi_send_recv(0x10 | ((x >> 4) & 0xF));

        DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

        for (j = 0; j < 128; j++)
            spi_send_recv(data[i * 128 + j]);
    }
}

/*
    Clears the display_buffer array by writing zeros to it.
*/
void clear_buffer(uint8_t *data)
{
    int i;
    for (i = 0; i < 512; i++)
    {
        data[i] = 0;
    }
}
