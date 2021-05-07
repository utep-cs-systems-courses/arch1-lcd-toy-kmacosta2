/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "drawKunai.h"

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
  
  u_char offset_r = 70, offset_c = 65, size = 20;
  drawSpear(size, offset_r, offset_c);
  
}
