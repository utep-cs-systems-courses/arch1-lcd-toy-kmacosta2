#include <msp430.h>
#include "switches.h"
#include "led.h"

char ssd, ssd2, ssd3, ssd4, switch_state_changed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}


void
switch_interrupt_handler()
{/*just implement all of this into wdInterruptHandler then do the method call*/
  char p2val = switch_update_interrupt_sense();
  ssd = (p2val & SW1) ? 0 : 1;
  ssd2 = (p2val & SW2) ? 0 : 1;
  ssd3 = (p2val & SW3) ? 0 : 1;
  ssd4 = (p2val & SW4) ? 0 : 1;
  switch_state_changed = 1;
}


