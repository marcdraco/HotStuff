/*
  Copyright 2020, Marc Draco & Daniel Melvin

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THERE ARE NO BUGS IN THIS CODE, JUST FEATURES, SOME OF WHICH MAY CAUSE IT TO BEHAVE
  ERRATICALLY. SINCE YOU GOT IT FOR FREE, FIX THEM OR DON'T COME CRYING TO US!
  YES, IT'S WORDY AND WE'VE ESCHEWED MANY C "SHORTCUTS" TO MAKE IT EASIER FOR BEGINNERS

  Thanks to Steve Wood (ebay: audioSpectrumAnalysers) for the serial programmer.
  3.5" TFT shield supplied by A-Z Delivery via Amazon.  
*/


#define SERIAL_DEBUG

// use this if you have an incident like someone did...
#define SENSOR_MISSING_OR_BUSTED  

 // You have a dirty mind! This for the i2C version!
 //#define TOPLESS                

// remove this line to have the unit read in fahrenheit
#define METRIC                   
 
// This is for the experimental analog display
//#define CLOCKWISE


/*
   Poor man's unit testing. These defines can set temperature and humidity.reading
   well outside what the DHT22 is sending in order to check changes to code.
   Remember it makes no sense have both high AND low temp/RH% the same time though
   Temperature for debug purposes is in CENTIGRADE!

*/

// #define DEBUG_OVERTEMP_ALARM 45
// #define DEBUG_EXCESS_DAMP_ALARM 90
// #define DEBUG_DRY_AIR_ALARM 10
// #define DEBUG_FROST_ALARM -5

#define SimpleDHTSuccess         0 
#define SimpleDHTErrStartLow     1
#define SimpleDHTErrStartHigh    2
#define SimpleDHTErrDataLow      3
#define SimpleDHTErrDataHigh     4
#define SimpleDHTErrDataEOF      5
#define SimpleDHTErrDataChecksum 6

#define SHOW_BANDS               // optionally plot some dotted lines for normal values
#define BUTTON_PIN 10
#define DHT22_POWER 11        // pin to power the DHT22 since the power pins are covered.
#define DHT22_DATA 12         // The DHT 22 can be powered elsewhere leaving this free however.
#define ALARM_PIN 13          // LED or a high-impedance buzzer
#define GRAPH_WIDTH 240
#define WIDTH_SCALE 1         // divide the size of the screen based on a 320x240 matrix
#define HEIGHT_SCALE 1        // divide the size of the screen based on a 320x240 matrix

/*
   A good selection of simple colour defines
   from David Prentice's TFT library
*/

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))
#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define WHITE     0xFFFF
#define GREY      RGB(127, 127, 127)
#define GRAY      RGB(127, 127, 127)
#define DARKGREY  RGB(64, 64, 64)
#define DARKGRAY  RGB(64, 64, 64)
#define DEEPGREY  RGB(16, 16, 16)
#define DEEPGRAY  RGB(16, 16, 16)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)
#define BROWNISH  RGB(0x2e,0x2d,0x0)
#define PURPLEISH RGB(0x2f,0x00,0x2d)

/*
   Timer 1 is the 16 bit timer so this is also used for the "in-app" RTC so be careful!
   Consult the ISR below for further notes Timer 1 to fire every 4 seconds
   Adjust this if your board has a different speed!

   x = 65535 - (16Mhz * 4/1024)
   therefore x = 3035.
   https://oscarliang.com/arduino-timer-and-interrupt-tutorial/
*/

#define UPDATER 49910  // one second timer. 

MCUFRIEND_kbv screen;
UniversalDHT dht22(DHT22_DATA);