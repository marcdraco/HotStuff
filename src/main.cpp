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
  C ALLOWS YOU TO LEAVE OUT ENCLOSING BRACES, DOESN'T MEAN YOU *SHOULD* LEAVE THEM 
  OUT BECAUSE THAT SORT OF THING ONLY LEADS TO ACCIDENTAL LINE INSERTIONS THAT 
  DON'T WORK AS INTENDED.
  
  WANT DO MULTIPLY BY 2? USE VAR = VAR *2, VAR <<= 1 WILL DO THE SAME THING BUT THE 
  COMPILER WILL DO THAT ASSUMING IT DOESN'T OPTIMISE YOUR HARDER TO READ CODE AWAY 
  ANYWAY. ONLY USE SHIFT OPERATORS WHEN YOU MEAN TO SHIFT BITS"

  #DEFINES ARE USED IN PREFERENCE TO CONSTS BECAUSE THEY CAN SAVE A LITTLE MEMORY 
  AND MEMORY IS VERY PRECIOUS ON MCUS!
  
  YOU MIGHT THINK YOURSELF CLEVER, BUT BET YOUR BUTT THE COMPILER IS SMARTER AND CAN
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
#include "UniversalDHT.hpp"   // @winlinvip's DHT11/22 library functions modified by Tim Harper

#include "types.hpp"
#include "hotstuff_fonts.hpp"
#include "hotstuff.hpp"

MCUFRIEND_kbv screen;
Display display;
UniversalDHT dht22(DHT22_DATA);
Graph graph;
Alarm alarm;
Reading humidity;
Reading temperature;
Messages messages;
Fonts fonts;
Environmental environment;
Flags flags;
/*
void SerialBar(char *b)
{
  for (int n = 0; n < 25; n++)
  {
    Serial.print("=");
  }

  Serial.print(b);

  for (int n = 0; n < 25; n++)
  {
    Serial.print("=");
  }
  Serial.println("");
}
*/

void pause()
{
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    while (digitalRead(BUTTON_PIN) == HIGH)
    {

    }    
  }
  delay(100);
};

void setup()
{
 uint16_t ID{screen.readID()};

  if (ID == 0xD3D3)
  {
    ID = 0x9481; //force ID if write-only screen
  }
  screen.begin(ID);
  humidity.setTrace(AZURE);    // humidity graph line
  temperature.setTrace(YELLOW);   // temperature graph line

  fonts.setFont(static_cast<const gfxfont_t *>(&HOTLARGE));
  humidity.setX(160);
  humidity.setY(10);
  temperature.setY(10);

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

  graph.initGraph();
  fonts.setFont(&HOTSMALL);
  screen.fillRect(0, TFT_HEIGHT - 16, TFT_WIDTH, 16, GREY); //just that little Uptime display, a nod to *nix.

  pinMode(BUTTON_PIN, INPUT);         // Our last spare pin (phew) is going to be dual purpose!
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Hold it high so it goes active LOW when pressed.
  pinMode(ALARM_PIN, OUTPUT);         // This is usually pin 13 (the board LED)
  pinMode(DHT22_POWER, OUTPUT);       // cheeky way to power the DHT22, but it only requires 1.5mA
  digitalWrite(DHT22_POWER, HIGH);    // and saves wiring from the ICSP ports on UNO with a TFT shield
  pinMode(DHT22_DATA, INPUT_PULLUP);  // keep the data pin from just hanging around

  readings_t read;
  
  dht22.read(&read.H, &read.T);
  
  temperature.setLowRead(read.T);
  temperature.setHighRead(read.T);
  temperature.updateReading(read.T);
  humidity.setLowRead(read.H);
  humidity.setHighRead(read.H);
  humidity.updateReading(read.H);
}
 
void loop()
{

  temperature.takeReadings();
  humidity.takeReadings();

  temperature.showReadings();  
  humidity.showReadings();  

  if (isrTimings.timeInSeconds == 0) // this ticks every minute
  {
    /*
      The "timeToRead" variable is incremented by the interupt service routine
      once every second. After three seconds we take a new read. Use a larger 
      int if you prefer. Area temperatures don't vary much unless the sensor is 
      in a drafty corner!
    */
    flags.set(UPDATEREADS);
  }

  while (isrTimings.timeToRead < 3)
  {
    alarm.checkAlarm();
    alarm.annunciators();
    alarm.checkButton();
    messages.showUptime();
  }
}

