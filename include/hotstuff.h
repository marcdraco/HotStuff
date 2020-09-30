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

#ifndef __HOTSTUFF_H
#define __HOTSTUFF_H

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

#define SHOW_BANDS            // optionally plot some dotted lines for normal values
#define BUTTON_PIN 10         // the acknowlegement button to stop alerts for ice, damp etc.
#define DHT22_POWER 11        // pin to power the DHT22 since the power pins are covered.
#define DHT22_DATA 12         // The DHT 22 can be powered elsewhere leaving this free however.
#define ALARM_PIN 13          // LED or a high-impedance buzzer
#define GRAPH_WIDTH 240       // The absolute width of the graph where used
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

#define UPDATER 49910  // one second timer. 


// use this if you have an incident like someone did...
#define SENSOR_MISSING_OR_BUSTED  

 // You have a dirty mind! This for the i2C version!
 //#define TOPLESS                

// remove this line to have the unit read in fahrenheit
#define METRIC                   
 
// This is for the experimental analog display
//#define CLOCKWISE

uint16_t err = 0;

struct 
{
  enum messages {c, f, percent, slash, damp, dry, 
  frost, uptime, temperature, humidity, temperatureScale, 
  humidityScale, work1, work2, caution, xcaution, danger, xdanger};

  const char * msg[18] = {
    "C", "F", "%", "/", 
    "DAMP", "DRY", "FROST", "Uptime: ", 
    "Air Temp:", "Humidity:", "Temperature in ", 
    "Relative Humidity", "High temp & humidity!", "Temp Equivalent: ", 
    "Caution", "Extreme Caution", "DANGER", "-DANGER TO LIFE-"};
} messages;

struct {
  volatile uint8_t timeInSeconds = 0;
  volatile uint8_t timeInMinutes = 0;
  volatile uint8_t timeInHours   = 0;
  volatile uint8_t timeInDays    = 0;
  volatile uint8_t timeInWeeks   = 0;
  volatile uint8_t timeInYears   = 0;
  volatile uint8_t timeToRead    = 0;
} isrTimings;

struct {
  const uint8_t errorY     = 230  / HEIGHT_SCALE;
  const uint16_t width     = 320  / WIDTH_SCALE; 
  const uint8_t height     = 240  / HEIGHT_SCALE;
  uint8_t graphX           = 0;      // the current plot position
  uint8_t lastTemperatureY = 0;
  uint8_t lastHumidityY    = 0;
  bool flashing            = false;
  bool warnDanger          = false;
  bool graphActive         = true;
  enum {
    rotatePortrait = 0, 
    rotateDefault = 1};     // Use 0 and 1 for or 2 and 3 depending on how you want your screen displayed
} tft;

/*
  Bit of tricky programming for beginners, these "flags" are set as bits in a single byte.
  When any one is set, that means the device is in an "alarm" condition. Hence all the alarms
  can be tested in one go but set/cleared without affecting any of the others. Flags are
  called semaphores here - they're synonymous.

  This gives us an easy way to set a bunch of conditions that might switch on and
  off at any time but the alarm beacon isn't cancelled by a single one going green.
  Note that the enumeration is a binary sequence: 1, 2, 4, 8, 16, 32 etc.
  16 or even 32 bits are possible but that would be exceptional in such limited space.

  This takes slightly longer than a simple true/false bool so we uses those where practical
*/
struct {
  enum     
  {
    frost    = 1, 
    damp     = 2, 
    dry      = 4, 
    overTemp = 8, 
    all =    0xFF
  };

  uint8_t  semaphore       = 0;
  bool     silenced        = false;
  bool     alarmedDryAir   = false;
  bool     alarmedDampAir  = false;
  bool     alarmedLowTemp  = false;
  bool     alarmedHighTemp = false; 
  bool     highRisk        = false;
} alarm;

// a couple of variables to determine the button multi-functions.
struct {
  bool          pressed    = false;
  uint8_t       timer      = 0;
  uint8_t       lastTimer  = 0;
  const uint8_t shortPress = 2;
  const uint8_t longPress  = 10;

} button;

// The failure record array gets sensor age after a "catastrophic" failure
struct {
  bool sensorFailure = false;
  enum {Y = 0, W, D, H, M};
  uint8_t failTime[5] = {0, 0, 0, 0, 0};
} fail;

/*
   The following constants set up various values to calculate the graphing functions and should
   be fairly self-explanatory. As set here, the chart covers temperatures from 0 to 50C
   and RH (humidity.reading) across the whole range. The DHT22 is good for -40 to 80C but this
   device is for humans at work or elderly so is set for those temperature ranges.
   Compare the DHT22 information sheet for complete specifications.
*/

struct
{
  struct
  {
    const uint16_t defaultBackground = BLACK;
    const uint16_t defaultForeground = CYAN;
    const uint16_t reticleColour     = DEEPGREY;
  } colour;

