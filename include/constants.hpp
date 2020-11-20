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
*/

#ifndef __DRACO_HOTSTUFF_CONSTANTS_H
#define __DRACO_HOTSTUFF_CONSTANTS_H

#include <Arduino.h>
#include <inttypes.h>

/**
 * use this if you have an incident like someone did...
 * after Marc's sloppy soldering (and failure to heatsink
 * the DHT22 pins, it registered a bad output... (blah blah)
 * The output, however, is still (broadly) within usable limits
 * so this is used in cases like that to disable the failure screen!
 * 
 * (Melvin forgets I have write access to this too... you can't 
 * make it up. I'm gonna slap him with a haddock at this rate.)
 */
 
#define SENSOR_MISSING_OR_BUSTED  

/**
 * @brief TOPLESS is for the version with i2C displays (no shield, hence topless)
 */
 
 //#define TOPLESS                 

/**
 * @brief This is for the experimental analog display
 */
  
//#define CLOCKWISE

/**
 * @brief Enable the huge metric 7-segLCD display
 * @remark This ONLY works for metric right now due to the size
 * of the font.
 */
  
//#define SIMPLE_LCD

/**
 * @brief 
 * 
 * @remark Poor man's unit testing. These defines can set temperature and humidity.reading
 * well outside what the DHT22 is sending in order to check changes to code.
 * Remember it makes no sense have both high AND low temp/RH% the same time though
 * Temperature for debug purposes is in CENTIGRADE!
 * 
*/



// #define DEBUG_OVERTEMP_ALARM 45
// #define DEBUG_EXCESS_DAMP_ALARM 90
// #define DEBUG_DRY_AIR_ALARM 10
// #define DEBUG_FROST_ALARM 30

constexpr int SimpleDHTSuccess         {0}; 
constexpr int SimpleDHTErrStartLow     {1};
constexpr int SimpleDHTErrStartHigh    {2};
constexpr int SimpleDHTErrDataLow      {3};
constexpr int SimpleDHTErrDataHigh     {4};
constexpr int SimpleDHTErrDataEOF      {5};
constexpr int SimpleDHTErrDataChecksum {6};

#define SHOW_BANDS                    // optionally plot some dotted lines for normal values
constexpr int BUTTON_PIN     {10};      // the acknowlegement button to stop alerts for ice, damp etc.
constexpr int DHT22_POWER    {11};      // pin to power the DHT22 since the power pins are covered.
constexpr int DHT22_DATA     {12};      // The DHT 22 can be powered elsewhere leaving this free however.
constexpr int ALARM_PIN      {13};      // LED or a high-impedance buzzer

constexpr int UPTIME_Y       {228};
constexpr int TRADIAL_X      {160};
constexpr int TRADIAL_Y      {120};
constexpr int HRADIAL        {160};
constexpr int INNER_RADIUS   {40 };
constexpr int OUTER_RADIUS   {70 };

constexpr int TFT_WIDTH      {320};
constexpr int TFT_HEIGHT     {240};

constexpr int FONT_BUFF_WIDTH    {10}; // special "offscreen" buffer for deleting and pre-rendering LARGE fonts (keep this to a div of 3)
constexpr int FONT_BUFF_HEIGHT   {10};  // The size of this is crucial because it uses a LOT of RAM.

#ifndef toFahrenheit
#define toFahrenheit(a) (a * 1.8 + 32)
#endif

#define STOP while (true) {}
/*
   A good selection of simple colour defines
   from David Prentice's TFT library
*/

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))

#define LIGHTGREY RGB(200, 200, 200)
#define GREY      RGB(128, 128, 128)
#define DARKGREY  RGB(64, 64, 64)
#define DARKGRAY  RGB(64, 64, 64)
#define DEEPGREY  RGB(16, 16, 16)
#define DEEPGRAY  RGB(16, 16, 16)

#define DEEPGREEN  RGB(0, 16, 0)
#define DEEPRED   RGB(16, 0, 0)
#define DARKRED   RGB(24, 0, 0)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)
#define BROWNISH  RGB(0x2e,0x2d,0x0)
#define PURPLEISH RGB(0x2f,0x00,0x2d)

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

#define defaultPaper  BLACK
#define defaultInk    CYAN
#define reticleColour DEEPGREY

#define HOURS 7

#define LOW_LIMIT_EXCEEDED BLUE
#define HIGH_LIMIT_EXCEEDED RED

