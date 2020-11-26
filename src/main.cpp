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

  * #DEFINES ARE USED IN PREFERENCE TO CONSTS ON MCUS BECAUSE A CONSTEXPR REQUIRES 
  A MEMORY LOCATION (ACCORDING TO THE MANUFACTURER'S APPLICATION NOTE) AND THAT CAN'T 
  OPTIMIZED.

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

// Rotary encoder!? 

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <Wire.h>

#include <Adafruit_GFX.h>     // Core graphics library by AdaFruit
#include <MCUFRIEND_kbv.h>    // David Prentice's Hardware-specific library - your shield might vary
#include "UniversalDHT.hpp"   // @winlinvip's DHT11/22 library functions modified by Tim Harper

#include "types.hpp"
#include "hotstuff_fonts.hpp"
#include "hotstuff.hpp"
#include "sevensegments.hpp"

MCUFRIEND_kbv screen;
Display display;
UniversalDHT dht22(DHT22_DATA);
Graph graph;
Alarm alarm;
Reading humidity;
Reading temperature;
Fonts fonts;
Environmental environment;
Flags flags;
Messages messages;
Sevensegments segments(defaultInk, DEEPBLUE);

// convert KNOWN Y coords to 8-bit only for a hair more speed.
// start working on a version for i2C displays with 128 x 240 etc. screens... both XY are 8-bit

/*
 * Nasty global variable...
 * These flags are set/checked in an interupt service so they need to avoid
 * diving in another subroutine (albetit one that could perceivably be inlined
 * by the compiler.) These macros avoids leaving to chance.
*/  
struct globalVariables
{
  #define SETBIT(flag, bit) (globals.semaphores |= (bit))      //Set bit in byte addr
  #define CLEARBIT(flag, bit) (globals.semaphores &= (~bit))   // Clear bit in byte addr
  #define CHECKBIT(flag, bit) (globals.semaphores & (bit))     // Check bit in byte addr

  uint16_t g_semaphores = 0;
} globals;

void setup()
{
  Serial.begin(9600);
  const int DHT22_POWER {11};      // pin to power the DHT22 since the power pins are covered.
  const int DHT22_DATA  {12};      // The DHT 22 can be powered elsewhere leaving this free however.
  uint16_t ID{screen.readID()};

  if (ID == 0xD3D3)
  {
    ID = 0x9481; //force ID if write-only screen
  }
  screen.begin(ID);
  humidity.setTrace(AZURE);    // humidity graph line
  temperature.setTrace(YELLOW);   // temperature graph line
  fonts.setFont(static_cast<const gfxfont_t *>(&HOTSMALL));

#ifdef USE_METRIC
  flags.set(USEMETRIC);
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
  graph.initGraph(read);
  graph.drawGraph();
}

void loop()
{
  
  if (flags.isSet(UPDATEREADS))
  {
    
    Reading::takeReadings();
    flags.clear(UPDATEREADS);
    showLCDReadsHorizontal();
    messages.showMinMax();
  }

  if (flags.isSet(UPDATEGRAPH))
  {
    readings_t R;
    R.H = humidity.getCMA();
    R.T = temperature.getCMA();
    graph.postReadings(R);
    flags.clear(UPDATEGRAPH);
    graph.drawGraph();
  }

  (flags.isSet(FLASH)) ? display.setFlashInk(defaultInk) : display.setFlashInk(defaultPaper);

  if (flags.isSet(CLEARFROST | CLEARDAMP | CLEARDRY | CLEARDRY))
  {
    display.setFlashInk(defaultPaper);

    if (flags.isSet(CLEARDAMP))
    {
      display.displaySmallBitmap(130, 50, 40, 40, (uint8_t *) symbolDamp);
      flags.clear(CLEARDAMP);
    }

    if (flags.isSet(CLEARFROST))
    {
      display.displaySmallBitmap(130, 50, 40, 40, (uint8_t *) symbolIce);
      flags.clear(CLEARFROST);
    }

    if (flags.isSet(CLEARDRY))
    {
      display.displaySmallBitmap(130, 50, 40, 40, (uint8_t *) symbolDry);
      flags.clear(CLEARDRY);
    }

    if (flags.isSet(CLEARHOT))
    {
      display.displaySmallBitmap(130, 50, 40, 40, (uint8_t *) symbolHot);
      flags.clear(CLEARHOT);
    }
  } 

  if (flags.isSet(FROST | DAMP | DRY | OVERTEMP))     
  {
    if (flags.isSet(DAMP))
    {
      display.displaySmallBitmap(140, 50, 40, 40, (uint8_t *) symbolDamp);
    }

    if (flags.isSet(FROST))
    {
      display.displaySmallBitmap(140, 50, 40, 40, (uint8_t *) symbolIce);
    }

    if (flags.isSet(DRY))
    {
      display.displaySmallBitmap(140, 50, 40, 40, (uint8_t *) symbolDry);
    }

    if (flags.isSet(OVERTEMP))
    {
      display.displaySmallBitmap(140, 50, 40, 54, (uint8_t *) symbolHot);
    }
  }
}

void showLCDReadsVertical()
{
  char b[5];
  int16_t r = temperature.getReading() * 10;
  sprintf(b, "%d", r);

  segments.drawGlyph(0, 0, b[0], 52, 52, 5, 4);
  segments.drawGlyph(90, 0, b[1], 52, 52, 5, 4);
  segments.drawGlyph(200, 0, b[2], 24, 24, 2, 3);
  segments.drawGlyph(190, 100, 'o', 12, 12, 1, 1);
  segments.drawGlyph(220, 100, 'C', 12, 12, 1, 1);

  r = round(humidity.getReading());
  sprintf(b, "%d", r);
  segments.drawGlyph(0, 180, b[0], 52, 52, 5, 4);
  segments.drawGlyph(90, 180, b[1], 52, 52, 5, 4);
  segments.drawPercent(190, 265, 12, 1, 1);
}

void showLCDReadsHorizontal()
{
  char b[5];

  int r = (flags.isSet(USEMETRIC)) ?  temperature.getReading() * 10: (toFahrenheit(temperature.getReading()) * 10);
  sprintf(b, "%3d", r);
  constexpr uint8_t L1 = 30;
  constexpr uint8_t T1 = 10;
  constexpr uint8_t S1 = 8;
  constexpr uint8_t ROWS1 = 3;
  constexpr uint8_t ROWS2 = 1;
  constexpr uint8_t BIAS1 = 2;

  segments.drawGlyph(0,   0, b[0], L1, L1, ROWS1, BIAS1);
  segments.drawGlyph(50,  0, b[1], L1, L1, ROWS1, BIAS1);

  if (flags.isSet(USEMETRIC))
  {
    segments.drawGlyph(100, 0, b[2], T1, T1, ROWS2, 1);
  }
  segments.drawGlyph(130, 0, (flags.isSet(USEMETRIC)) ? 'C' : 'F',  S1, S1, 1, 1);

  r = round(humidity.getReading());
  sprintf(b, "%2d", r);
  segments.drawGlyph(190,   0, b[0], L1, L1, ROWS1, BIAS1);
  segments.drawGlyph(240,   0, b[1], L1, L1, ROWS1, BIAS1);
  segments.drawPercent(290, 0, S1, 1, 1);
}

void Graph::drawGraph()
{
  const colours_t tInk = temperature.getTrace();
  const colours_t hInk = humidity.getTrace();

  screen.fillRect(GRAPH_LEFT, BASE - GRAPH_HEIGHT, GRAPH_WIDTH -1, GRAPH_HEIGHT, defaultPaper);
  drawReticles(6, 6);

  int16_t X = 1 + GRAPH_LEFT;
  for (uint8_t i {1}; i < GRAPH_WIDTH - 1; ++i)
  {
    screen.drawPixel(X + i, BASE - (m_temperature[i] * 2), tInk);
    screen.drawPixel(X + i, BASE -  m_humidity[i],         hInk);
  }
}

void Graph::drawIBar(const ucoordinate_t x, const reading_t reading, int16_t minimum, int16_t maximum, const int8_t scale, const colours_t ink, const bool pointer)
{
  const ucoordinate_t vX = (pointer) ? x - 1 : x + 1; 
  const ucoordinate_t y  = BASE - (static_cast<int8_t>(round(reading)) * scale);
  const uint16_t max     = BASE - (static_cast<int8_t>(round(abs(maximum))) * scale);  
  const uint16_t min     = BASE - (static_cast<int8_t>(round(abs(minimum))) * scale);
  const uint16_t outset  = 5; 
  screen.drawFastVLine(vX, max, min - max, ink);

  if (ink == temperature.getTrace())
  {
    screen.drawFastHLine(vX - outset, y,   outset, ink);
    screen.drawFastHLine(vX - outset, max, outset, ink);
    screen.drawFastHLine(vX - outset, min, outset, ink);      
  }
  else
  {
    screen.drawFastHLine(vX, y,   outset, ink);
    screen.drawFastHLine(vX, max, outset, ink);
    screen.drawFastHLine(vX, min, outset, ink);      
  }
}

void Graph::drawTarget(const ucoordinate_t x, const reading_t reading, const uint16_t scale, const uint8_t size, const colours_t ink)
{
  const uint16_t y = BASE - (static_cast<int8_t>(round(reading)) * scale);
  screen.drawFastHLine(x - size, y, size * 2, ink);
  screen.drawFastVLine(x, y - size, size * 2, ink);
  screen.drawCircle(x, y, 4, ink);
}

void Graph::drawMinMax(const ucoordinate_t x, const reading_t reading, const int16_t minimum, const int16_t maximum, const int8_t scale, const colours_t ink)
{
  const uint16_t outset  = 3; 
  const ucoordinate_t vX = (ink == temperature.getTrace()) ? x - outset : x + 1;
  const ucoordinate_t Y  = BASE - (static_cast<int8_t>(round(reading)) * scale);
  const uint16_t max     = BASE - (static_cast<int8_t>(round(abs(maximum))) * scale);  
  const uint16_t min     = BASE - (static_cast<int8_t>(round(abs(minimum))) * scale);

  screen.drawFastVLine(vX, max, min - max, ink);

  screen.drawLine(vX - outset, max - outset, vX, max, ink);
  screen.drawLine(vX + outset, max - outset, vX, max, ink);
  screen.drawLine(vX - outset, min + outset, vX, min, ink);
  screen.drawLine(vX + outset, min + outset, vX, min, ink);

  if (ink == temperature.getTrace())
  {
    screen.drawFastHLine(vX - outset, Y, outset, ink);
  }
  else
  {
    screen.drawFastHLine(vX, Y, outset, ink);
  }
}

void Graph::drawDiamond(const ucoordinate_t x, const reading_t reading, const uint16_t scale, const uint8_t size, const colours_t ink)
{
  const uint16_t y = BASE - (static_cast<int8_t>(round(reading)) * scale);

  ucoordinates_t d[4] { x - size,  y, 
                        x,  y - size, 
                        x + size,  y, 
                        x,  y + size
                      };

  for (int i{0}; i < 3; ++i)
  {
    screen.drawLine(d[i].X, d[i].Y, d[i + 1].X, d[i + 1].Y, ink);
  }
  screen.drawLine(d[3].X, d[3].Y, d[0].X, d[0].Y, ink);
}

void Graph::drawReticles(const uint8_t xDivs, const uint8_t yDivs)
{
  for (uint8_t i {0}; i < 7; ++i)    // vertical divisions
  {
    screen.drawFastVLine(GRAPH_LEFT + m_xStep * i, BASE - GRAPH_HEIGHT + 20, GRAPH_HEIGHT, reticleColour);
  }

  for (uint8_t i {1}; i < 8; ++i)   // horizontal divisions
  {
    screen.drawFastHLine(GRAPH_LEFT,               BASE - GRAPH_HEIGHT + i * m_yStep,    GRAPH_WIDTH, reticleColour);
  }

  for (uint8_t i {1}; i < 7; ++i)   // humidity ticks
  {
    screen.drawFastHLine(GRAPH_LEFT + GRAPH_WIDTH, BASE - GRAPH_HEIGHT + i * m_yStep, 5, defaultInk);
  }

  for (int8_t i {1}; i < 8; ++i)   // temp ticks
  {
    screen.drawFastHLine(GRAPH_LEFT - 5, BASE - GRAPH_HEIGHT + (i * m_yStep), 5, defaultInk);
  }

  screen.drawFastHLine(GRAPH_LEFT,               BASE,                GRAPH_WIDTH,       defaultInk);
  screen.drawFastVLine(GRAPH_LEFT,               BASE - GRAPH_HEIGHT + 20, GRAPH_HEIGHT + 5, defaultInk);
  screen.drawFastVLine(GRAPH_LEFT + GRAPH_WIDTH, BASE - GRAPH_HEIGHT + 20, GRAPH_HEIGHT + 5, defaultInk);
}

void Graph::initGraph(readings_t read)
{ 
  fonts.setFont(&HOTSMALL);
  screen.fillRect(0, 90, TFT_WIDTH, TFT_HEIGHT, defaultPaper);
  drawGraphScaleMarks();
  drawReticles(6, 6); 
  for (uint8_t i {0}; i < GRAPH_WIDTH; ++i)
  {
    m_temperature[i] = static_cast<int8_t>(read.T);
    m_humidity[i]    = static_cast<int8_t>(read.H);
  }
};

void Graph::drawGraphScaleMarks(void)
{
    fonts.setRotation(3);
    fonts.setFont(&HOTSMALL);
    screen.setTextColor(defaultInk);
    screen.setCursor(AXIS_Y_POSITION, fonts.getYstep());

    if (flags.isSet(USEMETRIC))
    {
        messages.execute(Messages::temperatureScale);
        messages.execute(Messages::c);
    }
    else
    {
        messages.execute(Messages::temperatureScale);
        messages.execute(Messages::f);
    }

    screen.setCursor(AXIS_Y_POSITION, TFT_WIDTH - fonts.getYstep());

    messages.execute(Messages::humidityScale);
    fonts.setRotation(0);

    // temp scale
    for (int8_t i {-1}; i < 6; i++)
    {
        const int yShift = fonts.getYstep() / 2;
        const int X = getGraphX() - (fonts.getXstep() * 3);
        screen.setCursor(X, BASE - (i * m_temperatureStep * m_temperatureScale) + yShift);
        reading_int_t value = (flags.isSet(USEMETRIC)) ? 
                            i * m_temperatureStep : 
                            static_cast<reading_int_t>(toFahrenheit(i * m_temperatureStep));
        char b[6];
        sprintf(b, "%3d", value);
        fonts.print(b);
    }
    
    // humidity scale
    for (uint8_t i {0}; i < 6; i++)
    {
        const int X = getGraphX() + GRAPH_WIDTH + fonts.getXstep();
        const int yShift = fonts.getYstep() / 2;
        screen.setCursor(X, BASE - (i * m_humidityStep) + yShift);
        char b[6];
        sprintf(b, "%3d", (i * m_humidityStep));
        fonts.print(b);
    }
}

readings_t Reading::takeReadings(void)
{
  /*
    Get the current temp and humidity from the sensor.
    Check that the DHTxx didn't develop a fault or break
    during since the last read. If it did, we're going
    to stop work and report a service fault giving the
    failure time so engineers can figure out how reliable
    these devices are in their environment.
  */
  readings_t R;
  UniversalDHT::Response reading = dht22.read(&R.H, &R.T);

  if (reading.error)
  {
    alarm.sensorFailed(reading);
  }

  temperature.updateReading(R.T);
  humidity.updateReading(R.H);
  environment.checkHumidityConditions();
  environment.checkTemperatureConditions();
  environment.checkHeatIndex(R);  
  return R;
}

void Reading::updateReading(const reading_t reading)
{
  m_currRead = reading + m_correction;

  m_minRead  = (reading < m_minRead) ? reading : m_minRead;
  m_maxRead  = (reading > m_maxRead) ? reading : m_maxRead;

  m_cumulativeMovingAverage = (m_cumulativeMovingAverage + (reading - m_cumulativeMovingAverage) / ++m_cmaCounter) + m_correction;
}

void Reading::bufferReading(const reading_t reading, char* buffer, const semaphore_t flags)
{
  using mixed_t = struct 
  {
    int8_t floatPart {0};
    int8_t intPart   {0};
  };
  
  reading_t r = reading;
  if ( flags & IMPERIAL)
  {
    r = toFahrenheit(reading);
  }

  float integer {0};
  float fract   {0};

  mixed_t read;
  fract = modff(r, &integer);
  read.intPart   = static_cast<int>(integer);
  read.floatPart = static_cast<int>(abs(fract * 10));

  if (read.intPart < 100 && read.intPart > - 9)
  {
    sprintf(buffer, "%d.%1d", read.intPart, read.floatPart);
  }
  else
  {
    sprintf(buffer, "%d", read.intPart);
  }
  
  if (flags & HUMIDITY)
  {
    sprintf(buffer, "%d%c", read.intPart, '%');
  }
}

ISR(TIMER1_OVF_vect)    // interrupt service routine for overflow
{
  TCNT1 = UPDATER;     // preload timer

  // this SHOULD use a MACRO (and a global variable for speed on embedded systems)
  flags.flip(FLASH); // flip the boolean for flashing items

  ++isrTimings.timeInSeconds;  // this is determined by the ISR calculation at the head of the sketch.
  ++isrTimings.timeToRead;

  if (isrTimings.timeToRead == 3)
  {
    isrTimings.timeToRead = 0;
    flags.set(UPDATEREADS);
  }


  if (isrTimings.timeInSeconds == 60)
  {
    isrTimings.timeInSeconds = 0;
    ++isrTimings.timeInMinutes;

    if (isrTimings.timeInMinutes == 8 && isrTimings.timeInSeconds == 0)
    {     
      flags.set(UPDATEGRAPH);
    }
     
    if (isrTimings.timeInMinutes == 60)
    {
      isrTimings.timeInMinutes = 0;
      ++isrTimings.timeInHours;

      if (isrTimings.timeInHours == 24)
      {
        isrTimings.timeInHours = 0;
        ++isrTimings.timeInDays;

        if (isrTimings.timeInDays == 7)
        {
          isrTimings.timeInWeeks = 0;
          ++isrTimings.timeInWeeks;
        }
      }
    }
  }
}

void Environmental::checkHumidityConditions(void)
{
  if (humidity.getCMA() > DAMP_AIR_WATERSHED)
  {
    flags.set(DAMP);
  }
      
  if (humidity.getCMA() <= DAMP_AIR_WATERSHED)
  {
    if (flags.isSet(DAMP))
    {
      flags.set(CLEARDAMP);
      flags.clear(DAMP);
    }
  }

  if (humidity.getCMA() < DRY_AIR_WATERSHED)
  {
      flags.set(DRY);
  }

  if (humidity.getCMA() >= DRY_AIR_WATERSHED)
  {
    if (flags.isSet(DRY))
    {
      flags.set(CLEARDRY);
      flags.clear(DRY);
    }
  }
}

void Environmental::checkTemperatureConditions(void)
{
  if (temperature.getReading() <= 1.0)   // 1.0 degrees (C) to allow for errors in the sensor.
  {
    flags.set(FROST);          // start das-blinky-flashun light
  }

  if (temperature.getCMA() > FROST_WATERSHED)
  {
    if (flags.isSet(FROST))
    { 
      flags.clear(FROST);     //Stop the frost warn flashing
      flags.set(CLEARFROST);  // for clean up
    }
  }
}

void Environmental::checkHeatIndex(const readings_t readings)
{
  reading_int_t effectiveTemperature = static_cast<reading_int_t>(heatIndex(readings));

  // heat i routine only works reliably(ish) for temps >26 celcius and RH >= 40%
  if ((effectiveTemperature < 26) || 
                          readings.T < 26 || 
                          readings.H < 40)
  {
    if (flags.isSet(WARNDANGER))
    {
      screen.fillRect(0, 90, TFT_WIDTH, TFT_HEIGHT, defaultPaper);
      flags.clear(WARNDANGER);      
    }
    return;
  }

  flags.set(WARNDANGER);

  screen.fillRect(0, 100, TFT_WIDTH, TFT_HEIGHT - 110, defaultPaper);

  if (effectiveTemperature <= CAUTION)
  {
    messages.flashText(messages.caution);
    unsafeTempWarnings(effectiveTemperature);
  }

  if (effectiveTemperature >= CAUTION && 
      effectiveTemperature <= WARNING)
  {
    messages.flashText(messages.xcaution);
    unsafeTempWarnings(effectiveTemperature);
  }

  if (effectiveTemperature >= WARNING  && 
      effectiveTemperature <= RISK)
  {
    messages.flashText(messages.danger);
    unsafeTempWarnings(effectiveTemperature);
  }
  if (effectiveTemperature >= RISK)
  {
    messages.flashText(messages.xdanger);
    unsafeTempWarnings(effectiveTemperature);
  }
}

void Environmental::unsafeTempWarnings(const reading_t T)
{

    messages.execute(messages.work1);
    messages.execute(messages.work2);

  if (flags.isSet(USEMETRIC))
  {
    screen.print(T);
    fonts.print(F(" C"));
  }
  else
  {
    screen.print(round(toFahrenheit(T)));
    fonts.print(F(" F"));
  }
}

float Environmental::heatIndex(const readings_t readings)
{
  constexpr float c1 {-8.78469475556};
  constexpr float c2 {1.61139411};
  constexpr float c3 {2.33854883889};
  constexpr float c4 {-0.14611605};
  constexpr float c5 {-0.012308094};
  constexpr float c6 {-0.0164248277778};
  constexpr float c7 {0.002211732};
  constexpr float c8 {0.00072546};
  constexpr float c9 {-0.000003582};
  return  (c1 + 
          (c2 *  readings.T) + 
          (c3 *  readings.H) + 
          (c4 *  readings.T  *  readings.H)  + 
          (c5 * (readings.T  *  readings.T)) + 
          (c6 * (readings.H  *  readings.H)) + 
          (c7 * (readings.T  *  readings.T)  *  readings.H)  + 
          (c8 *  readings.T  * (readings.H   *  readings.H)) + 
          (c9 * (readings.T  *  readings.T)  * (readings.H   * readings.H)));
}

float Environmental::magnusDewpoint(const readings_t readings)
{
  // Magnus dew point constants
  constexpr double a = 17.62;
  constexpr double b = 243.12;
  reading_t c = (a * readings.T) / (b + readings.T);
  reading_t r = log(readings.H / 100);

  return static_cast<reading_t>(b * (r + c) / (a - (r + c)));
}

void Alarm::sensorFailed(UniversalDHT::Response response)
{
  // He's dead Jim! He's DEAD!

#ifdef SENSOR_MISSING_OR_BUSTED
 return;
#endif
  screen.fillRect(0, 0, TFT_WIDTH, TFT_HEIGHT, defaultPaper);
  
  screen.setCursor(20, 120);
  screen.print(F("-Sensor Fail-"));
  screen.setCursor(20, 135);

  switch (response.error)
  {
    case SimpleDHTErrStartLow:

      screen.print(F("Start signal arrived early ("));
      screen.print(response.time);
      screen.print(F(" microseconds)"));
      break;

    case SimpleDHTErrStartHigh:
      screen.print(F("Start high came too soon ("));
      screen.print(response.time);
      screen.print(F(" microseconds)"));
      break;

    case SimpleDHTErrDataLow:
      screen.print(F("Start datalow came too soon ("));
      screen.print(response.time);
      screen.print(F(" microseconds)"));
      break;

    case SimpleDHTErrDataEOF:
      screen.print(F("timeout on data EOF signal ("));
      screen.print(response.time);
      screen.print(F(" microseconds)"));
      break;

    case SimpleDHTErrDataHigh:
      screen.print(F("Data high failed ("));
      screen.print(response.time);
      screen.print(F(" microseconds)"));
      break;

    case SimpleDHTErrDataChecksum:
      screen.print(F("failure validating checksum"));
      break;

    case SimpleDHTSuccess: ;  // shuts up the compiler warning
  }
  STOP // loop until re-set.
}

glyph_t Fonts::findGlyphCode(const glyph_t glyph)
{
  // This searches the Flash memory for matching glyph
  // All this pulava is to reduce memory consumption
  // from a bunch of glyphs we'll never use. Bitmaps use 
  // a LOT of space we simply don't have any to waste.

  const gfxfont_t *gfxFont = m_pFont;
  uint8_t glyphCount  = static_cast<uint8_t>(pgm_read_byte(&gfxFont->glyphCount));
  
  int i {0};
  for (; i != glyphCount; ++i)
  {
    gfxglyph_t* theGlyph  = pgm_read_glyph_ptr(gfxFont, i);
    if (glyph == pgm_read_byte(&theGlyph->ascii))
    {
       return i;
    }
  }
  return 0;
}

void Fonts::print(const __FlashStringHelper *flashString)
{
  PGM_P p = reinterpret_cast<PGM_P>(flashString);
  while (glyph_t glyph = pgm_read_byte(p++))
  {
    drawImgGlyph(glyph);
  }
}

void Fonts::print(char* b)
{
  int i{0};
  while (b[i])
  {
    drawImgGlyph(b[i]);
    ++i;
  }
}

void Fonts::print(const int X, const int Y, char* buffer)
{
    int size = (m_bufferWidth * m_bufferHeight) >> 3;
    m_pixelBuffer = new char[size] {};

    if (! m_pixelBuffer)
    {
      screen.fillRect(X, Y, m_bufferWidth, m_bufferHeight, defaultInk);
      STOP
    }
    else
    { 
      screen.setCursor(X, Y);
      m_X = 0;
      m_Y = getYstep();

      int i{0};

      while (buffer[i])
      {
        glyphdata_t glyph;
        prepImgGlyph(findGlyphCode(buffer[i]), &glyph);
        bufferImgGlyph(buffer[i]);
        ++i;
      } 
      showBuffer(X, Y); 
      delete [] m_pixelBuffer;
    }
}

void Fonts::print(const String &string)
{
  for (uint8_t i{0}; i < string.length(); i++)
  {
      drawImgGlyph(string.charAt(i));
  }
}

void Fonts::prepImgGlyph(const glyph_t g, glyphdata_t* data)
{
    const gfxfont_t*  font  = m_pFont;
    gfxglyph_t* glyph = pgm_read_glyph_ptr(font, g);

    data->bitmap       = pgm_read_bitmap_ptr(font);
    data->offset       = pgm_read_word(&glyph->bitmapOffset);
    data->dimensions.H = pgm_read_byte(&glyph->height);
    data->dimensions.W = pgm_read_byte(&glyph->width);
    data->xo           = pgm_read_byte(&glyph->xOffset);
    data->yo           = pgm_read_byte(&glyph->yOffset);
    data->xAdvance     = pgm_read_byte(&glyph->xAdvance);
    data->bits         = 0;
    data->bit          = 0;
    data->x            = fonts.getX();
    data->y            = fonts.getY();
    data->glyph        = g;
    data->colour       = display.getInk();
}

uint8_t Fonts::bufferImgGlyph(const glyph_t glyph)
{
  screen.startWrite();
  glyphdata_t thisGlyph;
  prepImgGlyph(findGlyphCode(glyph), &thisGlyph);

  for (uint8_t i {0}; i < thisGlyph.dimensions.H; ++i) 
  {
      uint16_t X = m_X + thisGlyph.xo;
      uint16_t Y = m_Y + thisGlyph.yo + i;

      for (uint16_t j {0}; j < thisGlyph.dimensions.W; ++j) 
      {
          if (! (thisGlyph.bit & 0x07)) 
          {
            thisGlyph.bits = pgm_read_byte(&thisGlyph.bitmap[thisGlyph.offset++]);
          }
          
          if (thisGlyph.bits & 0x80) 
          {
            bufferPixel(X, Y);
          }
          ++X;
          ++thisGlyph.bit;
          thisGlyph.bits = thisGlyph.bits << 1;
      }
  }
  m_X = m_X + thisGlyph.xAdvance;
 
  screen.setCursor(m_X, m_Y);
  screen.endWrite();
  return thisGlyph.xAdvance;
}

void Display::displaySmallBitmap(ucoordinate_t X, ucoordinate_t Y, uint8_t H, uint8_t W, uint8_t* buffer)
{
  // Tweaked by MD from the orginal by Limor "Lady Ada" Fried. 
  // 8-bits are used in preference to 16 where possible because these are faster on  
  screen.startWrite();

  int16_t byteWidth = (W + 7) >> 3;
  uint8_t byte {0};

  for (int8_t j {0}; j < H; j++, Y++) 
  {
    for (int8_t i {0}; i < W ; i++) 
    {
      if (i & 7)
      {
        byte <<= 1;
      }
      else
      {
        byte = pgm_read_byte(&buffer[j * byteWidth + (i >> 3)]);
      }
      if (! (byte & 0x80))
      {
        screen.writePixel(X + i, Y, m_flash);
      }
    }
  }
  screen.endWrite();
}

uint8_t Fonts::drawImgGlyph(const glyph_t glyph)
{
  m_X = screen.getCursorX();
  m_Y = screen.getCursorY();
  colours_t ink = display.getInk();
  colours_t paper = display.getPaper();
  
  screen.startWrite();
  glyphdata_t thisGlyph;
  prepImgGlyph(findGlyphCode(glyph), &thisGlyph);

  for (uint8_t i {0}; i < thisGlyph.dimensions.H; ++i) 
  {
      uint16_t X = m_X + thisGlyph.xo;
      uint16_t Y = m_Y + thisGlyph.yo + i;

      for (uint16_t j {0}; j < thisGlyph.dimensions.W; ++j) 
      {
          if (! (thisGlyph.bit & 0x07)) 
          {
            thisGlyph.bits = pgm_read_byte(&thisGlyph.bitmap[thisGlyph.offset++]);
          }
          
          if (thisGlyph.bits & 0x80) 
          {
            printPixel(X, Y, ink);
          }
          else
          {
            printPixel(X, Y, paper);
          }
          ++X;
          ++thisGlyph.bit;
          thisGlyph.bits = thisGlyph.bits << 1;
      }
  }
  m_X = m_X + thisGlyph.xAdvance;
  screen.setCursor(m_X, m_Y);
  screen.endWrite();
  return thisGlyph.xAdvance;
}

void Fonts::bufferPixel(const uint16_t X, const uint16_t Y)
{
  if (X >= m_bufferWidth || Y >= m_bufferHeight) 
  {
    return;
  }
  int16_t byteAddress = ((Y * m_bufferWidth) + X) >> 3;  // fast divide by 8
  int16_t bit = 128 >> (X % 8);
  m_pixelBuffer[byteAddress] |= bit;
}

void Fonts::showBuffer(const int X, const int Y)
{
  colours_t ink = display.getInk();
  colours_t paper = display.getPaper();

  for (uint16_t y{0}; y < m_bufferHeight; ++y)
  {
    for (uint16_t x{0}; x < m_bufferWidth; ++x)
    {
      int16_t byteAddress  = ((y * m_bufferWidth) + x) >> 3;  // fast divide by 8
      uint8_t pixelAddress = x % 8;
      uint8_t bit          = 128 >> pixelAddress;

      if (m_pixelBuffer[byteAddress] & bit)
      {
        screen.drawPixel(x + X, y + Y, ink);
      }
      else
      {
        screen.drawPixel(x + X, y + Y, paper);
      }
    }
  }
}

dimensions_t Fonts::getGlyphDimensions(const glyph_t glyph)
{
    glyphdata_t G;
    glyph_t code = findGlyphCode(glyph);
    prepImgGlyph(code, &G);
    return {G.dimensions.W, G.dimensions.W};
}

void Fonts::printPixel(coordinate_t X, coordinate_t Y, colours_t ink)
{
  coordinate_t t;
  switch (m_rotation) 
  {
    case 1:
      t = X;
      X = TFT_WIDTH - 1 - Y;
      Y = t;
      break;
    case 2:
      X = TFT_WIDTH - 1 - X;
      Y = TFT_HEIGHT - 1 - Y;
      break;
    case 3:
      t = X;
      X = Y;
      Y = TFT_HEIGHT - 1 - t;
      break;
  }
  screen.writePixel(X, Y, ink);
}

void Messages::execute(const uint8_t M)
{
  String text = translations[M];
  fonts.print(text);
}

uint16_t Messages::textWidth(char* message)
{
  int x{0};
  uint8_t i{0};

  while (message[i++])
  {
    glyphdata_t data;
    glyph_t code = fonts.findGlyphCode(message[i]);
    fonts.prepImgGlyph(code, &data);
    x += data.xAdvance;
  }
  return x;
}

void Messages::clear(const uint8_t message)
{
  display.setInk(defaultPaper);
  display.setPaper(defaultPaper);
  execute(message);
}

void Messages::flashText(const uint8_t M)
{
  execute(M);
}
  
void Messages::showUptime(void)
{  
  /*
    This block produces the uptime data at the base
    of the screen as a quick check that the machine
    hasn't suffered a power loss or reset.
  */
  char* msg = static_cast<char *> (malloc(40));

  sprintf(msg, "Uptime: %2d Weeks, %2d Days, %02d:%02d:%02d", 
          isrTimings.timeInWeeks,
          isrTimings.timeInDays,
          isrTimings.timeInHours,
          isrTimings.timeInMinutes,
          isrTimings.timeInSeconds);
 
  display.setColours(defaultPaper, GREY);  
  fonts.setFont(&HOTSMALL);
  uint8_t width = (textWidth(msg) / 4) * 4; // Polish off any slight font width weirdness.
  uint8_t margin = (TFT_WIDTH - width) / 2;
  fonts.setBufferDimensions(TFT_WIDTH, 18);
  fonts.print(margin, TFT_HEIGHT - 16, msg);
  display.setColours(defaultInk, defaultPaper); 
  free(msg);
}

void Messages::showMinMax(void)
{  
  char b[10]; 

  int min = temperature.getMinRead();
  int max = temperature.getMaxRead();

  if (flags.isClear(USEMETRIC))
  {
    min = static_cast<int>(toFahrenheit(temperature.getMinRead()));
    max = static_cast<int>(toFahrenheit(temperature.getMaxRead()));
  }

  sprintf(b,"%d", min);
  segments.segmentedString(100, 38, b, 6, 0, 1, 12);

  sprintf(b,"%d", max);
  segments.segmentedString(100, 58, b, 6, 0, 1, 12);

  min = humidity.getMinRead();
  max = humidity.getMaxRead();

  sprintf(b,"%d", min);
  segments.segmentedString(HUMIDITY_X, 38, b, 6, 0, 1, 14);

  sprintf(b,"%d", max);
  segments.segmentedString(HUMIDITY_X, 58, b, 6, 0, 1, 14);
}

void Messages::debugger(const int X, const int Y, char* msg)
{
  fonts.setFont(&HOTSMALL);
  fonts.setBufferDimensions(TFT_WIDTH, 18);
  display.setInk(RED);
  fonts.print(X, Y, msg);
}

void Graph::draw(const quadrilateral_t* quad, const colours_t ink, const colours_t outline)
{
  screen.fillTriangle(quad->cords[0].X, quad->cords[0].Y,
                      quad->cords[1].X, quad->cords[1].Y,
                      quad->cords[2].X, quad->cords[2].Y,
                      ink);

  screen.fillTriangle(quad->cords[0].X, quad->cords[0].Y,
                      quad->cords[3].X, quad->cords[3].Y,
                      quad->cords[2].X, quad->cords[2].Y,
                      ink);

  screen.drawLine(quad->cords[0].X, quad->cords[0].Y, quad->cords[1].X, quad->cords[1].Y, outline);
  screen.drawLine(quad->cords[1].X, quad->cords[1].Y, quad->cords[2].X, quad->cords[2].Y, outline);
  screen.drawLine(quad->cords[2].X, quad->cords[2].Y, quad->cords[3].X, quad->cords[3].Y, outline);
  screen.drawLine(quad->cords[3].X, quad->cords[3].Y, quad->cords[0].X, quad->cords[0].Y, outline);
}

void Graph::rotate(quadrilateral_t* quad, const int16_t rotation)
{
  double sinTheta = sin(DEG_TO_RAD * rotation);
  double cosTheta = cos(DEG_TO_RAD * rotation);
  for (auto i{0}; i < 4; ++i)
  {
    int16_t tX;
    tX = ( (double) quad->cords[i].X * cosTheta - (double)quad->cords[i].Y * sinTheta);
    quad->cords[i].Y  = ( (double) quad->cords[i].X * sinTheta + (double)quad->cords[i].Y * cosTheta);
    quad->cords[i].X = tX;
  }
}

void Graph::translate(triangle_t* triangle, const coordinates_t cords)
{
  for (auto i {0}; i < 4; ++i)
  {
    triangle->cords[i].X += cords.X;
    triangle->cords[i].Y += cords.Y;
  }
}

void Graph::translate(quadrilateral_t* polygon, const coordinates_t cords)//  uint8_t width = (textWidth(msg) / 4) * 4; // Polish off any slight font width weirdness.
{
  for (auto i {0}; i < 4; ++i)
  {
    polygon->cords[i].X += cords.X;
    polygon->cords[i].Y += cords.Y;
  }
}

void Graph::drawPointers()
{
  {
    int16_t t = 33;
    quadrilateral_t pointer;
    pointer.cords[0] = {0,0};
    pointer.cords[1] = {10,-10};
    pointer.cords[2] = {0,64};
    pointer.cords[3] = {-10,-10};

    Graph::rotate(&pointer, t);
    Graph::translate(&pointer, {160,120});
    Graph::draw(&pointer, defaultPaper, defaultPaper);
  }

  {
    int16_t t = 33;
    quadrilateral_t pointer;
    pointer.cords[0] = {0,0};
    pointer.cords[1] = {10,-10};
    pointer.cords[2] = {0,64};
    pointer.cords[3] = {-10,-10};

    Graph::rotate(&pointer, t);
    Graph::translate(&pointer, {160,120});
    Graph::draw(&pointer, BLUE, WHITE);
  }

  {
    int16_t t = -43;
    quadrilateral_t pointer;
    pointer.cords[0] = {0,0};
    pointer.cords[1] = {10,-10};
    pointer.cords[2] = {0,64};
    pointer.cords[3] = {-10,-10};

    Graph::rotate(&pointer, t);
    Graph::translate(&pointer, {160,120});
    Graph::draw(&pointer, GREEN, WHITE);
  }
}

void Graph::drawRadials()

{
 for (int t = 0; t<190; t+=10)
  {
    quadrilateral_t tick;
    tick.cords[0] = {-80, -2};
    tick.cords[1] = {-60, -2};
    tick.cords[2] = {-60, 2};
    tick.cords[3] = {-80, 2};

    Graph::rotate(&tick, t);
    Graph::translate(&tick, {160,120});
    Graph::draw(&tick, YELLOW, YELLOW);
  }

  for (int t = 190; t<360; t+=10)
  {
    quadrilateral_t tick;
    tick.cords[0] = {-80, -2};
    tick.cords[1] = {-60, -2};
    tick.cords[2] = {-60, 2};
    tick.cords[3] = {-80, 2};

    Graph::rotate(&tick, t);
    Graph::translate(&tick, {160,120});
    Graph::draw(&tick, RED, RED);
  }
}

inline void Sevensegments::drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag)
{
  coordinate_t y = Y + m_rows;
  for (uint8_t i = m_rows; i != 0; --i)                       // counting DOWN to 0 is faster for time critical loops
  {
    screen.drawFastHLine(X + i, y + i, m_Xlength - (i << 1), (onFlag) ? m_lit : m_unlit);
    screen.drawFastHLine(X + i, y - i, m_Xlength - (i << 1), (onFlag) ? m_lit : m_unlit);
  }
    screen.drawFastHLine(X, y, m_Xlength, (onFlag) ? m_lit : m_unlit);
}

