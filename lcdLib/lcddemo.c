/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "Get Over Here!", COLOR_GREEN, COLOR_RED);

  //  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  /*
  u_char offset_r = 50, offset_c = 50, size = 50;
  for (int r = 0; r <= 50; r++) {
    for (int c = 0; c <= r; c++) {
      drawPixel(offset_c + c, offset_r + r, COLOR_ORANGE);
    }
    }*/
  u_char offset_r = 70, offset_c = 65, size = 20;
  /*for (int r = size; r >= 0; r--) {
    for (int c = 0; c <= r; c++) {
      drawPixel(offset_r + r, offset_c + c, COLOR_GREEN);
      drawPixel(offset_c + 50 - r, offset_c + c, COLOR_RED);
    }
    
    }*/
  drawSpear(size, offset_r, offset_c);
  
}
