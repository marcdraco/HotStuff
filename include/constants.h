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


constexpr int SimpleDHTSuccess         {0}; 
constexpr int SimpleDHTErrStartLow     {1};
constexpr int SimpleDHTErrStartHigh    {2};
constexpr int SimpleDHTErrDataLow      {3};
constexpr int SimpleDHTErrDataHigh     {4};
constexpr int SimpleDHTErrDataEOF      {5};
constexpr int SimpleDHTErrDataChecksum {6};

constexpr int DHT22_POWER    {11};      // pin to power the DHT22 since the power pins are covered.
constexpr int DHT22_DATA     {12};      // The DHT 22 can be powered elsewhere leaving this free however.
constexpr int ALARM_PIN      {13};      // LED or a high-impedance buzzer

constexpr int UPTIME_Y       {228};
constexpr int TRADIAL_X      {160};
constexpr int TRADIAL_Y      {120};
constexpr int HRADIAL        {160};
constexpr int INNER_RADIUS   { 40};
constexpr int OUTER_RADIUS   { 70};

constexpr int TEMPERATURE_X  {290};
constexpr int HUMIDITY_X     {290};
constexpr int AXIS_Y_POSITION {5};

constexpr int READ_SCALAR    {128};

constexpr int TFT_WIDTH      {320};
constexpr int TFT_HEIGHT     {240};

constexpr int FONT_BUFF_WIDTH    {120}; // special "offscreen" buffer for deleting and pre-rendering LARGE fonts (keep this to a div of 3)
constexpr int FONT_BUFF_HEIGHT   {40};  // The size of this is crucial because it uses a LOT of RAM.

constexpr int SYMX1     {0}; 
constexpr int SYMX2   {260};
constexpr int SYMY     {80};


#ifndef toFahrenheit
#define toFahrenheit(a) (a * 1.8 + 32)
#endif

#ifndef toFixed2
#define toFixed(a) (a * 128)    // 328p in the Uno etc. has hardware multiply (not divide!)
#endif

#ifndef fromFixed2
#define fromFixed(a) (a >> 7) // fast div by 128 (this is sufficient to keep 2 decimal places)
#endif

#define SETBIT(bit)   (globals.g_semaphores |= ( bit))    //Set bit in byte addr
#define CLEARBIT(bit) (globals.g_semaphores &= (~bit))   // Clear bit in byte addr
#define CHECKBIT(bit) (globals.g_semaphores &  ( bit))     // Check bit in byte addr
#define FLIPBIT(bit)  (globals.g_semaphores ^= ( bit))    // Flip a bit


#define STOP while (true) {}
/*
   A good selection of simple colour defines
   from David Prentice's TFT library
*/

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))

constexpr uint16_t LIGHTGREY = RGB(200, 200, 200);
constexpr uint16_t GREY      = RGB(128, 128, 128);
constexpr uint16_t DARKGREY  = RGB(64, 64, 64);
constexpr uint16_t DARKGRAY  = RGB(64, 64, 64);
constexpr uint16_t DEEPGREY  = RGB(16, 16, 16);
constexpr uint16_t DEEPGRAY  = RGB(16, 16, 16);
constexpr uint16_t DEEPBLUE  = RGB(0,0,16);
constexpr uint16_t DEEPGREEN = RGB(0, 16, 0);
constexpr uint16_t DEEPRED   = RGB(16, 0, 0);
constexpr uint16_t DARKRED   = RGB(24, 0, 0);
constexpr uint16_t TURQUOISE = RGB(0, 128, 128);
constexpr uint16_t PINK      = RGB(255, 128, 192);
constexpr uint16_t OLIVE     = RGB(128, 128, 0);
constexpr uint16_t PURPLE    = RGB(128, 0, 128);
constexpr uint16_t AZURE     = RGB(0, 128, 255);
constexpr uint16_t ORANGE    = RGB(255, 128, 64);
constexpr uint16_t BROWNISH  = RGB(0x2e, 0x2d, 0x0);
constexpr uint16_t PURPLEISH = RGB(0x2f, 0x00, 0x2d);
constexpr uint16_t BLACK     {0x0000};
constexpr uint16_t BLUE      {0x001F};
constexpr uint16_t RED       {0xF800};
constexpr uint16_t GREEN     {0x07E0};
constexpr uint16_t CYAN      {0x07FF};
constexpr uint16_t MAGENTA   {0xF81F};
constexpr uint16_t YELLOW    {0xFFE0};
constexpr uint16_t WHITE     {0xFFFF};

