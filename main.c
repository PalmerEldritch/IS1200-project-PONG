#include <pic32mx.h>
#include <stdint.h>
#include "init.h"
#include "arrays.c"
#include "structs.h"

extern void enable_interrupt();
//Global variables
int timeOutCount = 0;

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & 0x00000100)
  {
    timeOutCount++;
    IFSCLR(0) = 0x00000100;


    if(timeOutCount == 50)
    {
			display_image(0, display_buffer);

    	timeOutCount = 0;
    }
  }
}


int main(void) {

	pins_init();
	display_init();
	display_image(0, splash_screen);

	Ball b;
	b.x = 64;
	b.y = 16;
	draw_ball(b);
	display_image(0, display_buffer);



	for(;;) ;
	return 0;
}