/*
  Timer 1 is the 16 bit timer so this is also used for the "in-app" RTC so be careful!
  Consult the ISR below for further notes Timer 1 to fire every 4 seconds
  Adjust this if your board has a different speed!

  x = 65535 - (16Mhz * 4/1024)
  therefore x = 3035.
  https://oscarliang.com/arduino-timer-and-interrupt-tutorial/
*/

#define UPDATER {49910};  // one second timer. 


// Active semaphores
enum semaphores : uint16_t
{
  FROST       = 0x0001, 
  DAMP        = 0x0002, 
  DRY         = 0x0004, 
  OVERTEMP    = 0x0008,
  FLASH       = 0x0010,
  WARNDANGER  = 0x0020,
  UNUSED      = 0x0040,
  ALARMDRY    = 0x0080,
  ALARMFROST  = 0x0100,
  ALARMDAMP   = 0x0200,
  USEMETRIC   = 0x0400,
  UPDATEREADS = 0x0800,
  REDRAWGRAPH = 0x1000,
  RESERVED1   = 0x2000,
  RESERVED2   = 0x4000,
  RESERVED3   = 0x8000,
  RESETALL    = 0xFFFF
};

#define B0000000100000000 = 0x0100
#define B0000001000000000 = 0x0200
#define B0000010000000000 = 0x0400
#define B0000100000000000 = 0x0800
#define B0001000000000000 = 0x1000
#define B0010000000000000 = 0x2000
#define B0100000000000000 = 0x4000
#define B1000000000000000 = 0x8000

// non-active semaphores used for function arguments}
enum  
{
  IMPERIAL = B00000001,
  METRIC   = B00000010,
  HUMIDITY = B00001000,
  HOURLY   = B00010000,
  DAILY    = B00100000,
  RESET    = B01000000,
};


const unsigned char symbolDry [] PROGMEM = {
0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x23, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xfe, 0x23, 0xff, 0xff, 0xcf, 0xff, 0xf0, 0xff, 0xfe, 0x31, 0xff, 0xff, 0x87, 0xff, 0xf0, 
0xff, 0xfc, 0x71, 0xff, 0xff, 0x03, 0xff, 0xf0, 0xff, 0xfc, 0x71, 0xff, 0xfe, 0x01, 0xff, 0xf0, 
0xff, 0xf8, 0xf8, 0xff, 0xfc, 0x00, 0xff, 0xf0, 0xff, 0xf8, 0xfc, 0xff, 0xf8, 0x88, 0x7f, 0xf0, 
0xff, 0xf1, 0xfc, 0x7f, 0xf9, 0x8c, 0xff, 0xf0, 0xff, 0xf1, 0xfc, 0x7f, 0xff, 0x8f, 0xff, 0xf0, 
0xff, 0xe3, 0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xf0, 0xff, 0xe3, 0xfe, 0x1f, 0xff, 0x8f, 0xff, 0xf0, 
0xff, 0xc7, 0xff, 0x1f, 0xff, 0x1f, 0xc3, 0xf0, 0xff, 0x87, 0xff, 0x8f, 0xfe, 0x1f, 0x81, 0xf0, 
0xff, 0x8f, 0xff, 0x87, 0xfc, 0x3f, 0x00, 0xf0, 0xff, 0x0f, 0xff, 0xc7, 0xf8, 0x7e, 0x00, 0x70, 
0xfe, 0x1f, 0xff, 0xef, 0xe0, 0xfc, 0x20, 0x30, 0xfe, 0x3f, 0xff, 0xff, 0x81, 0xfc, 0x66, 0x30, 
0xfc, 0x3f, 0xff, 0xfe, 0x07, 0xfe, 0xe7, 0x70, 0xf8, 0x7f, 0xff, 0xf0, 0x1f, 0xff, 0xc7, 0xf0, 
0xf8, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xc7, 0xf0, 0xf0, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xc7, 0xf0, 
0xf1, 0xff, 0xf8, 0x0c, 0x3f, 0xff, 0x8f, 0xf0, 0xe3, 0xff, 0xf0, 0x3e, 0x3f, 0xff, 0x0f, 0xf0, 
0xe3, 0xff, 0xc1, 0xff, 0x1f, 0xfe, 0x1f, 0xf0, 0xc7, 0xff, 0x87, 0xff, 0x1f, 0xf8, 0x3f, 0xf0, 
0xc7, 0xff, 0x0f, 0xff, 0xff, 0xe0, 0x7f, 0xf0, 0x8f, 0xfe, 0x1f, 0xff, 0xff, 0x81, 0xff, 0xf0, 
0x8f, 0xfe, 0x3f, 0xff, 0xfc, 0x07, 0xff, 0xf0, 0x8f, 0xfc, 0x7f, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 
0x9f, 0xfc, 0x7f, 0xff, 0xc0, 0x7f, 0xff, 0xf0, 0x1f, 0xfc, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xf0, 
0x1f, 0xf8, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xf0, 0x1f, 0xf8, 0xff, 0xf0, 0x47, 0xff, 0xff, 0xf0, 
0x1f, 0xff, 0xff, 0xe1, 0xe7, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xc3, 0xe7, 0xff, 0xff, 0xf0, 
0x1f, 0xff, 0xff, 0x87, 0xe7, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0x0f, 0xc7, 0xff, 0xff, 0xf0, 
0x1f, 0xff, 0xff, 0x1f, 0xc7, 0xff, 0xff, 0xf0, 0x9f, 0xff, 0xfe, 0x3f, 0xc7, 0xff, 0xff, 0xf0, 
0x9f, 0xff, 0xfe, 0x3f, 0xc7, 0xff, 0xff, 0xf0, 0x8f, 0xff, 0xfe, 0x3f, 0x8f, 0xff, 0xff, 0xf0, 
0xcf, 0xff, 0xfe, 0x7f, 0x8f, 0xff, 0xff, 0xf0, 0xc7, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xf0, 
0xc7, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xf0, 0xe3, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xf0, 
0xf1, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xf0, 0xf8, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xf0, 
0xfc, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xfe, 0x1f, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0x07, 0xff, 0x07, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xe0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0
};

