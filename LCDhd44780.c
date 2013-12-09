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

#include "LCDhd44780.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "plib/delays.h"
#include <xc.h>

const unsigned _rs_pin = 0;
const unsigned _rw_pin = 1;
const unsigned _enable_pin = 0x02;
const unsigned _data_pin0 = 0x03;
const unsigned _data_pin1 = 0x04;
const unsigned _data_pin2 = 0x05;
const unsigned _data_pin3 = 0x06;
const unsigned _data_pin4 = 0x07;
const unsigned _data_pin5 = 0x08;
const unsigned _data_pin6 = 0x09;
const unsigned _data_pin7 = 0x0A;


/***** Based on Arduino wiring_digital Functions *****/

void digitalWrite(const unsigned pin, unsigned int level) {
    if (pin == _rs_pin) {
        LCD_RS_PIN_LAT = level;
    }else if (pin == _rw_pin) {
        LCD_RW_PIN_LAT = level;
    }else if (pin == _enable_pin) {
        LCD_ENABLE_PIN_LAT = level;
    }else if (pin == _data_pin0) {
        LCD_DATA_PIN0_LAT = level;
    }else if (pin == _data_pin1) {
        LCD_DATA_PIN1_LAT = level;
    }else if (pin == _data_pin2) {
        LCD_DATA_PIN2_LAT = level;
    }else if (pin == _data_pin3) {
        LCD_DATA_PIN3_LAT = level;
    }else if (pin == _data_pin4) {
        LCD_DATA_PIN4_LAT = level;
    }else if (pin == _data_pin5) {
        LCD_DATA_PIN5_LAT = level;
    }else if (pin == _data_pin6) {
        LCD_DATA_PIN6_LAT = level;
    }else if (pin == _data_pin7) {
        LCD_DATA_PIN7_LAT = level;
    }
}

void pinModeOutput(const unsigned int pin) {
    if (pin == _rs_pin) {
        LCD_RS_PIN_TRIS = 0;
    }else if (pin == _rw_pin) {
          LCD_RW_PIN_TRIS = 0;
    }else if (pin == _enable_pin) {
        LCD_ENABLE_PIN_TRIS = 0;
    }else if (pin == _data_pin0) {
        LCD_DATA_PIN0_TRIS = 0;
    }else if (pin == _data_pin1) {
        LCD_DATA_PIN1_TRIS = 0;
    }else if (pin == _data_pin2) {
        LCD_DATA_PIN2_TRIS = 0;
    }else if (pin == _data_pin3) {
        LCD_DATA_PIN3_TRIS = 0;
    }else if (pin == _data_pin4) {
        LCD_DATA_PIN4_TRIS = 0;
    }else if (pin == _data_pin5) {
        LCD_DATA_PIN5_TRIS = 0;
    }else if (pin == _data_pin6) {
        LCD_DATA_PIN6_TRIS = 0;
    }else if (pin == _data_pin7) {
        LCD_DATA_PIN7_TRIS = 0;
    }
}


/***** Functions below based on Arduino LiquidCrystal Class *****/


