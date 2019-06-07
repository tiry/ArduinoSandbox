// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int maxXY=32;
int marginX=2;
int marginY=2;
int w=3;
int inc =1;

uint16_t nxWhite = matrix.Color333(6, 6, 6);
uint16_t nxBlue = matrix.Color333(0, 0, 3);
uint16_t red = matrix.Color333(7, 0, 0 );

void setup() {

  matrix.begin();
  
  // fix the screen with nx blue
  matrix.fillRect(0, 0, maxXY, maxXY, nxBlue);    
 
}

void drawX(int mX,int mY, uint16_t c) {
  // draw Nuxeo X
  for (int i=0; i <= w; i++) {
      matrix.drawLine(mX, mY+i, maxXY-mX-i-1, maxXY-mY-1, c);
      if (i>0) {
        matrix.drawLine(mX+i, mY, maxXY-mX-1, maxXY-mY-i-1, c);
      }
  }

  for (int i=0; i <= w; i++) {
      matrix.drawLine(maxXY-mX-1, mY+i, mX+i, maxXY-mY-1, c);
      if (i>0) {
        matrix.drawLine(maxXY-mX-i-1, mY, mX, maxXY-mY-i-1, c);
      }
  }
}

void eraseX(int mX,int mY, uint16_t c, int inc) {

  int i = w;

  if (inc>0) {
    matrix.drawLine(mX, mY+i, maxXY-mX-i-1, maxXY-mY-1, c);  
    matrix.drawLine(mX+i, mY, maxXY-mX-1, maxXY-mY-i-1, c);  
  } else {
    matrix.drawLine(mX, mY+i, maxXY-mX-i-1, maxXY-mY-1, c);  
    matrix.drawLine(mX+i, mY, maxXY-mX-1, maxXY-mY-i-1, c);      
  }

  matrix.drawLine(maxXY-mX-1, mY+i, mX+i, maxXY-mY-1, c);
  matrix.drawLine(maxXY-mX-i-1, mY, mX, maxXY-mY-i-1, c);

  matrix.fillRect(mX, mY, maxXY-2*mX, mY+1 , c);
  matrix.fillRect(mX, maxXY-2*mY-1, maxXY-2*mX, mY+1 , c);
}



void loop() {

  // partial delete
  // redrawing  the whole matrix
  // would increase flicker
  eraseX(marginX,marginY, nxBlue, inc);
  
  marginX = marginX+inc;
  if (marginX>15) {
    inc=-inc;
  } else if (marginX<3) {
    inc=-inc;
    drawX(marginX,marginY, nxWhite);
    delay(2000);    
  } else {
    drawX(marginX,marginY, nxWhite);
  }

  
  
}