constexpr int GRAPH_WIDTH  {189};
constexpr int GRAPH_HEIGHT {100};
constexpr int GRAPH_LEFT   {63};
constexpr int GRAPH_Y      {130};
constexpr int BASE         {GRAPH_Y + GRAPH_HEIGHT};

constexpr uint16_t defaultPaper  {BLACK};
constexpr uint16_t defaultInk    {CYAN};
constexpr uint16_t reticleColour {DEEPGREY};

/*
  Timer 1 is the 16 bit timer so this is also used for the "in-app" RTC so be careful!
  Consult the ISR below for further notes 
  for exaxmple, for Timer 1 to fire every 4 seconds
  (Adjust this if your board has a different speed!

  x = 65535 - (16Mhz * 4/1024)
  therefore x = 3035.
  https://oscarliang.com/arduino-timer-and-interrupt-tutorial/
*/

constexpr uint16_t UPDATER {49910};  // one second timer. 

// Active semaphores
enum semaphores : uint16_t
{
  FROST       = 0x0001, 
  DAMP        = 0x0002, 
  DRY         = 0x0004, 
  OVERTEMP    = 0x0008,
  FLASH       = 0x0010,
  WARNDANGER  = 0x0020,
  USEMETRIC   = 0x0040,
  UPDATEREADS = 0x0080,
  REDRAWGRAPH = 0x0100,
  CLEARFROST  = 0x0200,
  CLEARDRY    = 0x0400,
  CLEARHOT    = 0x0800,
  CLEARDAMP   = 0x1000,
  UPDATEGRAPH = 0x2000,
  RESERVED1   = 0x4000,
  RESERVED2   = 0x8000,
  RESETALL    = 0xFFFF
};

constexpr uint16_t B0000000000000001 {0x0001};
constexpr uint16_t B0000000000000010 {0x0002};
constexpr uint16_t B0000000000000100 {0x0004};
constexpr uint16_t B0000000000001000 {0x0008};
constexpr uint16_t B0000000000010000 {0x0010};
constexpr uint16_t B0000000000100000 {0x0020};
constexpr uint16_t B0000000001000000 {0x0040};
constexpr uint16_t B0000000010000000 {0x0080};
constexpr uint16_t B0000000100000000 {0x0100};
constexpr uint16_t B0000001000000000 {0x0200};
constexpr uint16_t B0000010000000000 {0x0400};
constexpr uint16_t B0000100000000000 {0x0800};
constexpr uint16_t B0001000000000000 {0x1000};
constexpr uint16_t B0010000000000000 {0x2000};
constexpr uint16_t B0100000000000000 {0x4000};
constexpr uint16_t B1000000000000000 {0x8000};

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

/* 
* This is 0 - 90 degrees of arc in quadrant 1
* Flip the sign to get the relative quadrant data.
*/

const uint16_t sinTable [] PROGMEM = 
{
0, 572, 1144, 1715, 2286, 2856, 3425, 3993, 4560, 5126, 5690, 6252, 6813, 
7371, 7927, 8481, 9032, 9580, 10126, 10668, 11207, 11743, 12275, 12803, 13328, 
13848, 14365, 14876, 15384, 15886, 16384, 16877, 17364, 17847, 18324, 18795, 
19261, 19720, 20174, 20622, 21063, 21498, 21926, 22348, 22763, 23170, 23571, 
23965, 24351, 24730, 25102, 25466, 25822, 26170, 26510, 26842, 27166, 27482, 
27789, 28088, 28378, 28660, 28932, 29197, 29452, 29698, 29935, 30163, 30382, 
30592, 30792, 30983, 31164, 31336, 31499, 31651, 31795, 31928, 32052, 32166, 
32270, 32365, 32449, 32524, 32588, 32643, 32688, 32723, 32748, 32763, 32767
};

