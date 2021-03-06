#include <stdint.h>
#include <pic32mx.h>
#include "init.h"

/* 
  Simple delay function
*/
void delay(int cyc)
{
  int i;
  for (i = cyc; i > 0; i--)
    ;
}

/* 
  Initialize all pins
*/
void pins_init(void)
{
  /* Set up peripheral bus clock */
  OSCCON &= ~0x180000;
  OSCCON |= 0x080000;

  /* Set up output pins */
  AD1PCFG = 0xFFFF;
  ODCE = 0x0;
  TRISECLR = 0xFF;
  PORTE = 0x0;

  /* Output pins for display signals */
  PORTF = 0xFFFF;
  PORTG = (1 << 9);
  ODCF = 0x0;
  ODCG = 0x0;
  TRISFCLR = 0x70;
  TRISGCLR = 0x200;

  /* Set up input pins */
  TRISDSET = (1 << 8);
  TRISFSET = (1 << 1);

  /* Set up SPI as master */
  SPI2CON = 0;
  SPI2BRG = 4;

  /* Clear SPIROV*/
  SPI2STATCLR &= ~0x40;
  /* Set CKP = 1, MSTEN = 1; */
  SPI2CON |= 0x60;

  /* Turn on SPI */
  SPI2CONSET = 0x8000;

  // Set buttons as input
  TRISDSET = 0xE0;
  TRISFSET = 0x2;
}

/* 
  Initialize timer with interrupts
*/
void timer_init()
{
  //Initialize timer2
  T2CON = 0;
  T2CONSET = (0x4 << 4);
  TMR2 = 0x0;
  PR2 = 0x7A12;
  IFSCLR(0) = 0x00000100;

  //Enable timer2 interrupts
  IECSET(0) = 0x00000100;
  IPC(2) = 0x5;

  //Start timer2
  T2CONSET = 0x8000;
}

/* 
  Initialize the display
*/
void display_init()
{
  DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
  delay(10);
  DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
  delay(1000000);

  spi_send_recv(0xAE);
  DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
  delay(10);
  DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
  delay(10);

  spi_send_recv(0x8D);
  spi_send_recv(0x14);

  spi_send_recv(0xD9);
  spi_send_recv(0xF1);

  DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
  delay(10000000);

  spi_send_recv(0xA1);
  spi_send_recv(0xC8);

  spi_send_recv(0xDA);
  spi_send_recv(0x20);

  spi_send_recv(0xAF);
}
