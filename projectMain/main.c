#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "switch.h"
#include "stateMachine.h"
//draw
#include "lcdutils.h"
#include "lcddraw.h"



void led_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

short redrawScreen = 1;
short rad = 0;

void wdt_c_handler()
{
  static int wdtCount = 0;
  wdtCount ++;
  if (wdtCount >= 25) { //10/sec 
    wdtCount = 0;
    redrawScreen = 1;
  }
}

void shape();

int main() { // Initialize everything at the start
  //clearScreen(COLOR_BLUE);
    configureClocks();
    switch_init();
    led_init();
    buzzer_init();
    lcd_init();
    configureClocks();
    enableWDTInterrupts();

    or_sr(0x8);          // CPU off, GIE on
    
    clearScreen(COLOR_BLUE);
    
    while (1) {/* forever */

      if (redrawScreen) {
	redrawScreen = 0;
        shape();
      }
      
      or_sr(0x10);/**< CPU OFF */
      
    }
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
    timeSM();
}

void shape(){

  if(rad <= 50){
    circle(rad);
    rad += 5;
  }
  else{
    clearScreen(COLOR_BLUE);
    rad = 0;
  }
}
