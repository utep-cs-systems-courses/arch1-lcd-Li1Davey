/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
//#include <stdlib.h>
//#include <stdio.h>

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString8x12(10,5, "World", COLOR_BLACK, COLOR_RED);

  short radius = 50;
  
  circle(radius);
  
  /*
  for (short c = 50; c >= 0; c--){
    for(short j = 0; j <= c; j++){
      short R = 30 - c;
      drawPixel(centerC+j, centerR+R, COLOR_YELLOW); //bottom right
      drawPixel(centerC+j, centerR-R, COLOR_YELLOW); //top right
      drawPixel(centerC-j, centerR+R, COLOR_YELLOW); //bottom left
      drawPixel(centerC-j, centerR-R, COLOR_YELLOW); //top left
    }
  }
  */
  

  /*	
  //short col = 30;
  short startc = SHORT_EDGE_PIXELS/2, startr = LONG_EDGE_PIXELS/2;
  
  for (short col = 0; col < 30;){
    short row = col; //-col turns it upside down
    short leftEdge = -col;
    short rightEdge = col;
    for (short c = leftEdge; c <= rightEdge; c++){
      drawPixel(startc+c, startr+row, COLOR_PINK);
    }
    //drawPixel(startc+leftEdge, startr+row, COLOR_PINK);
    //drawPixel(startc+rightEdge, startr+row, COLOR_PINK);
    col += 1;
  }
  */

  /*
  short centerR = LONG_EDGE_PIXELS/2; // Center coordinate for the rows
  short centerC = SHORT_EDGE_PIXELS/2; //Center coordinate for the columns
  
  for (short row = -30; row <= 30; row++){
    short col1 = row;
    short col2 = -row;
    short minCol;
    if(col1 < col2){
      minCol = col1;
    }
    else{
      minCol = col2;
    }
    short maxCol;
    if(col1 < col2){
      minCol = col2;
    }
    else{
      minCol = col1;
    }
    
    for(short col = minCol; col < maxCol; col++){
      drawPixel(col+centerC, row+centerR, COLOR_PINK);
    }
  }
  */
  
  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