inline void Sevensegments::drawVSegment(const coordinate_t X, const coordinate_t Y, const  uint8_t onFlag)
{
 coordinate_t x = X + m_rows; 
 for (uint8_t i = m_rows; i != 0; --i)
  {
    screen.drawFastVLine(x + i, Y + i, m_Ylength - (i << 1), (onFlag) ? m_lit : m_unlit);
    screen.drawFastVLine(x - i, Y + i, m_Ylength - (i << 1), (onFlag) ? m_lit : m_unlit);
  }
    screen.drawFastVLine(x, Y, m_Ylength, (onFlag) ? m_lit : m_unlit);
}

inline void Sevensegments::drawRLSegment(coordinate_t X, coordinate_t Y, coordinate_t X1, coordinate_t Y1, const uint8_t rows, uint8_t onFlag)
{
  Y1 -= rows;
  for (uint8_t i = (rows << 1); i > 0; --i)
  {
    fastShortLine(X, Y + i, X1, Y1 + i, (onFlag) ? m_lit : m_unlit);
  }
}

inline void Sevensegments::drawLRSegment(coordinate_t X, coordinate_t Y, coordinate_t X1, coordinate_t Y1, const uint8_t rows, uint8_t onFlag)
{
  Y1 -= rows;  
  for (uint8_t i = (rows << 1); i > 0 ; --i)
  {
    fastShortLine(X, Y + i, X1, Y1 + i, (onFlag) ? m_lit : m_unlit);
  }
}