  const uint8_t  bigReadXTemp    = 10  / WIDTH_SCALE;
  const uint8_t  bigReadXHumid   = 140 / WIDTH_SCALE;
  const uint16_t degreeX         = 280 / WIDTH_SCALE;
  const uint16_t degreeSymbolX   = 280 / WIDTH_SCALE;
  const uint8_t  dryWarnX        = 180  / WIDTH_SCALE;
  const uint8_t  dampWarnX       = 228  / WIDTH_SCALE;
  const uint8_t  frostWarnX      = 42  / WIDTH_SCALE;
  const uint8_t  lowHumidX       = 176 / WIDTH_SCALE;
  const uint8_t  lowTempX        = 42  / WIDTH_SCALE;
  const uint8_t  leftMargin      = 20  / WIDTH_SCALE;
  const uint8_t  leftAxisLabel   = 5   / WIDTH_SCALE;
  const uint16_t rhpc            = 295 / WIDTH_SCALE;
  const uint16_t scaleX          = 295 / WIDTH_SCALE;
  
  const uint16_t axisYPosition   = 30  / HEIGHT_SCALE;
  const uint8_t  degreeSymbolY   = 8   / HEIGHT_SCALE;
  const uint8_t  BigReadY        = 5  / HEIGHT_SCALE;
  const uint8_t  degreeY         = 8   / HEIGHT_SCALE;
  const uint8_t  dryWarnY        = 80  / HEIGHT_SCALE;
  const uint8_t  frostWarnY      = 80  / HEIGHT_SCALE;
  const uint8_t  temperatureY    = 74  / HEIGHT_SCALE;
  const uint8_t  humidityY       = 74  / HEIGHT_SCALE;
  const uint8_t  heatIndexY      = 110 / HEIGHT_SCALE;
  const uint8_t  lowTempY        = 60  / HEIGHT_SCALE;
  const uint8_t  lowHumidY       = 60  / HEIGHT_SCALE;
  const uint8_t  dampWarnY       = 80  / HEIGHT_SCALE;
  const uint8_t  uptimeTimeY     = 228 / HEIGHT_SCALE;
  const uint8_t  baseHeight      = 8;
  const uint8_t  baseWidth       = 6;
  enum {small  = 1,                       // 6 x 8 
        medium = 2,                       // 12 x 16
        large  = 3,                       // 18 x 24
        huge   = 4,                       // 24 x 32
        enormous = 5,                     // 30 x 40
        humungous = 6                     // 36 x 48
       };
} text;

struct {
  const uint16_t tRadialX    = 160  / WIDTH_SCALE;
  const uint16_t tRadialY    = 120 / HEIGHT_SCALE;
  const uint16_t hRadial     = +1160 / HEIGHT_SCALE;
  const uint16_t innerRadius = 40 / WIDTH_SCALE;
  const uint16_t outerRadius = 70 / WIDTH_SCALE;

} radials;

struct
{
  const uint8_t FSD    = 100  / HEIGHT_SCALE; 
  const uint8_t X      = 41   / WIDTH_SCALE;
  const uint8_t Y      = 110  / HEIGHT_SCALE;
  const uint8_t width  = 240  / WIDTH_SCALE;
  const uint8_t height = 100  / HEIGHT_SCALE;
  const uint16_t reticleColour = DEEPGREY;
  bool updateGraphReadings = true;
} graph;

struct
{
  const uint8_t  minComfort            = 45;      // the minium humidity.reading considered "normal" < 40% RH can trigger dry skin, etc.
  const uint8_t  maxComfort            = 55;      // the maxium humidity.reading considered "normal" > 60% RH, moulds and other pests get going.
  const uint8_t  guard                 = 5;       // the guard zone values +- the normal min/max start to set up more alerts
  const uint16_t trace                 = AZURE;   // humidity graph line
  float          lowestReading         = 101;
  float          highestReading        = 0;
  float          reading               = 0;
  float          previousRead          = -1;
  uint16_t       cmaCounter            = 0;
  float          cumulativeMovingAverage = 50;
  float          mean                  = 0;
  uint8_t        readingY              = 0;
  uint8_t        Y                     = 0;
  uint8_t pipe[GRAPH_WIDTH];
  const float correction               = 0;     // % correction if the RH is off
  const float    dampAirWatershed      = 60;
  const float    dryAirWatershed       = 40;
} humidity;

struct
{
  uint16_t trace                = YELLOW;   // temperature graph line
  const uint8_t caution         = 32;       // Three watermarks (32,41,54)
  const uint8_t warning         = 41;       // per Steadman "safe" for working temperatures
  const uint8_t risk            = 54;       // Above 54c is very bad
  const uint8_t minComfort      = 20;      // the minium temperature considered "normal"
  const uint8_t maxComfort      = 22;      // the maxium temperature considered "normal"
  const uint8_t guard           = 5;       // the guard zone values +- the comfort min/max start to set up more alerts
  float highestReading          = 0;
  float lowestReading           = 99;
  float previousRead            = 0.0;
  float reading                 = -1;
  uint16_t cmaCounter           = 0;
  float cumulativeMovingAverage = 25;
  float mean                    = 0;
  uint8_t readingY              = 0;
  uint8_t Y                     = 0;
  uint8_t pipe[GRAPH_WIDTH];
  const float correction        = 0;    // centigrade correction if the temp is off
  int validRead                 = 0;
  const float frostWatershed    = 4.0;   // ice can appear/persist around this temp
#ifdef METRIC
  bool     useMetric            = true;
#else
  bool     useMetric            = false;
#endif
} temperature;

MCUFRIEND_kbv screen;
UniversalDHT dht22(DHT22_DATA);
#endif