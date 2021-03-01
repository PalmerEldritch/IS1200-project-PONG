#include <stdio.h>
#include <pic32mx.h>

void init_timer(void) {
// 16-BIT SYNCRONOUS INTERNAL CLOCK INITIALIZATION
  T2CON = 0x0;        // Disable timer and set clock source to internal
  T2CON = 0x7 << 4;   // Set pre-scale to 1:256   
  TMR2 = 0x0;         // Set timer start value to 0
  PR2 = 0x7a12;       // Set period register to 31250   

  IFSCLR(0) = 0x100;  // Clear the timer interrupt status flag 
  IPC(2) = 0x5;       // Set priority and subpriority for Timer 2
  IECSET(0) = 0x100;  // Enable interupts for Timer 2

  IFSCLR(0) = 0x80000;
  IPC(4) = 0x06000000;
  IECSET(0) = 0x80000;
  INTCONSET = 0x00000010;

  T2CONSET = 0x8000;  // Enable timer
  
  enable_interrupt(); // Enable global interrupts 

}