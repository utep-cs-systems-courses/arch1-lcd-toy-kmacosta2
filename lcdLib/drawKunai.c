#include "lcdutils.h"
#include "lcddraw.h"
#include "drawKunai.h"

/* Draws a kunai, pointing to the right side.
 */
void drawSpear(u_char size, u_char offset_r, u_char offset_c)
{
  for (u_char r = 0; r <= size; r++) {
    for (u_char c = 0; c <= (size-r); c++) { 
      drawPixel(offset_c - c, offset_r - r, COLOR_GRAY);
      drawPixel(offset_c - c, offset_r + r, COLOR_GRAY);
      
    }
  }
  drawEnd(size, offset_r, offset_c);
}

/* Draws the end of my spear */
void drawEnd(u_char size, u_char offset_r, u_char offset_c)
{
  for (u_char r = 0; r <= size; r++) {
    for (u_char c = 0; c <= (size-r)*2; c++) {
      drawPixel(offset_c + c, offset_r - r, COLOR_GRAY);
      drawPixel(offset_c + c, offset_r + r, COLOR_GRAY);
    }
  }
}
