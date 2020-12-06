/*
  +++++----------------------------------------------------------------------+++++

  Copyright 2020, Marc Draco with Garrie "Garrington" Steele & Daniel Melvin
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
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
  DAMAGE.

  +++++++++++++++++++++++++++ PROGRAMMER'S NOTES ++++++++++++++++++++++++++++++++++
  <nag mode>
  BEAUTIFUL CODE IS ELEGANT, CAREFULLY COMMENTED AND AIRY. ALL THAT FREE SPACE 
  MAKES IT EASIER FOR EVERYONE. YOUR CODE ISN'T GOING TO CATCH COVID AND DEVELOP
  PNEUMONIA BECAUSE YOU USED A FEW EXTRA SPACES!

  THERE ARE NO BUGS IN THIS CODE, JUST FEATURES, SOME OF WHICH MAY CAUSE IT TO 
  BEHAVE ERRATICALLY. SINCE YOU GOT IT FOR FREE, FIX THEM OR DON'T COME CRYING TO
  US!
  
  YES, IT'S WORDY AND WE'VE ESCHEWED MANY C "SHORTCUTS" TO MAKE IT EASIER FOR 
  BEGINNERS. REMEMBER, WE'RE NOT WORKING ON TELETYPES AND MANY SHORTCUTS LEAD TO 
  OBFUSCATED CODE THAT IS HARD TO READ AND EVEN MORE DIFFICULT TO DEBUG. IF 
  YOU'RNOT TYPING THIS BY HAND YOURSELF, YOU DON'T HAVE TO WORRY ABOUT THE 
  ALLMAN/BSD STYLE.

  YES, WE KNOW WHAT K&R SAYS BUT K&R WAS WRITTEN FOR TELETYPES. YOU'RE NOT WORKING 
  ON A TELETYPE. AND WE KNOW WHAT THE LINUX KERNEL STYLE GUIDE SAYS TOO. SAME 
  POINT. EVERY BYTE SAVED IS PRECIOUS WHEN YOU HAVE TO TYPE EVERY LETTER WITH A 
  SMALL HAMMER AND WAIT AN AGE WHILE THE 300 BAUD SERIAL LINE COUGHS BACK AN ACK.
  BUT THOSE DAYS ARE GONE AND WE ALL NEED TO MOVE WITH THE TIMES. INDENTATION AND
  CLEARLY MARKED SCOPE IS THE FUTURE.
  
  ENCLOSE EVERYTHING IN BRACES AND MAKE SURE IT'S INDENTED CORRECTLY. JUST BECAUSE 
  C/C++ ALLOWS YOU TO LEAVE OUT ENCLOSING BRACES, DOESN'T MEAN YOU *SHOULD* LEAVE THEM 
  OUT BECAUSE THAT SORT OF THING ONLY LEADS TO ACCIDENTAL LINE INSERTIONS THAT 
  DON'T WORK AS INTENDED. C++ USED HERE FOR ORGANIZATIONAL PURPOSES AND TO MAKE THE
  CODE EASIER TO MAINTAIN/EXPAND. C WOULD HAVE BEEN MARGINALLY MORE EFFICIENT HOWEVER.

  * THE TARGET MCUs ARE 8-BIT. FOR THIS REASON WE ONLY USE 16, 32 OR LARGER VARIABLES 
  WHEN IT'S NOT POSSIBLE TO FIT EVERYTHING INTO 8BITS. THE USUAL WISDOM OF USING SIGNED
  INTS BECUASE "BETTER" THAN UNSIGNED, IS ESCHEWED BY MICROCHIP FOR PERFORMANCE REASONS

  * SIGNED ARITHMETIC IS SLIGHTLY MORE COMPLEX THAN UNSIGNED SO WE PREFER UNSIGNED WHERE
  THAT IS POSSIBLE.

  * IT'S CHEAPER (AT THE ASSEMBLY LEVEL) TO COUNT DOWN TO ZERO RATHER THAN UP TO A VALUE
  SO WHERE PERFORMANCE IS REQUIRED WE'VE STARTED TO TRANSITION TO THE SLIGHTLY LONGER
  BUT MORE PERFORMANT COUNT DOWNS UNLESS THERE IS A GOOD REASON NOT TO DO THIS. SOME OLDER
  CODE HERE MIGHT NOT HAVE MADE THIS TRANSITION (YET) AS WE ONLY FOUND THE APPLICATION NOTE
  LATE INTO DEVELOPMENT.
  
  * YOU MIGHT THINK YOURSELF CLEVER, BUT BET YOUR BUTT THE COMPILER IS SMARTER AND CAN
  SEE THINGS YOU NEVER EVEN THOUGHT POSSIBLE SO MAKE IT EASIER FOR EVERYONE AND BE 
  AS EXPLICIT AS YOU POSSIBLY CAN, BUT NO MORE EXPLICT THAN THE PROGRAM REQUIRES.

  BY THE TIME YOU RECEIVE THIS, THERE SHOULD NOT BE ANY COMPILER WARNINGS UNLESS
  NEW ONES HAVE BEEN INTRODUCED SINCE WE LAST TOO A DEEP DIVE AND HIT MAKE.
  WARNINGS MIGHT NOT BE ERRORS (THEY DON'T STOP THINGS RUNNING) BUT THAT DOESN'T 
  MEAN THAT THEY CAN BE IGNORED. WASTED VARIABLES, WASTED DECLARATIONS AND SO ON
  MEAN WASTED MEMORY AND AIN'T NO ONE GOT TIME FOR THAT.
  </nag mode>

  Thanks to Steve Wood (ebay: audioSpectrumAnalysers) for the serial programmer.
  3.5" TFT shield supplied by A-Z Delivery via Amazon
  Clone UNO by Elegoo based on a design by Arduino  

@file
@brief Main code
*/