void Sevensegments::drawGlyph(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, uint8_t wide, uint8_t high, const uint8_t rows, const uint8_t bias)
{
  wide = ((wide >> 1) << 1);
  high = ((high >> 1) << 1);
  
  setXlen(wide);
  setYlen(high);
  setRows(rows);
  setBias(bias);
  uint8_t S = translateChar(glyph);
  if (S == B11111110)
  {
    slash(X, Y, wide, high*2, 2);
    return;
  }

  uint8_t biasA = bias << 1;
  
  drawHSegment(X + rows + bias,  Y,                              (S & B10000000) ? 1 : 0);  //seg A
  drawHSegment(X + bias + rows,  Y + (high << 1) + biasA + bias, (S & B00010000) ? 1 : 0);  //seg D
  drawHSegment(X + rows + bias,  Y + high + bias + (bias >> 1),  (S & B00000010) ? 1 : 0);  //seg G (Bias >> 1 + bias is a fast mult by 1.5)

  drawVSegment(X + wide + biasA, Y + rows +        bias,         (S & B01000000) ? 1 : 0);  //seg B
  drawVSegment(X + wide + biasA, Y + high + rows + biasA,        (S & B00100000) ? 1 : 0);  //seg C
  drawVSegment(X,                Y + high + rows + biasA,        (S & B00001000) ? 1 : 0);  //seg E
  drawVSegment(X,                Y + rows +        bias,         (S & B00000100) ? 1 : 0);  //seg F
}