const unsigned char symbolIce [] PROGMEM = {
0xff, 0xff, 0xfc, 0xff, 0xf3, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x7f, 0xe1, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xf8, 0x3f, 0xc1, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x1f, 0x83, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfe, 0x0f, 0x07, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x06, 0x0f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xfe, 0x7f, 0xc0, 0x3f, 0xe7, 0xff, 0xf0, 
0xff, 0xfc, 0x3f, 0xe0, 0x7f, 0xc3, 0xff, 0xf0, 0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 
0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 
0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 
0xff, 0x00, 0x3f, 0xf0, 0xff, 0xc0, 0x0f, 0xf0, 0xfe, 0x00, 0x3f, 0xf0, 0xff, 0xc0, 0x07, 0xf0, 
0xfe, 0x00, 0x1f, 0xf0, 0xff, 0x80, 0x07, 0xf0, 0xff, 0x00, 0x0f, 0xf0, 0xff, 0x00, 0x0f, 0xf0, 
0xff, 0xff, 0x07, 0xf0, 0xfe, 0x0f, 0xff, 0xf0, 0xff, 0xff, 0x83, 0xf0, 0xfc, 0x1f, 0xff, 0xf0, 
0xff, 0xff, 0xc1, 0xf0, 0xf8, 0x3f, 0xff, 0xf0, 0x9f, 0xff, 0xe0, 0xf0, 0xf0, 0x7f, 0xff, 0x90, 
0x0f, 0xff, 0xf0, 0x70, 0xe0, 0xff, 0xff, 0x00, 0x07, 0xff, 0xf8, 0x30, 0xc1, 0xff, 0xfe, 0x00, 
0x83, 0xff, 0xfc, 0x10, 0x83, 0xff, 0xfc, 0x10, 0xc1, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xf8, 0x30, 
0xe0, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xf0, 0x70, 0xf0, 0x7f, 0xff, 0x80, 0x1f, 0xff, 0xe0, 0xf0, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 
0xf0, 0x7f, 0xff, 0x80, 0x1f, 0xff, 0xe0, 0xf0, 0xe0, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xf0, 0x70, 
0xc1, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xf8, 0x30, 0x83, 0xff, 0xfc, 0x10, 0x83, 0xff, 0xfc, 0x10, 
0x07, 0xff, 0xf8, 0x30, 0xc1, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0xf0, 0x70, 0xe0, 0xff, 0xff, 0x00, 
0x9f, 0xff, 0xe0, 0xf0, 0xf0, 0x7f, 0xff, 0x90, 0xff, 0xff, 0xc1, 0xf0, 0xf8, 0x3f, 0xff, 0xf0, 
0xff, 0xff, 0x83, 0xf0, 0xfc, 0x1f, 0xff, 0xf0, 0xff, 0xff, 0x07, 0xf0, 0xfe, 0x0f, 0xff, 0xf0, 
0xff, 0x00, 0x0f, 0xf0, 0xff, 0x00, 0x0f, 0xf0, 0xfe, 0x00, 0x1f, 0xf0, 0xff, 0x80, 0x07, 0xf0, 
0xfe, 0x00, 0x3f, 0xf0, 0xff, 0xc0, 0x07, 0xf0, 0xff, 0x00, 0x3f, 0xf0, 0xff, 0xc0, 0x0f, 0xf0, 
0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 
0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 
0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf0, 0xff, 0xfc, 0x3f, 0xe0, 0x7f, 0xc3, 0xff, 0xf0, 
0xff, 0xfe, 0x7f, 0xc0, 0x3f, 0xe7, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x06, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0x0f, 0x07, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfc, 0x1f, 0x83, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x3f, 0xc1, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xf8, 0x7f, 0xe1, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0xff, 0xf3, 0xff, 0xff, 0xf0
};