#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <Wire.h>

#include <Adafruit_GFX.h>     // Core graphics library by AdaFruit
#include <MCUFRIEND_kbv.h>    // David Prentice's Hardware-specific library - your shield might vary
#include "UniversalDHT.h"   // @winlinvip's DHT11/22 library functions modified by Tim Harper

#include "Alarm.h"
#include "Display.h"
#include "Environmental.h"
#include "Fonts.h"
#include "Graph.h"
#include "hotstuff_fonts.h"
#include "hotstuff.h"
#include "Messages.h"
#include "Reading.h"
#include "Sevensegments.h"
#include "Trig.h"
#include "types.h"

MCUFRIEND_kbv screen;
Display display;
UniversalDHT dht22(DHT22_DATA);
Graph graph;
Reading humidity;
Reading temperature;
Fonts fonts;
Environmental environment;
Messages messages;
Sevensegments segments(defaultInk);

// convert KNOWN Y coords to 8-bit only for a hair more speed.

// start working on a version for i2C displays with 128 x 240 etc. screens... both XY are 8-bit

/// chart update counter should count CHART updates, not CMA updates!
/// CMA counter doesn't work with the bloody 8-10 minute update, stupid!

globalVariables globals;

/**
 * @brief classic Arduino setups
 *  
 */

void setup()
{
  const int DHT22_POWER {11};      // pin to power the DHT22 since the power pins are covered.
  const int DHT22_DATA  {12};      // The DHT 22 can be powered elsewhere leaving this free however.
  uint16_t ID{screen.readID()};

  if (ID == 0xD3D3)
  {
    ID = 0x9481; //force ID if write-only screen
  }
  screen.begin(ID);
  humidity.setTrace(AZURE);       // humidity graph line
  temperature.setTrace(YELLOW);   // temperature graph line
  fonts.setFont(static_cast<const gfxfont_t *>(&HOTSMALL));

#ifdef USE_METRIC
  SETBIT(globals.gp, USEMETRIC);
  temperature.goMetric();
#else
  temperature.goImperial();
#endif

  noInterrupts();                       // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = UPDATER;                      // pre-calculated re-read time.
  TCCR1B |= (1 << CS10) | (1 << CS12);  // 1024 prescaler (see header)
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  interrupts();                         // enable all interrupts

  screen.setRotation(display.rotateLandscapeSouth); // possible values 0-3 for 0, 90, 180 and 270 degrees rotation
  screen.fillScreen(defaultPaper);

  pinMode(DHT22_POWER, OUTPUT);       // cheeky way to power the DHT22, but it only requires 1.5mA
  digitalWrite(DHT22_POWER, HIGH);    // and saves wiring from the ICSP ports on UNO with a TFT shield
  pinMode(DHT22_DATA, INPUT_PULLUP);  // keep the data pin from just hanging around

  readings_t read;
  
  delay(3000);
  dht22.read(&read.H, &read.T);
  temperature.initReads(read.T);
  humidity.initReads(read.H);
  #ifdef USE_GRAPH
  graph.drawGraph();
  #endif
}