const unsigned char symbolDry [] PROGMEM = {
0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 
0xe3, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xc9, 0xff, 0xf7, 0xff, 0xff, 0xc9, 
0xff, 0xe3, 0xff, 0xff, 0x9c, 0xff, 0xc1, 0xff, 0xff, 0x9c, 0xff, 0x80, 0xff, 0xff, 0x3e, 0x7f, 
0xb4, 0xff, 0xff, 0x3e, 0x7f, 0xe7, 0xff, 0xfe, 0x7f, 0x3f, 0xe7, 0xff, 0xfe, 0x7f, 0x3f, 0xe7, 
0x8f, 0xfc, 0xff, 0x9f, 0xcf, 0x07, 0xf8, 0xff, 0x9f, 0x1e, 0x03, 0xf9, 0xff, 0xfc, 0x3e, 0x41, 
0xf3, 0xff, 0xf0, 0xff, 0xdb, 0xe3, 0xff, 0x83, 0xff, 0x9f, 0xe7, 0xfe, 0x03, 0xff, 0x9f, 0xcf, 
0xf8, 0x79, 0xff, 0x1f, 0xcf, 0xf1, 0xf9, 0xfe, 0x3f, 0x9f, 0xe3, 0xff, 0xf8, 0x7f, 0x9f, 0xcf, 
0xff, 0xe1, 0xff, 0xbf, 0xcf, 0xff, 0x07, 0xff, 0x3f, 0x9f, 0xfc, 0x1f, 0xff, 0x3f, 0x9f, 0xf0, 
0x7f, 0xff, 0x3f, 0x9f, 0xc2, 0x7f, 0xff, 0x3f, 0xff, 0x8e, 0x7f, 0xff, 0x3f, 0xff, 0x1e, 0x7f, 
0xff, 0x3f, 0xff, 0x3e, 0x7f, 0xff, 0x3f, 0xff, 0x7e, 0xff, 0xff, 0xbf, 0xfe, 0x7c, 0xff, 0xff, 
0x9f, 0xfe, 0x7c, 0xff, 0xff, 0xcf, 0xff, 0xf9, 0xff, 0xff, 0xcf, 0xff, 0xf9, 0xff, 0xff, 0xe7, 
0xff, 0xf3, 0xff, 0xff, 0xf3, 0xff, 0xc7, 0xff, 0xff, 0xf8, 0xff, 0x0f, 0xff, 0xff, 0xfe, 0x00,
};

const unsigned char symbolIce [] PROGMEM = {
/*
0xff, 0xfe, 0xff, 0x7f, 0xff, 0xff, 0xfc, 0x7e, 0x3f, 0xff, 0xff, 0xfe, 0x3c, 0x7f, 0xff, 0xff, 
0xff, 0x18, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0x8f, 0xc3, 0xf1, 0xff, 0xff, 0x8f, 
0xe7, 0xf1, 0xff, 0xff, 0x8f, 0xe7, 0xf1, 0xff, 0xff, 0x8f, 0xe7, 0xf1, 0xff, 0xf8, 0x0f, 0xe7, 
0xf0, 0x1f, 0xf8, 0x0f, 0xe7, 0xf0, 0x1f, 0xf8, 0x07, 0xe7, 0xe0, 0x1f, 0xff, 0xe3, 0xe7, 0xc7, 
0xff, 0xff, 0xf1, 0xe7, 0x8f, 0xff, 0xbf, 0xf8, 0xe7, 0x1f, 0xfd, 0x1f, 0xfc, 0x66, 0x3f, 0xf8, 
0x8f, 0xfe, 0x24, 0x7f, 0xf1, 0xc7, 0xff, 0x00, 0xff, 0xe3, 0xe3, 0xff, 0x81, 0xff, 0xc7, 0xf0, 
0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xe3, 0xff, 0x81, 0xff, 0xc7, 0xc7, 0xff, 
0x00, 0xff, 0xe3, 0x8f, 0xfe, 0x24, 0x7f, 0xf1, 0x1f, 0xfc, 0x66, 0x3f, 0xf8, 0xbf, 0xf8, 0xe7, 
0x1f, 0xfd, 0xff, 0xf1, 0xe7, 0x8f, 0xff, 0xff, 0xe3, 0xe7, 0xc7, 0xff, 0xf8, 0x07, 0xe7, 0xe0, 
0x1f, 0xf8, 0x0f, 0xe7, 0xf0, 0x1f, 0xf8, 0x0f, 0xe7, 0xf0, 0x1f, 0xff, 0x8f, 0xe7, 0xf1, 0xff, 
0xff, 0x8f, 0xe7, 0xf1, 0xff, 0xff, 0x8f, 0xe7, 0xf1, 0xff, 0xff, 0x8f, 0xc3, 0xf1, 0xff, 0xff, 
0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0x18, 0xff, 0xff, 0xff, 0xfe, 0x3c, 0x7f, 0xff, 0xff, 0xfc, 
0x7e, 0x3f, 0xff, 0xff, 0xfe, 0xff, 0x7f, 0xff*/
};

