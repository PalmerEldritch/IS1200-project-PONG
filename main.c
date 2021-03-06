#include <pic32mx.h>
#include <stdint.h>
#include "init.h"

extern void enable_interrupt();

/* Global variables */
int timeOutCount = 0;
int framecounter = 0;
int play_intro = 1;
int game_over = 0;
int play_game = 0;
int game_length = 10;

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
	else if ((IFS(0) & 0x00000100) && (play_game == 1))
	{
		IFSCLR(0) = 0x00000100;
		timeOutCount++;
		if (timeOutCount > 1)
		{
			if ((p1.score == game_length) || (p2.score == game_length))
			{
				play_game = 0;
				game_over = 1;
			}
			display_image(0, display_buffer);
			update_screen(display_buffer);
			timeOutCount = 0;
		}
	}
	else if ((IFS(0) & 0x00000100) && (game_over == 1))
	{
		if (p1.score == game_length)
		{
			display_image(0, p1_win);
		}
		else
		{
			display_image(0, p2_win);
		}
	}
}

/* 
	Takes x and y coordinates for a pixel on the screen and sets the corresponding bit in the display_buffer array
*/
void draw_bit(float x, float y)
{
	x = (int)x;
	y = (int)y;
	int p = y / 8, B = x + 128 * p, b = y - 8 * p;
	char c = 0x01 << b;
	display_buffer[B] = display_buffer[B] | c;
}

/* 
	Draws the current score of the designated player to the display_buffer array
*/
void draw_score(Paddle p)
{
	int i;
	switch (p.id)
	{
	case 1:
		for (i = 0; i < 8; i++)
		{
			display_buffer[52 + i] = numbers[p.score * 8 + i];
		}
		break;

	case 2:
		for (i = 0; i < 8; i++)
		{
			display_buffer[68 + i] = numbers[p.score * 8 + i];
		}
		break;
	default:
		break;
	}
}

/* 
	Updates the screen while in game mode
*/
void update_screen(uint8_t *data)
{
	clear_buffer(data);
	move_ball(&b, &p1, &p2);
	move_paddle_p1(&p1);
	move_paddle_p2(&p2);
	draw_paddle(p1);
	draw_paddle(p2);
	draw_ball(b);
	draw_score(p1);
	draw_score(p2);
}

/* 
	Draws the intro animation frames to the display_buffer array, incrementally, one every cycle 
*/
void intro(void)
{
	if (framecounter < 30)
	{
		display_image(0, intro_frames[framecounter]);
		framecounter++;
	}
	else
	{
		framecounter = 0;
		play_intro = 0;
		play_game = 1;
	}
}

int main(void)
{
	/* 
		Run initialization of pins, display and timers
	*/
	pins_init();
	display_init();
	timer_init();
	enable_interrupt();

	/* 
		Setup start positions for the ball and paddles
	*/
	b.x = 64;
	b.y = 16;
	p1.id = 1;
	p1.x = 0;
	p1.y_top = 12;
	p1.score = 0;
	p2.id = 2;
	p2.x = 127;
	p2.y_top = 15;
	p2.score = 0;

	for (;;)
		return 0;
}
