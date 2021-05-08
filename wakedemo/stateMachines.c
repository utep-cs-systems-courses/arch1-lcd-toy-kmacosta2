#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

void switchSM()
{
  if(ssd) sm1();
  else if(ssd2) sm2();
  else if(ssd3) sm3();
  else if(ssd4) sm4();
  else stop_all();   
  led_changed = 1;
  led_update();
}

void stop_all() {
  red_on = 0;
  green_on = 0;
  buzzer_set_period(0);
  led_changed = 1;
  led_update();
}

void sm1() //call this method for ssd == true
{
  static char state = 0;
  green_on = 0;
  switch(state) { /*in my cases there'll be the sequences of the lights & the frequencies. And use the wdInterrupt!! */
  case 0: red_on = 1; state++; buzzer_set_period(2000); break;
  case 1: red_on = 0; state = 0; buzzer_set_period(0); break;
  default: state = 0;
  }
   led_changed = 1;
   led_update();
}

void sm2()
{
  static char state = 0;
  red_on = 0;
  switch(state) {
  case 0: green_on = 1; state++; buzzer_set_period(2000); break;
  case 1: green_on = 0; state = 0; buzzer_set_period(1000); break;
  default: state = 0; buzzer_set_period(0);
  }
   led_changed = 1;
   led_update();
}

void sm3()
{
  static char state = 0;
  switch(state) {
  case 0: green_on = 1; red_on = 0; state++; buzzer_set_period(2000); break;
  case 1: green_on = 0; red_on = 1; state = 0; buzzer_set_period(1000); break;
  default: state = 0; buzzer_set_period(0);
  }
   led_changed = 1;
   led_update();
}

void sm4()
{
  static char state = 0;
  switch(state) {
  case 0: green_on = 1; red_on = 1; state++; buzzer_set_period(900); break;
  case 1: green_on = 0; red_on = 0; state = 0; buzzer_set_period(2000); break;
  default: state = 0; buzzer_set_period(0);
  }
   led_changed = 1;
   led_update();
} 