void showLCDReads(void)
{}

void Graph::displayGraph(void)
{
    if (flags.isSet(UPDATEREADS))
    {
      return;
    }
    flags.clear(UPDATEREADS);

    drawReticles();

    if (temperature.getCMA() > 50)
    {
      temperature.setY((GRAPH_Y + FSD) - 100);
    }
    else if (temperature.getCMA() < 0)
    {
      temperature.setY(GRAPH_Y + FSD);
    }
    else
    {
      temperature.setY((GRAPH_Y + FSD) - (round(temperature.getCMA()) * 2));
    }

    humidity.setY((GRAPH_Y + FSD) - round(humidity.getCMA()));

    //put the latest readings at the end of the pipe.

    uint8_t step{16}; 

    for (auto i {0}; i < getGraphWidth() -1; i += step)
    {
      colours_t T = temperature.getTrace();
      colours_t H = humidity.getTrace();
      ucoordinate_t xPosition = i + getGraphX();
      int temperatureX = xPosition;
      int humidityX    = xPosition + (step / 2) + 1;
      int baseY        = GRAPH_Y;
      {
        int min = random(20)+18;
        int max = random(20)+20;
        drawIBar(temperatureX , baseY, 5, abs(max - min), T);
      }

      {
        int min = random(10)+50;
        int max = random(10)+50;
        drawIBar(humidityX , baseY, 5, abs(max - min), H);
      }
    }
    temperature.slidePipe();
    humidity.slidePipe();
}

void Graph::drawIBar(const ucoordinate_t &X, const ucoordinate_t &Y, const ucoordinate_t &W, const ucoordinate_t &H, const colours_t &ink)
{
  screen.drawFastHLine(X, Y, W, ink);
  screen.drawFastHLine(X, Y + H, W, ink);
  screen.drawFastVLine(X + (W/2), Y, H, ink); // width should be an odd number or this looks odd
}

void Graph::drawMainAxes(void)
{
  screen.drawFastHLine(getGraphX(), GRAPH_Y + FSD, getGraphWidth(), defaultInk);
  screen.drawFastVLine(getGraphX() - 1, GRAPH_Y, FSD, defaultInk);
  screen.drawFastVLine(getGraphX() + getGraphWidth(), GRAPH_Y, FSD, defaultInk);
}

void Graph::drawReticles(void)
{
   // draws vertical blanking strokes and reticules 
  for (auto i {0}; i < getGraphWidth(); ++i)    
  {
    ucoordinate_t xPosition = i + getGraphX();

    // seven vertical divisions
    if (i % (getGraphWidth() / 8) == 0)              
    {
      screen.drawFastVLine(xPosition, GRAPH_Y, FSD, reticleColour);
    }
  }

  for (auto i {0}; i < FSD + 20; i = i + 20)
  {
    screen.drawFastHLine(getGraphX(), GRAPH_Y + i, getGraphWidth(), reticleColour);
  }

  minmax_t humids;
  minmax_t temps;

  humids.max = (GRAPH_Y + HEIGHT) - MAX_COMFORT_HUMID;
  humids.min = (GRAPH_Y + HEIGHT) - MIN_COMFORT_HUMID;
  temps.min = (GRAPH_Y + HEIGHT) - MIN_COMFORT_TEMP * 2;
  temps.max = (GRAPH_Y + HEIGHT) - MAX_COMFORT_TEMP * 2;

  for (auto i {1}; i <getGraphWidth(); i += 10)     
  {
    auto width {3};
    screen.drawFastHLine(getGraphX() + i, humids.max, width, BROWNISH);
    screen.drawFastHLine(getGraphX() + i, humids.min, width, BROWNISH);
    screen.drawFastHLine(getGraphX() + i, temps.min, width, PURPLEISH);
    screen.drawFastHLine(getGraphX() + i, temps.max, width, PURPLEISH);
  }
}