/**
 * @brief Classic Arduino loop
 * 
 */

void loop()
{
  if (CHECKBIT(globals.ISR,  UPDATEREADS))
  {    
    CLEARBIT(globals.ISR,  UPDATEREADS);
    Reading::takeReadings();
    messages.showMinMax();
  }
//graph.drawRadials();

showLCDReadsHorizontal();

#ifdef USE_GRAPH
  if (CHECKBIT(globals.ISR,  UPDATEGRAPH))
  {
    CLEARBIT(globals.ISR,  UPDATEGRAPH);
    graph.drawGraph();
  }
#endif


/**
 * @brief Following here are the annunciators
 * 
 */

  (CHECKBIT(globals.ISR,  FLASH)) ? display.setFlashInk(defaultInk) : display.setFlashInk(defaultPaper);

  if (CHECKBIT(globals.ISR,  CLEARFROST | CLEARDAMP | CLEARDRY | CLEARHOT))
  {
    if (CHECKBIT(globals.ISR,  CLEARDRY))
    {
      CLEARBIT(globals.ISR,  CLEARDRY);
      display.setFlashInk(defaultPaper);
      display.displaySmallBitmap(SYMX2, SYMY, 40, 40, (uint8_t *) symbolDry);
    }

    if (CHECKBIT(globals.ISR,  CLEARDAMP))
    {
      CLEARBIT(globals.ISR,  CLEARDAMP);
      display.setFlashInk(defaultPaper);
      display.displaySmallBitmap(SYMX2, SYMY, 40, 40, (uint8_t *) symbolDamp);
    }

  #ifdef INCUBATOR
    if (CHECKBIT(globals.ISR,  CLEARFROST))
    {
      CLEARBIT(globals.ISR,  CLEARFROST);
      display.setFlashInk(defaultPaper);
      display.displaySmallBitmap(SYMX1, SYMY, 40, 40, (uint8_t *) symbolIce);
    }

    if (CHECKBIT(globals.ISR,  CLEARHOT))
    {
      CLEARBIT(globals.ISR,  CLEARHOT);
      display.setFlashInk(defaultPaper);
      display.displaySmallBitmap(SYMX1, SYMY, 40, 40, (uint8_t *) symbolHot);
    }
  #endif
  } 

  if (CHECKBIT(globals.ISR,  FROST | DAMP | DRY | OVERTEMP))     
  {
    if (CHECKBIT(globals.ISR,  DAMP))
    {
      display.displaySmallBitmap(SYMX2, SYMY, 40, 40, (uint8_t *) symbolDamp);
    }

    if (CHECKBIT(globals.ISR,  DRY))
    {
      display.displaySmallBitmap(SYMX2, SYMY, 38, 40, (uint8_t *) symbolDry);
    }

  #ifdef INCUBATOR
    if (CHECKBIT(globals.ISR,  FROST))
    {
      display.displaySmallBitmap(SYMX1, SYMY, 40, 40, (uint8_t *) symbolIce);
    }

    if (flags.isSet(OVERTEMP))
    {
      display.displaySmallBitmap(SYMX1, SYMY, 40, 54, (uint8_t *) symbolHot);
    }
  #endif
  }
}

/**
 * @brief Show the large temperature and humidity displays
 * 
 */
