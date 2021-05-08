
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "drawKunai.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

u_char currentRow = 10;
u_char nextRow = 10;
u_char currentCol = 10;
u_char nextCol = 10;
signed char velocity = 6;

void wdt_c_handler()
{
  static int secCount = 0;
  static int dSecCount = 0;
  static int sizeCount = 0;
  static int current_Period = 1000;
  secCount ++;
  dSecCount ++;
  sizeCount ++;
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    sizeCount = 0; 
    u_char size = 30, offset_r = 70, offset_c = 65;
    drawSpear(size, offset_r, offset_c);
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
  if (sizeCount == 1) {
    clearScreen(COLOR_BLUE);
    u_char size = 15, offset_r = 70, offset_c = 65;
    drawSpear(size, offset_r, offset_c);
  }
  if (sizeCount == 84) {
    u_char size = 20, offset_r = 70, offset_c = 65;
    drawSpear(size, offset_r, offset_c);
  }
  if (sizeCount == 167) {
    u_char size = 25, offset_r = 70, offset_c = 65;
    drawSpear(size, offset_r, offset_c);
    
  }
  
  if (dSecCount == 25) {         /* 10x / sec */
    dSecCount = 0;
    nextCol += velocity;
    if (nextCol > 90 || nextCol < 10) {  /* addressing the extremes */
      velocity *= -1;                         /* onto the other direction */
      nextCol += velocity;                    /* undo last move */
      nextRow += velocity;
    }
    redrawScreen = 1;
    if (ssd) {
      current_Period = (current_Period == 1000) ? 1400 : 1000;
      buzzer_set_period(current_Period);
    }
    if (ssd2) {
      buzzer_set_period(0);
    }
  }
  
}

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  switch_init();
  buzzer_init();
  buzzer_set_period(0);
  led_init();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts), bit 4 for CPU OFF */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(currentCol, currentRow, "MK11", COLOR_BLUE, COLOR_BLUE);
      drawString5x7(nextCol, nextRow, "MK11", fontFgColor, COLOR_BLUE);
      currentCol = nextCol;
      currentRow = nextRow;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF, so it's stalling here */
    P1OUT |= LED_GREEN;		/* green on */
  }
}