const unsigned char symbolHot [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0x80, 0xff, 0x9f, 0xfc, 0x7e, 0x7f, 0x7f, 0x1f, 0xfe, 
0x3e, 0xff, 0xbe, 0x3f, 0xff, 0x1d, 0xff, 0xbc, 0x7f, 0xff, 0x8d, 0xff, 0xf8, 0xff, 0xff, 0xcd, 
0xff, 0xf1, 0xff, 0xff, 0xed, 0xff, 0xfb, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x39, 
0xff, 0xff, 0xff, 0xfc, 0x3a, 0xbf, 0xff, 0xff, 0xfc, 0xdb, 0x3f, 0xff, 0xff, 0xff, 0xd7, 0xff, 
0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0x00, 
0x00, 0x7f, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x39, 0xff, 0xff, 0xff, 
0xfe, 0x3a, 0xff, 0xff, 0xff, 0xfe, 0xdb, 0x7f, 0xff, 0xff, 0xfd, 0xd7, 0xbf, 0xff, 0xff, 0xfd, 
0xe7, 0xbf, 0xff, 0xff, 0xcd, 0xe7, 0xf3, 0xff, 0xff, 0x8d, 0xff, 0xf1, 0xff, 0xff, 0x0d, 0xff, 
0xf0, 0xff, 0xfe, 0x3d, 0xe7, 0xf8, 0x7f, 0xfc, 0x3d, 0xe7, 0xfc, 0x3f, 0xfc, 0xfd, 0xe7, 0xfe, 
0x3f, 0xff, 0xfd, 0xe7, 0xff, 0xbf, 0xff, 0xfd, 0xe7, 0xff, 0xff, 0xff, 0xfd, 0xe7, 0xff, 0xff, 
0xff, 0xfd, 0xe7, 0xff, 0xff, 0xff, 0xfd, 0xe7, 0xff, 0xff, 0xff, 0xfd, 0xe7, 0xff, 0xff, 0xff, 
0xfd, 0xe7, 0xff, 0xff, 0xff, 0xfd, 0xe7, 0xff, 0xff, 0xff, 0xfd, 0xe7, 0xff, 0xff, 0xff, 0xfd, 
0xe7, 0xff, 0xff, 0xff, 0xf9, 0xe7, 0xdf, 0xff, 0xff, 0xfb, 0xe7, 0xcf, 0xff, 0xff, 0xf7, 0xe3, 
0xef, 0xff, 0xff, 0xf7, 0x81, 0xf7, 0xff, 0xff, 0xf7, 0x9c, 0xf7, 0xff, 0xff, 0xe7, 0x3c, 0xf7, 
0xff, 0xff, 0xf7, 0x3c, 0xf7, 0xff, 0xff, 0xf7, 0x9c, 0xf7, 0xff, 0xff, 0xf7, 0x80, 0xe7, 0xff, 
0xff, 0xf3, 0xc3, 0xef, 0xff, 0xff, 0xf9, 0xff, 0xdf, 0xff, 0xff, 0xfc, 0xff, 0x9f, 0xff, 0xff, 
0xfe, 0x3e, 0x7f, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const unsigned char symbolDamp [] PROGMEM = {
0xfd, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xe0, 
0x7f, 0xff, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x1f, 
0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0x9f, 0x80, 0x0f, 0xff, 
0xff, 0x1f, 0x00, 0x0f, 0xff, 0xff, 0x0f, 0x00, 0x0f, 0xff, 0xfe, 0x07, 0x00, 0x0f, 0xff, 0xfe, 
0x07, 0x00, 0x0f, 0xff, 0xfc, 0x03, 0x80, 0x0f, 0xff, 0xf8, 0x03, 0x80, 0x1f, 0xff, 0xf8, 0x01, 
0x80, 0x1f, 0xff, 0xf8, 0x01, 0xe0, 0x7f, 0xff, 0xf0, 0x01, 0xf9, 0xff, 0xff, 0xf0, 0x00, 0xff, 
0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 
0x3f, 0xf0, 0x01, 0xff, 0xfe, 0x1f, 0xf8, 0x01, 0xff, 0xfe, 0x1f, 0xf8, 0x03, 0xff, 0xfc, 0x0f, 
0xfe, 0x0f, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x07, 0xff, 
0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 
0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 
0xe0, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xf8, 
0x07, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff
};
#endif