void Sevensegments::drawPercent(coordinate_t X, coordinate_t Y, const uint8_t size, const uint8_t rows, const uint8_t bias)
{
  setXlen(size);
  setYlen(size);
  setRows(rows);
  setBias(bias);

  uint8_t biasA = m_bias << 1;

  drawHSegment(X + rows + bias,  Y,                              1);  //seg A
  drawHSegment(X + rows + bias,  Y + size + bias + (bias >> 1),  1);  //seg G (Bias >> 1 + bias is a fast mult by 1.5)
  drawVSegment(X + size + biasA, Y + rows +        bias,         1);  //seg B
  drawVSegment(X,                Y + rows +        bias,         1);  //seg F

  X += m_Xlength << 1;
  Y += m_Xlength << 1;

  drawHSegment(X + rows + bias,  Y,                              1);  //seg A
  drawHSegment(X + rows + bias,  Y + size + bias + (bias >> 1),  1);  //seg G (Bias >> 1 + bias is a fast mult by 1.5)
  drawVSegment(X + size + biasA, Y + rows +        bias,         1);  //seg B
  drawVSegment(X,                Y + rows +        bias,         1);  //seg F
  slash(X, Y - m_Xlength, m_Xlength, (m_Xlength << 1), 4);
}

int Sevensegments::segmentedString(coordinate_t X, coordinate_t Y, char * b, uint8_t size, uint8_t rows, uint8_t bias, uint8_t step)
{
  uint8_t i {0};
  while (*b)
  {
    segments.drawGlyph(X + (step * i++), Y, *b++, size, size, rows, bias);
  }
  return X + step * (i -1);
}