void Graph::initGraph(void)
{
  if (flags.isSet(GRAPHACTIVE))
  {
    return;
  }
  
  /*
  * Allow space for fonts 
  * 2 * height "temperature in *" and "Relative humidity" message.  
  * 8 * (!) font width allows for the scale markings
  */
  fonts.setFont(&HOTSMALL);
  setGraphWidth(TFT_WIDTH - ((2 * fonts.getYstep()) + (8 * fonts.getXstep())));

  screen.fillRect(0, 90, TFT_WIDTH, TFT_HEIGHT, display.getPaper());
  drawGraphScaleMarks();
  drawMainAxes();
  drawReticles(); 
  flags.set(GRAPHACTIVE);
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
    for (auto i{-10}; i < 50; i += 10)
    {
        fonts.setFont(&HOTSMALL);
        char b[6];
        reading_int_t value;
        screen.setCursor(getGraphX() - (fonts.getXstep() * 3), 
                        (GRAPH_Y + FSD) - (i * 2) - 20);

        (flags.isSet(USEMETRIC)) ? value = i : value = static_cast<reading_int_t>(toFahrenheit(i));
        sprintf(b, "%3d", value);
        fonts.print(b);
    }
        
    // humidity scale
    for (auto i{0}; i < 120; i += 20)
    {
        fonts.setFont(&HOTSMALL);
        char b[6];
        screen.setCursor(getGraphX() + getGraphWidth() + fonts.getXstep(), (GRAPH_Y + FSD - 4) - i );
        sprintf(b, "%3d", i);
        fonts.print(b);
    }
}

void Reading::takeReadings(void)
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
  if (reading.error != 0)
  {
    alarm.sensorFailed(reading);
  }

  temperature.updateReading(R.T);
  humidity.updateReading(R.H);
  isrTimings.timeToRead = 0;

  environment.checkHumidityConditions();
  environment.checkTemperatureConditions();
  environment.checkHeatIndex(R);  
}

void Reading::updateReading(const reading_t &reading)
{
  m_reading = reading + m_correction;
  m_lowRead = (reading > m_lowRead) ? reading : m_lowRead;
  m_highRead = (reading > m_highRead) ? reading : m_highRead;

  m_cumulativeMovingAverage = (m_cumulativeMovingAverage + 
                              (m_reading - m_cumulativeMovingAverage) / ++m_cmaCounter
                              );
  
  setPipe(HOURS - 1, static_cast<const uint8_t>(round(m_lowRead)), 
                     static_cast<const uint8_t>(round(m_highRead))
         );
}

void Reading::showReadings(void)
{
    fonts.setFont(&HOTLARGE);
    display.setInk(defaultInk);
    char buffer[10];

    graph.displayGraph();

    fonts.setFont(&HOTLARGE);
    fonts.setBufferDimensions(FONT_BUFF_WIDTH, FONT_BUFF_HEIGHT);
    bufferReading(temperature.getReading(), buffer, (flags.isSet(USEMETRIC)) ? METRIC : IMPERIAL);  
    fonts.print(0, 0, buffer);
    
    bufferReading(humidity.getReading(), buffer, HUMIDITY);
    fonts.print(TFT_WIDTH / 2, 0, buffer);
}

void Reading::bufferReading(const reading_t &reading, char* buffer, const semaphore_t &flags)
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

  if (flags & METRIC) 
  {
    sprintf(buffer, "%d.%1d", read.intPart, read.floatPart);
  }

  if (flags & IMPERIAL)
  {
    sprintf(buffer, "%d", read.intPart);
  }
  
  if (flags & HUMIDITY)
  {
    sprintf(buffer, "%d%c", read.intPart, '%');
  }
}

void Environmental::setColour(const reading_t &value, const limits_t &limits)
{
  if (value < static_cast<reading_t>(limits.lower))
  {
    display.setInk(LOW_LIMIT_EXCEEDED);
    return;
  }
  else if (value > static_cast<reading_t>(limits.upper))
  {
    display.setInk(HIGH_LIMIT_EXCEEDED);
    return;
  }
  display.setInk(defaultInk);
  return;
}