void showLCDReadsHorizontal()
{
  constexpr uint8_t L1 = 30;
  constexpr uint8_t T1 = 10;
  constexpr uint8_t S1 = 8;
  constexpr uint8_t ROWS1 = 3;
  constexpr uint8_t ROWS2 = 1;
  constexpr uint8_t BIAS1 = 2;

  reading_t r = (temperature.getFencedReading());

  colours_t T;

  // test to make sure we're not out of range (-9 to 99)
  if (r >= 99)
  {
    T = segments.setLit(RED, RED);
  }
  else if (r <= -9)
  {
    T = segments.setLit(BLUE, BLUE);
  }
  else
  {
    T = defaultInk;
    r = temperature.getReading();
  }

#ifdef STEADMAN
  char b[5];
  colours_t ink;
  bool jumpTheShark = false;
  if (CHECKBIT(globals.gp, WARNDANGER))
  {
    jumpTheShark = true;
    segments.drawGlyph(190, 0, 'o', L1, L1, ROWS1, BIAS1);
    segments.drawGlyph(240, 0, 'H', L1, L1, ROWS1, BIAS1);

    r = temperature.getEffective();
    
    switch (static_cast<int>(r))
    {
    case TEMP_CAUTION:
      ink = AZURE;
      break;

    case TEMP_WARNING:
      ink = YELLOW;
      break;

    case TEMP_RISK:
      ink = MAGENTA;
      break;

    case TEMP_DANGER:
      ink = RED;
      break;

    default:
      ink = AZURE;
      break;
    }

    if (! CHECKBIT(globals.gp, USEMETRIC))
    {
      r = toFahrenheit(r);
    }

    if (CHECKBIT(globals.ISR, FLASH)) 
    {
      segments.setLit(defaultInk);
    }
    else
    {
      segments.setLit(ink);
    }
  }
  
  sprintf(b, "%3d", static_cast<int>(r * 10));

  segments.drawGlyph(0,   0, b[0], L1, L1, ROWS1, BIAS1);
  segments.drawGlyph(50,  0, b[1], L1, L1, ROWS1, BIAS1);
  segments.drawGlyph(100, 0, b[2], T1, T1, ROWS2, BIAS1);

  if (CHECKBIT(globals.gp, USEMETRIC))
  {
    segments.drawGlyph(130, 0, 'C',  S1, S1, 1, 1);
  }
  else
  {
    segments.drawGlyph(130, 0, 'F',  S1, S1, 1, 1);
  }
  
  segments.setLit(T, T);

  if (jumpTheShark)
  {
    return;
  }
#endif 

  // Now the humidty, which only has an upper range stop of 99%
  r = round(humidity.getFencedReading());
  sprintf(b, "%2d", static_cast<int>(r));
  if (r == 99)
  {
    T = segments.setLit(RED, RED);
  }

  segments.drawGlyph(190,   0, b[0], L1, L1, ROWS1, BIAS1);
  segments.drawGlyph(240,   0, b[1], L1, L1, ROWS1, BIAS1);
  segments.drawPercent(290, 0, S1, 1, 1);

  segments.setLit(T, T);
}

/**
 * @brief Hotstuff's internal clock which ticks every second
 * 
 */

ISR(TIMER1_OVF_vect)    // interrupt service routine for overflow
{
  TCNT1 = UPDATER;     // preload timer

  FLIPBIT(globals.ISR,  FLASH); // flip the boolean for flashing items

  ++isrTimings.timeInSeconds;  // this is determined by the ISR calculation at the head of the sketch.
  ++isrTimings.timeToRead;

  if (isrTimings.timeToRead == READ_UPDATE_TIME)
  {
    isrTimings.timeToRead = 0;
    SETBIT(globals.ISR,  UPDATEREADS);

      ++isrTimings.timeToGraph;

      if (isrTimings.timeToGraph == CHART_UPDATE_FREQUENCY) // note this only "ticks" when the data is read!
      {
        SETBIT(globals.ISR, UPDATEGRAPH);
        isrTimings.timeToGraph = 0;
      }
  }

  if (isrTimings.timeInSeconds == 60)
  {
    isrTimings.timeInSeconds = 0;
    ++isrTimings.timeInMinutes;

    if (isrTimings.timeInMinutes == 1 && isrTimings.timeInSeconds == 0)
    { 
      ++isrTimings.timeToGraph;

      if (isrTimings.timeToGraph == CHART_UPDATE_FREQUENCY)
      {
        SETBIT(globals.ISR, UPDATEGRAPH);
        isrTimings.timeToGraph = 0;
      } 
    }
     
    if (isrTimings.timeInMinutes == 60)
    {
      isrTimings.timeInMinutes = 0;
      ++isrTimings.timeInHours;

      if (isrTimings.timeInHours == 24)
      {
        isrTimings.timeInHours = 0;
        ++isrTimings.timeInDays;
      }
    }
  }
}
