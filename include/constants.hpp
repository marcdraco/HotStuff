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
constexpr int WIDTH_SCALE    {1};       // divide the size of the screen based on a 320x240 matrix
constexpr int HEIGHT_SCALE   {1};       // divide the size of the screen based on a 320x240 matrix
constexpr int TEXTLARGE      {3};
constexpr int TEXTSMALL      {1};

constexpr int BASEWIDTH      {6};
constexpr int BASEHEIGHT     {8};

constexpr int DRY_WARN_X     {228 / WIDTH_SCALE};
constexpr int DAMP_WARN_X    {228 / WIDTH_SCALE};
constexpr int FROSTWARN_X    {228 / WIDTH_SCALE};

constexpr int LEFTMARGIN     {20 / WIDTH_SCALE};
constexpr int LEFTAXISLABEL  {5 / WIDTH_SCALE};

constexpr int BIGREAD_Y      {60 / HEIGHT_SCALE};
constexpr int DRY_WARN_Y     {80 / HEIGHT_SCALE};
constexpr int FROSTWARN_Y    {80 / HEIGHT_SCALE};

constexpr int HEATINDEX_Y    {120 / HEIGHT_SCALE};
constexpr int LOW_TEMP_X      {42 / WIDTH_SCALE};
constexpr int LOW_TEMP_Y      {100 / HEIGHT_SCALE};
constexpr int HIGHTEMP_y     {LOW_TEMP_Y};
constexpr int LOWHUMID_Y     {LOW_TEMP_Y};
constexpr int HIGHHUMID_Y    {LOW_TEMP_Y};
constexpr int DAMP_WARN_Y     {80  / HEIGHT_SCALE};
constexpr int UPTIME_Y       {228 / HEIGHT_SCALE};
constexpr int AXIS_Y_POSITION {30  / HEIGHT_SCALE};
constexpr int TRADIAL_X      {160 / WIDTH_SCALE};
constexpr int TRADIAL_Y      {120 / HEIGHT_SCALE};
constexpr int HRADIAL        {160 / HEIGHT_SCALE};
constexpr int INNER_RADIUS   {40  / WIDTH_SCALE};
constexpr int OUTER_RADIUS   {70  / WIDTH_SCALE};
constexpr int FSD            {100 / HEIGHT_SCALE};
constexpr int TFT_ERROR_Y    {234 / HEIGHT_SCALE};
constexpr int TFT_WIDTH      {320 / WIDTH_SCALE};
constexpr int TFT_HEIGHT     {240 / HEIGHT_SCALE};
constexpr int HEIGHT         {100 / HEIGHT_SCALE};
constexpr int GRAPH_Y        {110 / HEIGHT_SCALE};
constexpr int GRAPH_WIDTH    {180};

//constexpr int FONT_BUFF_WIDTH    {100}; // special "offscreen" buffer for deleting and pre-rendering fonts
//constexpr int FONT_BUFF_HEIGHT   {50};

constexpr int FONT_BUFF_WIDTH    {60}; // special "offscreen" buffer for deleting and pre-rendering fonts
constexpr int FONT_BUFF_HEIGHT   {50};


constexpr int CAUTION        {32};     // Three watermarks (32,41,54)
constexpr int WARNING        {41};     // per Steadman "safe" for working temperatures
constexpr int RISK           {54};     // Above 54c is very bad
constexpr float FROST_WATERSHED {4.0}; // ice can appear/persist around this temp
constexpr int SHORTPRESS     {2};
constexpr int LONGPRESS      {10};

constexpr float MIN_COMFORT_TEMP  {20.0};      // the minium temperature considered "normal"
constexpr float MAX_COMFORT_TEMP  {22.0};     // the maxium temperature considered "normal"
constexpr float GUARD_TEMP        {2.0};      // the guard zone values +- the comfort min/max start to set up more alerts

constexpr float MIN_COMFORT_HUMID {40.0};      // the minium temperature considered "normal"
constexpr float MAX_COMFORT_HUMID {60.0};      // the maxium temperature considered "normal"
constexpr float GUARD_HUMID       {2.0};      // the guard zone values +- the comfort min/max start to set up more alerts

constexpr float DAMP_AIR_WATERSHED {MIN_COMFORT_HUMID - GUARD_HUMID};
constexpr float DRY_AIR_WATERSHED  {MAX_COMFORT_HUMID + GUARD_HUMID};

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
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)
#define BROWNISH  RGB(0x2e,0x2d,0x0)
#define PURPLEISH RGB(0x2f,0x00,0x2d)

constexpr auto BLACK    {0x0000};
constexpr auto BLUE     {0x001F};
constexpr auto RED      {0xF800};
constexpr auto GREEN    {0x07E0};
constexpr auto CYAN     {0x07FF};
constexpr auto MAGENTA  {0xF81F};
constexpr auto YELLOW   {0xFFE0};
constexpr auto WHITE    {0xFFFF};

constexpr auto defaultPaper  {BLACK};
constexpr auto defaultInk    {CYAN};
constexpr auto reticleColour {DEEPGREY};

constexpr auto LOW_LIMIT_EXCEEDED {BLUE};
constexpr auto HIGH_LIMIT_EXCEEDED {RED};

/*
  Timer 1 is the 16 bit timer so this is also used for the "in-app" RTC so be careful!
  Consult the ISR below for further notes Timer 1 to fire every 4 seconds
  Adjust this if your board has a different speed!

  x = 65535 - (16Mhz * 4/1024)
  therefore x = 3035.
  https://oscarliang.com/arduino-timer-and-interrupt-tutorial/
*/

constexpr auto UPDATER {49910};  // one second timer. 


// Active semaphores
enum semaphores : uint16_t
{
  FROST       = 0x0001, 
  DAMP        = 0x0002, 
  DRY         = 0x0004, 
  OVERTEMP    = 0x0008,
  FLASHING    = 0x0010,
  WARNDANGER  = 0x0020,
  GRAPHACTIVE = 0x0040,
  ALARMDRY    = 0x0080,
  ALARMFROST  = 0x0100,
  ALARMDAMP   = 0x0200,
  USEMETRIC   = 0x0400,
  UPDATEREADS = 0x0800,
  SENSORFAIL  = 0x1000,
  RESETALL    = 0xFFFF
};

// non-active semaphores used for function arguments}
enum  
{
  FLOATS      = B00000001,
  METRIC      = B00000010,
  TEMPERATURE = B00000100
};


#endif