ISR(TIMER1_OVF_vect)    // interrupt service routine for overflow
{
  TCNT1 = UPDATER;     // preload timer

  ++isrTimings.timeToRead;

  flags.flip(FLASHING); // flip the boolean for flashing items

  ++isrTimings.timeInSeconds;  // this is determined by the ISR calculation at the head of the sketch.

  if (isrTimings.timeInSeconds == 60)
  {
    isrTimings.timeInSeconds = 0;
    ++isrTimings.timeInMinutes;

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

          if (isrTimings.timeInWeeks == 52)
          {
            isrTimings.timeInWeeks = 0;
            ++isrTimings.timeInYears;
          }
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

  if (humidity.getCMA() < DRY_AIR_WATERSHED)
  {
    flags.clear(DRY);
  }

  if (humidity.getCMA() >= DRY_AIR_WATERSHED)
  {
    flags.set(DRY);
  }
  
  if (humidity.getCMA() <= DAMP_AIR_WATERSHED)
  {
    flags.clear(DAMP);
  }
}

void Environmental::checkTemperatureConditions(void)
{
  if (temperature.getReading() <= 1.0)   // 1.0 degrees (C) to allow for errors in the sensor.
  {
    flags.set(FROST);          // start das-blinky-flashun light
    flags.set(ALARMFROST);     // true prevents re-firing
  }

  if (temperature.getCMA() > FROST_WATERSHED)
  {
    flags.clear(FROST);          // start das-blinky-flashun light
    flags.clear(ALARMFROST);     // true prevents re-firing
  }
}

void Environmental::checkHeatIndex(const readings_t &readings)
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

void Environmental::unsafeTempWarnings(const reading_t &T)
{
  screen.setTextSize(3);

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

float Environmental::heatIndex(const readings_t &readings)
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

float Environmental::magnusDewpoint(const readings_t &readings)
{
  // Magnus dew point constants
  constexpr double a = 17.62;
  constexpr double b = 243.12;
  reading_t c = (a * readings.T) / (b + readings.T);
  reading_t r = log(readings.H / 100);

  return static_cast<reading_t>(b * (r + c) / (a - (r + c)));
}

void Alarm::annunciators(void)
{
  fonts.setFont(&HOTSMALL);
  if ( flags.isSet(FROST))
  {
    screen.setCursor(FROSTWARN_X, FROSTWARN_Y);
    messages.execute(FROST);
  }
  else
  {
    screen.setCursor(FROSTWARN_X, FROSTWARN_Y);
    messages.clear(FROST);
  }

  if (flags.isSet(DAMP))
  {
    screen.setCursor(DAMP_WARN_X, DAMP_WARN_Y);
    messages.execute(DAMP);
  }
  else
  {
    screen.setCursor(DAMP_WARN_X, DAMP_WARN_Y);
    messages.clear(DAMP);
  }

  if (flags.isSet(DRY))
  {
    screen.setCursor(DRY_WARN_X, DRY_WARN_Y);
    messages.execute(DRY);
  }
  else
  {
    screen.setCursor(DRY_WARN_X, DRY_WARN_Y);
    messages.clear(DRY);
  }
}

void Alarm::checkAlarm(void)
{

  if (flags.isClear(FROST | DAMP | DRY | OVERTEMP)) 
  {
    digitalWrite(ALARM_PIN, LOW);
  }

  if (flags.isSet(FROST | DAMP | DRY | OVERTEMP))
  {
    if (flags.isSet(FLASHING))
    {
      digitalWrite(ALARM_PIN, HIGH);
    }
    else
    {
      digitalWrite(ALARM_PIN, LOW);
    }
  }
}

void Alarm::checkButton(void)
{
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        STOP
    }

    if (digitalRead(BUTTON_PIN) == HIGH)
    {
        if (! m_timer)
        {
            if (m_timer < SHORTPRESS) // button.shortPress)
            {
                flags.clear(FROST | DAMP | DRY | OVERTEMP);
                m_timer = 0;
                digitalWrite(ALARM_PIN, LOW);
            }
        }
    }
    else
    {
        if (! m_timer)
        {
            m_timer = 1;
        }
        else
        {
            m_timer += 1;
        }
    }

    if (m_timer > LONGPRESS)
    {
        // Toggle metric/imperial
        (flags.flip(METRIC) );
        screen.fillRect(LOW_TEMP_X,     LOW_TEMP_Y,  72,  8,     defaultPaper);
        screen.fillRect(LEFTMARGIN - 2, LOWHUMID_Y + 12, 20, 40, defaultPaper);
        m_timer = 0;
        temperature.showReadings();
        graph.drawGraphScaleMarks();
    }
}

void Alarm::sensorFailed(UniversalDHT::Response response)
{
  // He's dead Jim! He's DEAD!

#ifdef SENSOR_MISSING_OR_BUSTED

  return;
#endif
  screen.fillRect(0, 0, TFT_WIDTH, TFT_HEIGHT, defaultPaper);
  
  screen.print(F(" -Sensor Fail-"));
  screen.print(F("             Y  M  D  HH:MM:SS"));
  screen.print(F("Sensor age: "));

  char printable[60];
  
  sprintf(printable, "%2d %2d %2d  %02d:%02d:%02d", 
                      isrTimings.timeInYears,
                      isrTimings.timeInWeeks,
                      isrTimings.timeInDays,
                      isrTimings.timeInHours,
                      isrTimings.timeInMinutes,
                      isrTimings.timeInSeconds);
  
  screen.print(printable);

  // High 8bits are time duration (not shown)
  // Low 8bits are error code.
  // @see https://github.com/winlinvip/SimpleDHT/issues/25

  screen.setCursor(LEFTMARGIN, 160);
  switch (response.error)
  {
    case SimpleDHTErrStartLow:

      screen.print(F("Start came too early ("));
      screen.print(response.time);
      screen.print(F(") microseconds"));
      break;

    case SimpleDHTErrStartHigh:
      screen.print(F("Start high came too soon ("));
      screen.print(response.time);
      screen.print(F(") microseconds"));
      break;

    case SimpleDHTErrDataLow:
      screen.print(F("Start datalow came too soon ("));
      screen.print(response.time);
      screen.print(F(") microseconds"));
      break;

    case SimpleDHTErrDataEOF:
      screen.print(F("timeout on data EOF signal ("));
      screen.print(response.time);
      screen.print(F(") microseconds"));
      break;

    case SimpleDHTErrDataHigh:
      screen.print(F("Data high failed ("));
      screen.print(response.time);
      screen.print(F(") microseconds"));
      break;

    case SimpleDHTErrDataChecksum:
      screen.print(F("failure validating checksum"));
      break;
    case SimpleDHTSuccess: ;  // shuts up the compiler warning
  }

  while (true); // loop until re-set.
}

glyph_t Fonts::findGlyphCode(const glyph_t &glyph)
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

void Fonts::print(char* b, const bool &switchFloats)
{
  int i{0};
  while (b[i])
  {
    if ( static_cast<char> (b[i]) == '.' && switchFloats)
    {
      setFont(&HOTSMALL);
    }
    drawImgGlyph(b[i]);
    ++i;
  }
  setFont((gfxfont_t*) &HOTLARGE);
}

void Fonts::print(const int &X, const int &Y, char* buffer)
{
    int size = (m_bufferWidth * m_bufferHeight) >> 3;
    m_pixelBuffer = new char[size] {};

    if (! m_pixelBuffer)
    {
      screen.fillRect(0, 0, m_bufferWidth, m_bufferHeight, RED);
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
    return;
}

void Fonts::print(const String &string)
{
  for (uint8_t i{0}; i < string.length(); i++)
  {
      drawImgGlyph(string.charAt(i));
  }
}

void Fonts::prepImgGlyph(const glyph_t &g, glyphdata_t* data)
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

uint8_t Fonts::bufferImgGlyph(const glyph_t &glyph)
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

uint8_t Fonts::drawImgGlyph(const glyph_t &glyph)
{
  m_X = screen.getCursorX();
  m_Y = screen.getCursorY();

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
            printPixel(X, Y, m_ink);
          }
          else
          {
            printPixel(X, Y, m_paper);
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

void Fonts::bufferPixel(const uint16_t &X, const uint16_t &Y)
{
  if (X >= m_bufferWidth || Y >= m_bufferHeight) 
  {
    return;
  }
  int16_t byteAddress = ((Y * m_bufferWidth) + X) >> 3;  // fast divide by 8
  int16_t bit = 128 >> (X % 8);
  m_pixelBuffer[byteAddress] |= bit;
}

void Fonts::showBuffer(const int &X, const int &Y)
{
  for (uint16_t y{0}; y < m_bufferHeight; ++y)
  {
    for (uint16_t x{0}; x < m_bufferWidth; ++x)
    {
      int16_t byteAddress  = ((y * m_bufferWidth) + x) >> 3;  // fast divide by 8
      uint8_t pixelAddress = x % 8;
      uint8_t bit          = 128 >> pixelAddress;

      if (m_pixelBuffer[byteAddress] & bit)
      {
        screen.drawPixel(x + X, y + Y, m_ink);
      }
      else
      {
        screen.drawPixel(x + X, y + Y, m_paper);
      }
    }
  }
}

dimensions_t Fonts::getGlyphDimensions(const glyph_t &glyph)
{
    glyphdata_t G;
    glyph_t code = findGlyphCode(glyph);

    prepImgGlyph(code, &G);

    return {G.dimensions.W, G.dimensions.W};
}

void Fonts::setTextColor(const colours_t &ink, const colours_t &paper)
{
  m_ink = ink;
  m_paper = paper;
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

void Messages::execute(const char* buffer)
{
  fonts.setTextColor(defaultInk, defaultPaper);
  fonts.print((char *)(buffer));
}

void Messages::execute(const uint8_t &M)
{
  fonts.setTextColor(defaultInk, defaultPaper);
  String text = translations[M];
  fonts.print(text);
}

uint16_t Messages::textWidth(char* message)
{
  int x{0};
  unsigned int i{0};
 
  while (message[i++])
  {
    glyphdata_t data;
    glyph_t code = fonts.findGlyphCode(message[i]);
    fonts.prepImgGlyph(code, &data);
    x += data.xAdvance;
  }
  return x;
}

void Messages::clear(const uint8_t &message)
{
  display.setInk(defaultPaper);
  display.setPaper(defaultPaper);
  execute(message);
}

void Messages::flashText(const uint8_t &M)

{
  execute(M);
  flags.flip(FLASHING);
}

void Messages::showUptime(void)
{  
  /*
    This block produces the uptime data at the base
    of the screen as a quick check that the machine
    hasn't suffered a power loss or reset.
  */
  char* msg = new char[40];

  sprintf(msg, "Uptime: %2d Weeks, %2d Days, %02d:%02d:%02d", 
          isrTimings.timeInWeeks,
          isrTimings.timeInDays,
          isrTimings.timeInHours,
          isrTimings.timeInMinutes,
          isrTimings.timeInSeconds);
 
  fonts.setTextColor(defaultPaper, GREY);  
  fonts.setFont(&HOTSMALL);
  uint8_t width = (textWidth(msg) / 4) * 4; // Polish off any slight font width weirdness.
  uint8_t margin = (TFT_WIDTH - width) / 2;
  fonts.setBufferDimensions(TFT_WIDTH, 18);
  fonts.print(margin, TFT_HEIGHT - 16, msg);
  fonts.setTextColor(defaultInk, defaultPaper); 
  delete[] msg;
}

void Graph::draw(const quadrilateral_t* quad, const colours_t &ink, const colours_t &outline)
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

void Graph::rotate(quadrilateral_t* quad, const int16_t &rotation)
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

void Graph::translate(triangle_t* triangle, const coordinates_t &cords)
{
  for (auto i{0}; i < 4; ++i)
  {
    triangle->cords[i].X += cords.X;
    triangle->cords[i].Y += cords.Y;
  }
}

void Graph::translate(quadrilateral_t* polygon, const coordinates_t &cords)
{
  for (auto i{0}; i < 4; ++i)
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