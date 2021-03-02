#include <pic32mx.h>
#include <stdint.h>
#include "init.h"

extern void enable_interrupt();


//Global variables
int timeOutCount = 0;
Ball b;
Paddle p1, p2;


/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & 0x00000100)
  {
		IFSCLR(0) = 0x00000100;
    timeOutCount++;



    if(timeOutCount > 1)
    {
			display_image(0, display_buffer);
			update_screen(display_buffer);
    	timeOutCount = 0;
    }
  }
}
void draw_bit (float x, float y) {
		x = (int) x;
		y = (int) y;
    int p = y / 8, B = x + 128*p, b = y - 8*p;
    char c = 0x01 << b;
    display_buffer[B] = display_buffer[B] | c;
}

void update_screen (uint8_t *data){
	clear_buffer(data);
	move_ball(&b, &p1, &p2);
	move_paddle_p1(&p1);
	move_paddle_p2(&p2);
	draw_paddle(p1);
	draw_paddle(p2);
	draw_ball(b);
}
int main(void) {

	pins_init();
	delay(10000);
	display_init();
	display_image(0, splash_screen);
	timer_init();
	enable_interrupt();
	b.x = 64;
	b.y = 16;

	p1.x = 0;
	p1.y_top = 12;
	p2.x = 127;
	p2.y_top = 15;




	draw_ball(b);
	draw_bit(5, 5);
//	display_image(0, display_buffer);



	for(;;) ;
	return 0;
}