inline void Sevensegments::slash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows)
{
  // insert dope Saul Hudson gag here...  
  for (int i = 0; i < rows; ++i)
  {
    screen.drawLine(X + i, Y, X + i - wide, Y + high, m_lit);
  }
}

void Sevensegments::drawGlyph16(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, uint8_t size, const uint8_t rows, uint8_t bias)
{
  uint16_t S = translateChar16(glyph);

  uint8_t shorts = size >> 1;

  int16_t X0 = X  + bias   + rows;
  int16_t X1 = X0 + shorts - rows;
  int16_t X2 = X1 + bias   + rows;
  int16_t X3 = X2 + shorts - rows;

  int16_t Y0 = Y  + bias   + rows + 1;
  int16_t Y2 = Y  + bias   + size + rows + 2;
  int16_t Y1 = Y2 - rows   - 1;
  int16_t Y3 = Y  + bias   * 2    + size * 2 + 2;

  setXlen(shorts);
  setYlen(size);
  setRows(rows);
  setBias(bias);
  
  drawHSegment(X0, Y,  (S & SEG_A1) ? 1 : 0);  //seg A1
  drawHSegment(X2, Y,  (S & SEG_A2) ? 1 : 0);  //seg A2

  drawHSegment(X0, Y1, (S & SEG_G1) ? 1 : 0);  //seg G1 
  drawHSegment(X2, Y1, (S & SEG_G2) ? 1 : 0);  //seg G2 

  drawVSegment(X,  Y0, (S & SEG_F) ? 1 : 0);  //seg F 
  drawVSegment(X,  Y2, (S & SEG_E) ? 1 : 0);  //seg E 

  drawHSegment(X0, Y3, (S & SEG_D1) ? 1 : 0);  //seg D1 
  drawHSegment(X2, Y3, (S & SEG_D2) ? 1 : 0);  //seg D2 

  drawVSegment(X1, Y0, (S & SEG_I) ? 1 : 0);  //seg I
  drawVSegment(X1, Y2, (S & SEG_L) ? 1 : 0);  //seg L

  drawVSegment(X3, Y0, (S & SEG_B) ? 1 : 0);  //seg B
  drawVSegment(X3, Y2, (S & SEG_C) ? 1 : 0);  //seg C

  drawLRSegment(X0 + rows + 1,
                Y  + (rows << 1) + 1 + bias, 
                X  + shorts, 
                Y  + size - (rows >> 1) - rows,
                (rows << 1), (S & SEG_H) ? 1 : 0);

  drawRLSegment(X1 + shorts,
                Y  + (rows << 1) + 1 + bias, 
                X2 + 1 + rows,
                Y  + size - (rows >> 1) - rows,
                (rows << 1), (S & SEG_J) ? 1 : 0);

  drawRLSegment(X  + shorts, 
                Y1 + (rows << 1) + 1 + bias, 
                X0 + rows + 1, 
                Y1 + size - (rows >> 1) - rows,
                (rows << 1), (S & SEG_K) ? 1 : 0);

  drawLRSegment(X2 + 1 + rows, 
                Y1 + (rows << 1) + 1 + bias, 
                X1 + shorts - 1, 
                Y1 + size - (rows >> 1) - rows - + 1 - bias,
                (rows << 1), (S & SEG_M) ? 1 : 0);
}

void Sevensegments::drawDP(const coordinate_t X, const coordinate_t Y, const uint8_t radius, const uint8_t onFlag)
{
  screen.fillCircle(X, Y, radius, (onFlag) ? m_lit : m_unlit);
}

void Sevensegments::fastShortLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t ink) 
{
  int8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) 
  {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }

  if (x0 > x1) 
  {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }

  int8_t dx    = x1     - x0;
  int8_t dy    = abs(y1 - y0);
  int8_t error = dx >> 1;
  int8_t ystep = (y0 < y1) ? 1 : -1;

  for (; x0 <= x1; x0++) 
  {
    if (steep) 
    {
      screen.drawPixel(y0, x0, ink);
    } 
    else 
    {
      screen.drawPixel(x0, y0, ink);
    }

    error -= dy;
    if (error < 0) 
    {
      y0    += ystep;
      error += dx;
    }
  }
}
