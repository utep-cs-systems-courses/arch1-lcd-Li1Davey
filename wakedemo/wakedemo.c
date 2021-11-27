#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!
//#define LED BIT6/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

void led_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
}

short redrawScreen = 0;
int switches = 0;
int press = 0;

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
  if (switches & SW4) {
    redrawScreen = 1;
    press = 4;
  }
  if (switches & SW3) {
    redrawScreen = 1;
    press = 3;
  }
  if (switches & SW2) {
    redrawScreen = 1;
    press = 2;
  }
  if (switches & SW1){
    redrawScreen = 1;
    press = 1;
  }
}



// axis zero for col, axis 1 for row
//short drawPos[2] = {10,10}, controlPos[2] = {10,10};
//short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};
void timeSM();

void wdt_c_handler()
{
  timeSM();
}

int doReMi[] = {6802, 6060, 5405, 5102, 4545, 4049, 3610, 3407};

void draw_default();
void update_shape();
void update_restart();

void normalTime();
void blinkCounter();
void blinkUpdate();

void main()
{
  configureClocks();
  lcd_init();
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */

  update_restart();

  while (1) {/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    //lightControl(2);
    //P1OUT &= ~LED;/* led off */
    or_sr(0x10);/**< CPU OFF */
    //P1OUT |= LED;/* led on */
  }
}

void draw_default(){
  drawString8x12(10,20, "S1:Grow", COLOR_WHITE, COLOR_RED);
  drawString8x12(10,40, "S2:Shrink", COLOR_WHITE, COLOR_RED);
  drawString8x12(10,60, "S3:Solfege", COLOR_WHITE, COLOR_RED);
  drawString8x12(10,80, "S4:Reset", COLOR_WHITE, COLOR_RED);
}

unsigned char step = 0;

void
update_shape()
{
  switch (press){
  case 1:
    if(step <= 60){
      if(step == 0){
	clearScreen(COLOR_BLUE);
      }
      circle(step, COLOR_YELLOW);
      step ++;
    }
    else{
      clearScreen(COLOR_BLUE);
      step = 0;
    }
    break;
  case 2:
    if(step >= 0 && step <= 60){
      circle(step, COLOR_YELLOW);
      step--;
    }
    else{
      clearScreen(COLOR_BLUE);
      step = 60;
    }
  case 3:
    clearScreen(COLOR_BLUE);
    break;
  default:
    update_restart();
    break;
  }
}

void update_restart(){
  clearScreen(COLOR_BLUE);
  draw_default();
}

int secCount = 0;

void normalTime(){
  secCount ++;
  if (secCount >= 25) {/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}

int secondCount = 0;
int blinkCount = 0;
int blinkLimit = 0;
int getDim = 0;

void blinkUpdate(){
  blinkCount ++;
  if (blinkCount >= blinkLimit && doReMi[blinkLimit] > 0) {
    blinkCount = 0;
    buzzer_set_period(doReMi[blinkLimit]);
    lightControl(1);
  }
  else{
    lightControl(0);
  }
  blinkCounter();
}

void blinkCounter(){
  //For Every second
  secondCount ++;
  if (secondCount >= 250) {
    secondCount = 0;
    if(!getDim){
      blinkLimit ++;
      if (blinkLimit >= 7){ //when blink limit reaches highest limit it will tell the blink counter to make the LED dimmer
	getDim = 1;
      }
    }
    else{
      blinkLimit--;
      if(blinkLimit <= -1){
	press = 4;
	//button = 4; //Stops everyting
      }
    }
  }
}

void stopUpdates(){ //Turns off the buzzer and LEDs and reutrns all initial variables to their original value to start over
  secondCount = 0;
  blinkCount = 0;
  blinkLimit = 0;
  getDim = 0;

  redrawScreen = 0;
  
  buzzer_set_period(0);
  lightControl(0);
  press = 0;
  step = 0;
  update_restart();
  

}

void timeSM(){

  switch(press){
  case 1:
  case 2:
    normalTime();
    break;
  case 3:
    blinkUpdate();
    break;
  case 4:
    stopUpdates();
    break;
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
