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

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF, PLLCFG = OFF //CONFIG1H
#pragma config PWRTEN = OFF, BOREN = OFF, BORV = 250                 //CONFIG2L
#pragma config WDTEN = OFF, WDTPS = 32768                            //CONFIG2H
#pragma config MCLRE = EXTMCLR, PBADEN = OFF, HFOFST = OFF	     //CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF                   //CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF            //CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                  //CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF        //CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                    //CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF    //CONFIG7L
#pragma config EBTRB = OFF                                           //CONFIG7H

#include <xc.h>
#include "plib/delays.h"
#include "LCDhd44780.h"

void twoSecDelay() {
    for (int x = 0; x < 200; x++) {
        __delay_ms(10);
    }
}

void main(void) {
    int x;
    double y;

    uint8_t diamond[8] = {
        0b00000,
        0b00100,
        0b01010,
        0b10001,
        0b10001,
        0b01010,
        0b00100,
        0b00000
    };
    uint8_t square[8] = {
        0b00000,
        0b11111,
        0b10001,
        0b10001,
        0b10001,
        0b11111,
        0b00000,
        0b00000
    };


    OSCCON = 0x70; //1MHz Internal Oscillator
    OSCTUNEbits.PLLEN = 1; //4x PLL

    lcdBegin();

    while (1) {

        //print simple string
        lcdClear();
        lcdHome();
        lcdPrintStr("Print String");
        lcdSetCursor(0, 1);
        lcdPrintStr("Hello World");

        twoSecDelay();

        //print simple string
        lcdClear();
        lcdHome();
        lcdPrintStr("Print Char[]");
        lcdSetCursor(0, 1);
        char str1[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
        lcdPrintStr(str1);

        twoSecDelay();

        //print simple string
        lcdClear();
        lcdHome();
        lcdPrintStr("Print nul Char[]");
        lcdSetCursor(0, 1);
        char str2[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};
        lcdPrintStr(str2);

        twoSecDelay();

        //print simple string
        lcdClear();
        lcdHome();
        lcdPrintStr("Print 1 Char 'W'");
        lcdSetCursor(0, 1);
        lcdPrintChr('W');

        twoSecDelay();

        //Cursor
        lcdClear();
        lcdHome();
        lcdPrintStr("Display Cursor");
        lcdSetCursor(0, 1);
        lcdCursor();

        twoSecDelay();

        //Cursor
        lcdClear();
        lcdHome();
        lcdPrintStr("Blink Cursor");
        lcdSetCursor(0, 1);
        lcdBlink();

        twoSecDelay();

        //Cursor
        lcdClear();
        lcdHome();
        lcdPrintStr("No Blink ");
        lcdSetCursor(0, 1);
        lcdNoBlink();

        twoSecDelay();

        //Cursor
        lcdClear();
        lcdHome();
        lcdPrintStr("No Cursor ");
        lcdSetCursor(0, 1);
        lcdNoCursor();

        twoSecDelay();

        //print int as decimal
        lcdClear();
        lcdHome();
        lcdPrintStr("Print 123 as DEC");
        x = 123;
        lcdSetCursor(0, 1);
        lcdPrintInt(x, DEC);

        twoSecDelay();

        //print int as hex
        lcdClear();
        lcdHome();
        lcdPrintStr("Print 123 as HEX");
        x = 123;
        lcdSetCursor(0, 1);
        lcdPrintInt(x, HEX);

        twoSecDelay();

        //print int as oct
        lcdClear();
        lcdHome();
        lcdPrintStr("Print as 123 OCT");
        x = 123;
        lcdSetCursor(0, 1);
        lcdPrintInt(x, OCT);

        twoSecDelay();

        //print int as bin
        lcdClear();
        lcdHome();
        lcdPrintStr("Print 123 as BIN");
        x = 123;
        lcdSetCursor(0, 1);
        lcdPrintInt(x, BIN);

        twoSecDelay();

        //print double with 3 decimal places
        lcdClear();
        lcdHome();
        lcdPrintStr("Prt Dbl 123.456");
        y = 123.456;
        lcdSetCursor(0, 1);
        lcdPrintDbl(y, 3);
        lcdPrintStr(" 3 places");

        twoSecDelay();

        //print double with 2 decimal places
        lcdClear();
        lcdHome();
        lcdPrintStr("Prt Dbl 123.456");
        y = 123.456;
        lcdSetCursor(0, 1);
        lcdPrintDbl(y, 2);
        lcdPrintStr("  2 places");

        twoSecDelay();

        //print double with 1 decimal places
        lcdClear();
        lcdHome();
        lcdPrintStr("Prt Dbl 123.456");
        y = 123.456;
        lcdSetCursor(0, 1);
        lcdPrintDbl(y, 1);
        lcdPrintStr("   1 places");

        twoSecDelay();

        //print double with 1 decimal places
        lcdClear();
        lcdHome();
        lcdPrintStr("Prt Dbl -654.321");
        y = -654.321;
        lcdSetCursor(0, 1);
        lcdPrintDbl(y, 3);

        twoSecDelay();

        //scrolling example
        lcdClear();
        lcdHome();
        lcdPrintStr("Scrolling");
        //1sec delay
        for (x = 0; x < 100; x++) {
            __delay_ms(10);
        }


        // scroll 16 positions to the right to move it offscreen right:
        for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
            // scroll one position right:
            lcdScrollDisplayRight();
            // wait a bit:
            for (x = 0; x < 20; x++) {
                __delay_ms(10);
            }
        }

        // scroll 16 positions (display length + string length) to the left
        // to move it back to center:
        for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
            // scroll one position left:
            lcdScrollDisplayLeft();
            // wait a bit:
            for (x = 0; x < 20; x++) {
                __delay_ms(10);
            }
        }

        twoSecDelay();

        //Create Char example
        lcdClear();
        lcdHome();
        lcdPrintStr("Create Chars");
        lcdCreateChar(0, diamond);
        lcdCreateChar(1, square);
        lcdSetCursor(0, 1);
        lcdWrite(0);
        lcdSetCursor(3, 1);
        lcdWrite(1);
        lcdSetCursor(6, 1);
        lcdWrite(0);
        lcdSetCursor(9, 1);
        lcdWrite(1);
        lcdSetCursor(12, 1);
        lcdWrite(0);
        lcdSetCursor(15, 1);
        lcdWrite(1);

        twoSecDelay();
    }
}
