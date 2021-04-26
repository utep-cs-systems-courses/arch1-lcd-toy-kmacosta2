#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

u_char currentRow = 10;
u_char nextRow = 10;
u_char currentCol = 10;
u_char nextCol = 10;
signed char velocity = 3;  /* next time implement s1 to increase speed to 6*/

void wdt_c_handler()
{
  static int secCount = 0;
  static int dSecCount = 0;
  secCount ++;
  dSecCount ++;
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
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
  }
  
}



void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts), bit 4 for CPU OFF */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(currentCol, currentRow, "hello", COLOR_BLUE, COLOR_BLUE);
      drawString5x7(nextCol, nextRow, "hello", fontFgColor, COLOR_BLUE);
      currentCol = nextCol;
      currentRow = nextRow;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF, so it's stalling here */
    P1OUT |= LED_GREEN;		/* green on */
  }
}