const unsigned char symbolHot [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xfe, 0x7f, 0xcf, 0x3f, 0xf3, 0xff, 0xf0, 
0xff, 0xfe, 0x3f, 0xbf, 0xdf, 0xe3, 0xff, 0xf0, 0xff, 0xff, 0x1f, 0x7f, 0xef, 0xc7, 0xff, 0xf0, 
0xff, 0xff, 0x8f, 0x7f, 0xf7, 0x8f, 0xff, 0xf0, 0xff, 0xff, 0xc7, 0x7f, 0xf7, 0x1f, 0xff, 0xf0, 
0xff, 0xff, 0xe3, 0x7f, 0xf6, 0x3f, 0xff, 0xf0, 0xff, 0xff, 0xf7, 0x7f, 0xf6, 0x7f, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x7f, 0xf7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x4f, 0x77, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x0e, 0xb7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x36, 0xc7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x76, 0xe7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0x80, 0x3f, 0xff, 0xff, 0xc0, 0x1f, 0xf0, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xe0, 0x1f, 0xf0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xce, 0x7f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0xae, 0xbf, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x76, 0xdf, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x75, 0xef, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xf3, 0x79, 0xf6, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xe3, 0x7f, 0xf4, 0x7f, 0xff, 0xf0, 
0xff, 0xff, 0xc7, 0x7f, 0xf6, 0x3f, 0xff, 0xf0, 0xff, 0xff, 0x8f, 0x79, 0xf7, 0x1f, 0xff, 0xf0, 
0xff, 0xff, 0x1f, 0x79, 0xf7, 0x8f, 0xff, 0xf0, 0xff, 0xfe, 0x3f, 0x79, 0xf7, 0xc7, 0xff, 0xf0, 
0xff, 0xfe, 0x7f, 0x79, 0xf7, 0xe7, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x79, 0xf7, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0x79, 0xf7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfc, 0xf9, 0xfb, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfd, 0xf8, 0xf9, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xf9, 0xe0, 0x7d, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfb, 0xe7, 0x3c, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfb, 0xcf, 0x1c, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfb, 0xcf, 0x9c, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfb, 0xcf, 0x1c, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf9, 0xe2, 0x3d, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfd, 0xf0, 0x7d, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0xff, 0xfb, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xfe, 0x7f, 0xf3, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x3f, 0xe7, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0x87, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};

const unsigned char symbolDamp [] PROGMEM = {
0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xfc, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf8, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xf8, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xcf, 0xf0, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x8f, 0xf0, 
0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x07, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x03, 0xf0, 
0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x03, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01, 0xf0, 
0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0xf0, 
0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x70, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0x00, 0x70, 
0x80, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0x00, 0x30, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x30, 
0xc0, 0x00, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x10, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x10, 
0xf8, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x10, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xbf, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xc0, 0x00, 0x10, 
0xff, 0xff, 0xff, 0x1f, 0xff, 0xe0, 0x00, 0x10, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xe0, 0x00, 0x30, 
0xff, 0xff, 0xfc, 0x07, 0xff, 0xf0, 0x00, 0x70, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xf8, 0x00, 0xf0, 
0xff, 0xff, 0xf8, 0x03, 0xff, 0xfe, 0x03, 0xf0, 0xff, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xf0, 
0xff, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xf0, 
};
#endif