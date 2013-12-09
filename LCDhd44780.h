/*
Arduino LiquidCrystal, Print, and Wiring_Digital classes/functions
modified slightly to work with a Microchip PIC18F25K22.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LCDhd44780_h
#define LCDhd44780_h

#include <stdint.h>
#include <stdio.h>

/***** Update the defines below *****/

//Needed for delay function
#define _XTAL_FREQ 64000000   //16MHz int. clk. x PLL(4x) = 64MHz clock


//LCD Attributes
#define LCD_BITMODE 0x04 //Possible values: 4bit = 0x04 or 8bit = 0x08
#define LCD_LINES   0x02 //Possible values: 1 line = 0x01, 2 lines = 0x02
#define LCD_DOT_SIZE    0x00 //Possible values: 0x00 = 5x8, 0x04 = 5x10

//set pin assignments here
unsigned _unused_pin = 0; //Set any unused pin such as RW or D4-D7 (4bit mode) to ) _unused_pin.

#define LCD_RS_PIN_LAT  LATCbits.LC7
#define LCD_RS_PIN_TRIS TRISCbits.RC7

#define LCD_RW_PIN_LAT  _unused_pin
#define LCD_RW_PIN_TRIS _unused_pin

#define LCD_ENABLE_PIN_LAT  LATCbits.LC6
#define LCD_ENABLE_PIN_TRIS TRISCbits.RC6

#define LCD_DATA_PIN0_LAT  LATCbits.LC5
#define LCD_DATA_PIN0_TRIS TRISCbits.RC5

#define LCD_DATA_PIN1_LAT  LATCbits.LC4
#define LCD_DATA_PIN1_TRIS TRISCbits.RC4

#define LCD_DATA_PIN2_LAT  LATCbits.LC1
#define LCD_DATA_PIN2_TRIS TRISCbits.RC1

#define LCD_DATA_PIN3_LAT  LATCbits.LC0
#define LCD_DATA_PIN3_TRIS TRISCbits.RC0

#define LCD_DATA_PIN4_LAT  _unused_pin
#define LCD_DATA_PIN4_TRIS _unused_pin

#define LCD_DATA_PIN5_LAT  _unused_pin
#define LCD_DATA_PIN5_TRIS _unused_pin

#define LCD_DATA_PIN6_LAT  _unused_pin
#define LCD_DATA_PIN6_TRIS _unused_pin

#define LCD_DATA_PIN7_LAT  _unused_pin
#define LCD_DATA_PIN7_TRIS _unused_pin



/***** You should not have to change anything below this line ******/

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// levels
#define LOW 0
#define HIGH 1

//Print defines
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

void lcdBegin();

void lcdClear();
void lcdHome();

void lcdNoDisplay();
void lcdDisplay();
void lcdNoBlink();
void lcdBlink();
void lcdNoCursor();
void lcdCursor();
void lcdScrollDisplayLeft();
void lcdScrollDisplayRight();
void lcdLeftToRight();
void lcdRightToLeft();
void lcdAutoscroll();
void lcdNoAutoscroll();

void lcdCreateChar(uint8_t, uint8_t[]);
void lcdSetCursor(uint8_t, uint8_t);
size_t lcdWrite(uint8_t);
void lcdCommand(uint8_t);

void lcdSend(uint8_t, uint8_t);
void lcdWrite4bits(uint8_t);
void lcdWrite8bits(uint8_t);
void lcdPulseEnable();

unsigned int _displayfunction;
unsigned int _displaycontrol;
unsigned int _displaymode;

unsigned int _numlines;
unsigned int _currline;

size_t lcdWrite(uint8_t);
void lcdPrintStr(const char * );
void lcdPrintLng(long, int);
void lcdPrintUnLng(unsigned long, int);
void lcdPrintInt(int, int);
void lcdPrintUnInt(unsigned int, int);
void lcdPrintChr(char);
void lcdPrintUnChr(unsigned char, int);
void lcdPrintDbl(double, int);
void lcdPrintNumber(unsigned long, uint8_t);

#endif
