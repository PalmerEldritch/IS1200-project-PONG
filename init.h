#ifndef INIT_H
#define INIT_H
#include <stdint.h>
#include <stdio.h>

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

// Structures
typedef struct Paddle
{
    int paddle_id;
    int x;
    int y_top;
}Paddle;

//Define buttons

// Functions declarations
extern void enable_interrupt();

void pins_init(void);
void display_init(void);
uint8_t spi_send_recv(uint8_t data);
void display_image(int x, const uint8_t *data);
void clear_buffer(void);
void draw_bit (int x, int y);
void draw_paddle (Paddle);
void column_numbers (void);                         // Only used while working in the terminal
void terminal_image(const unsigned char output[]);  // Only used while working in the terminal
#endif
