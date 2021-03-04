#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "init.h"

extern void enable_interrupt();

/* Global variables */
int timeOutCount = 0;
int framecounter = 0;
int menu_pointer = 0;
int play_intro = 1;
int go_to_menu = 0;
int play_game = 0;

/* Structures for the ball and paddles */
Ball b;
Paddle p1, p2;

/* Interrupt Service Routine */
void user_isr(void)
{
	if ((IFS(0) & 0x00000100) && (play_intro == 1))
	{
		IFSCLR(0) = 0x00000100;
		timeOutCount++;

		if (timeOutCount > 10)
		{
			intro();
			timeOutCount = 0;
		}
	}
 	else if ((IFS(0) & 0x00000100) && (go_to_menu == 1)) 
	{
		IFSCLR(0) = 0x00000100;
		timeOutCount++;

		if (timeOutCount > 10)
		{
			menu();
			timeOutCount = 0;
		}
	}
	else if ((IFS(0) & 0x00000100) && (play_game == 1))
	{
		IFSCLR(0) = 0x00000100;
		timeOutCount++;
		if(timeOutCount > 1) {
			display_image(0, display_buffer);
			update_game(display_buffer);
			timeOutCount = 0;
  		}
	}
}

/* Takes x and y coordinates for a pixel on the screen and sets the corresponding bit in the display_buffer array */
void draw_bit(float x, float y)
{
	x = (int)x;
	y = (int)y;
	int p = y / 8, B = x + 128 * p, b = y - 8 * p;
	char c = 0x01 << b;
	display_buffer[B] = display_buffer[B] | c;
}

/* Updates the screen while in game mode */
void update_game(uint8_t *data)
{
	clear_buffer(data);
	move_ball(&b, &p1, &p2);
	move_paddle_p1(&p1);
	move_paddle_p2(&p2);
	draw_paddle(p1);
	draw_paddle(p2);
	draw_ball(b);
}

/* Plays the intro animation */
void intro(void)
{
	if (framecounter < 30)
	{
		// display_image(0, intro_frames[framecounter]);
		framecounter++;
	}
	else
	{
		framecounter = 0;
		play_intro = 0;
		go_to_menu = 1;
	}
}

/* Menu */
void menu( void ) 
{
	char menu_selected[2][3] = { {'-', '-', '>'}, {' ', ' ', ' '} };
	char menu_items[3][9] = {
		{'1',  ' ', 'P', 'l', 'a', 'y', 'e', 'r', ' ',},
		{'2',  ' ', 'P', 'l', 'a', 'y', 'e', 'r', ' ',},
		{'H', 'i', 'g', 'h', 's', 'c', 'o', 'r', 'e', },
	};

	display_string(0, 0, menu_selected[0]);
	display_string(0, 3, menu_items[0]);
	
	display_string(1, 0, menu_selected[1]);
	display_string(1, 3, menu_items[1]);
	
	display_string(2, 0, menu_selected[1]);
	display_string(2, 3, menu_items[2]);

	while(btn2() != 1) {
		if(btn4() && menu_pointer > 0) {
			menu_pointer--;
			display_string(menu_pointer, 0, menu_selected[0]);
			display_string(menu_pointer, 3, menu_items[menu_pointer]);
			display_string(menu_pointer + 1, 0, menu_selected[1]);
			display_string(menu_pointer, 3, menu_items[menu_pointer + 1]);
		}
		if(btn3() && menu_pointer < 2) {
			menu_pointer++;
			display_string(menu_pointer, 0, menu_selected[0]);
			display_string(menu_pointer, 3, menu_items[menu_pointer]);
			display_string(menu_pointer - 1, 0, menu_selected[1]);
			display_string(menu_pointer, 3, menu_items[menu_pointer - 1]);
		}
		display_update(); 
	}

	go_to_menu = 0;
	play_game = 1;
}

int main(void)
{
	/* Run initialization of pins, display and timers */
	pins_init();
	display_init();
	timer_init();
	enable_interrupt();

	/* Setup start positions for the ball and paddles */
	b.x = 64;
	b.y = 16;
	p1.x = 0;
	p1.y_top = 12;
	p2.x = 127;
	p2.y_top = 15;

	for (;;)
	return 0;
}
