#ifndef INIT_H
#define INIT_H
#include <stdint.h>
#include <stdio.h>
#include "structs.h"
#include "arrays.c"
// #include "intro.c"

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

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* Function declarations */
extern void enable_interrupt();
void delay(int cyc);
void pins_init(void);
void display_init(void);
uint8_t spi_send_recv(uint8_t data);
void display_image(int x, const uint8_t *data);
void display_string(int line, int offset, char *s);
void display_update(void);
void clear_buffer(uint8_t *data);
void draw_bit (float x, float y);
void draw_ball (Ball b);
void move_ball(Ball *b, Paddle *p1, Paddle *p2);
void update_game (uint8_t *data);
void draw_paddle (Paddle p);
void timer_init();
void move_paddle_p1(Paddle *p);
void move_paddle_p2 (Paddle *p);
int btn4 (void);
int btn3 (void);
int btn2 (void);
int btn1 (void);
void intro (void);
void menu(void);
#endif