//lcdBegin() merges Arduino LiquidCrystal class contructor and Begin() function
void lcdBegin() {

    pinModeOutput(_rs_pin);
    // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
    if (_rw_pin != 255) {
        pinModeOutput(_rw_pin);
    }
    pinModeOutput(_enable_pin);

    if (LCD_BITMODE == 4)
        _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    else
        _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;

    if (LCD_LINES > 1) {
        _displayfunction |= LCD_2LINE;
    }
    _numlines = LCD_LINES;
    _currline = 0;

    // for some 1 line displays you can select a 10 pixel high font
    if ((LCD_DOT_SIZE != 0) && (LCD_LINES == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
    __delay_ms(10);
    __delay_ms(10);
    __delay_ms(10);
    __delay_ms(10);
    __delay_ms(10);
    // Now we pull both RS and R/W low to begin commands
    digitalWrite(_rs_pin, LOW);
    digitalWrite(_enable_pin, LOW);
    if (_rw_pin != 255) {
        digitalWrite(_rw_pin, LOW);
    }

    //put the LCD into 4 bit or 8 bit mode
    if (!(_displayfunction & LCD_8BITMODE)) {
        // this is according to the hitachi HD44780 datasheet
        // figure 24, pg 46

        // we start in 8bit mode, try to set 4 bit mode
        lcdWrite4bits(0x03);
        __delay_us(4500);

        // second try
        lcdWrite4bits(0x03);
        __delay_us(4500);

        // third go!
        lcdWrite4bits(0x03);
        __delay_us(150);

        // finally, set to 4-bit interface
        lcdWrite4bits(0x02);
    } else {
        // this is according to the hitachi HD44780 datasheet
        // page 45 figure 23

        // Send function set command sequence
        lcdCommand(LCD_FUNCTIONSET | _displayfunction);
        __delay_us(4500);

        // second try
        lcdCommand(LCD_FUNCTIONSET | _displayfunction);
        __delay_us(150);
        // third go
        lcdCommand(LCD_FUNCTIONSET | _displayfunction);
    }

    // finally, set # lines, font size, etc.
    lcdCommand(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcdDisplay();

    // clear it off
    lcdClear();

    // Initialize to default text direction (for romance languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    lcdCommand(LCD_ENTRYMODESET | _displaymode);

}

/********** high level commands, for the user! */
void lcdClear() {
    lcdCommand(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
    __delay_us(2000);
}

void lcdHome() {
    lcdCommand(LCD_RETURNHOME); // set cursor position to zero
    __delay_us(2000);
}

void lcdSetCursor(uint8_t col, uint8_t row) {
    int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= _numlines) {
        row = _numlines - 1; // we count rows starting w/0
    }

    lcdCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)

void lcdNoDisplay() {
    _displaycontrol &= ~LCD_DISPLAYON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcdDisplay() {
    _displaycontrol |= LCD_DISPLAYON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off

void lcdNoCursor() {
    _displaycontrol &= ~LCD_CURSORON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcdCursor() {
    _displaycontrol |= LCD_CURSORON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor

void lcdNoBlink() {
    _displaycontrol &= ~LCD_BLINKON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcdBlink() {
    _displaycontrol |= LCD_BLINKON;
    lcdCommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM

void lcdScrollDisplayLeft(void) {
    lcdCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcdScrollDisplayRight(void) {
    lcdCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right

void lcdLeftToRight(void) {
    _displaymode |= LCD_ENTRYLEFT;
    lcdCommand(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left

void lcdRightToLeft(void) {
    _displaymode &= ~LCD_ENTRYLEFT;
    lcdCommand(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor

void lcdAutoscroll(void) {
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    lcdCommand(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor

void lcdNoAutoscroll(void) {
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcdCommand(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters

void lcdCreateChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7; // we only have 8 locations 0-7
    lcdCommand(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++) {
        lcdWrite(charmap[i]);
    }
}

/*********** mid level commands, for sending data/cmds */

void lcdCommand(uint8_t value) {
    lcdSend(value, LOW);
}

size_t lcdWrite(uint8_t value) {
    lcdSend(value, HIGH);
    return 1;
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void lcdSend(uint8_t value, uint8_t mode) {
    digitalWrite(_rs_pin, mode);

    // if there is a RW pin indicated, set it low to Write
    if (_rw_pin != 255) {
        digitalWrite(_rw_pin, LOW);
    }

    if (_displayfunction & LCD_8BITMODE) {
        lcdWrite8bits(value);
    } else {
        lcdWrite4bits(value >> 4);
        lcdWrite4bits(value);
    }
}

void lcdPulseEnable(void) {
    digitalWrite(_enable_pin, LOW);
    __delay_us(1);
    digitalWrite(_enable_pin, HIGH);
    __delay_us(1);
    digitalWrite(_enable_pin, LOW);
    __delay_us(100);
}

void lcdWrite4bits(uint8_t value) {
    pinModeOutput(_data_pin0);
    pinModeOutput(_data_pin1);
    pinModeOutput(_data_pin2);
    pinModeOutput(_data_pin3);

    int i = 0;
    digitalWrite(_data_pin0, (value >> i++) & 0x01);
    digitalWrite(_data_pin1, (value >> i++) & 0x01);
    digitalWrite(_data_pin2, (value >> i++) & 0x01);
    digitalWrite(_data_pin3, (value >> i++) & 0x01);

    lcdPulseEnable();
}

void lcdWrite8bits(uint8_t value) {
    pinModeOutput(_data_pin0);
    pinModeOutput(_data_pin1);
    pinModeOutput(_data_pin2);
    pinModeOutput(_data_pin3);
    pinModeOutput(_data_pin4);
    pinModeOutput(_data_pin5);
    pinModeOutput(_data_pin6);
    pinModeOutput(_data_pin7);

    int i = 0;
    digitalWrite(_data_pin0, (value >> i++) & 0x01);
    digitalWrite(_data_pin1, (value >> i++) & 0x01);
    digitalWrite(_data_pin2, (value >> i++) & 0x01);
    digitalWrite(_data_pin3, (value >> i++) & 0x01);
    digitalWrite(_data_pin4, (value >> i++) & 0x01);
    digitalWrite(_data_pin5, (value >> i++) & 0x01);
    digitalWrite(_data_pin6, (value >> i++) & 0x01);
    digitalWrite(_data_pin7, (value >> i++) & 0x01);

    lcdPulseEnable();
}


/***** Print Functions based on Ardunio Print class *****/

void lcdPrintStr(const char *str) {
        while (*str)
        lcdWrite(*str++);
}

void lcdPrintLng(long n, int base)
{
  if (base == 0) {
    lcdWrite(n);
  } else if (base == 10) {
    if (n < 0) {
      lcdWrite('-');
      n = -n;
    }
    lcdPrintNumber(n, 10);
  } else {
    lcdPrintNumber(n, base);
  }
}

void lcdPrintUnLng(unsigned long n, int base)
{
  if (base == 0) lcdWrite(n);
  else lcdPrintNumber(n, base);
}

void lcdPrintInt(int n, int base)
{
  lcdPrintLng((long) n, base);
}

void lcdPrintUnInt(unsigned int n, int base)
{
  lcdPrintUnLng((unsigned long) n, base);
}

void lcdPrintChr(char c)
{
  lcdWrite(c);
}

void lcdPrintUnChr(unsigned char b, int base)
{
  lcdPrintUnLng((unsigned long) b, base);
}

void lcdPrintDbl(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
     lcdWrite('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  lcdPrintUnLng(int_part, DEC);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    lcdWrite('.');

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = (int)remainder;
    lcdPrintInt(toPrint, DEC);
    remainder -= toPrint;
  }
}

void lcdPrintNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  lcdPrintStr(str);
}
