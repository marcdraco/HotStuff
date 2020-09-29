/*
  Copyright 2020, Marc Draco & Daniel Melvin & Garrie
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
*/



#include <Arduino.h>
#include "UniversalDHT.hpp"        // @winlinvip's DHT22 library functions modified by Tim Harper
#include <math.h>
#include <string.h>
#include <Wire.h>
#include <Adafruit_GFX.h>     // Core graphics library by AdaFruit
#include <MCUFRIEND_kbv.h>    // David Prentice's Hardware-specific library - your shield might vary
#include "lcd.h"
#include <protos.hpp>

/*
   The following constants set up various values to calculate the graphing functions and should
   be fairly self-explanatory. As set here, the chart covers temperatures from 0 to 50C
   and RH (humidity.reading) across the whole range. The DHT22 is good for -40 to 80C but this
   device is for humans at work or elderly so is set for those temperature ranges.
   Compare the DHT22 information sheet for complete specifications.
*/

void setup(void)
{
  Serial.begin(9600);
  uint16_t ID = screen.readID();
  if (ID == 0xD3D3)
  {
    ID = 0x9481; //force ID if write-only screen
  }

  screen.begin(ID);
  screen.setRotation(DEFAULT); // possible values 0-3 for 0, 90, 180 and 270 degrees rotation
  screen.fillScreen(text.colour.defaultBackground);

  pinMode(BUTTON_PIN, INPUT);         // Our last spare pin (phew) is going to be dual purpose!
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Hold it high so it goes active LOW when pressed.
  pinMode(ALARM_PIN, OUTPUT);         // This is usually pin 13 (the board LED)
  pinMode(DHT22_POWER, OUTPUT);       // cheeky way to power the DHT22, but it only requires 1.5mA
  digitalWrite(DHT22_POWER, HIGH);    // and saves wiring from the ICSP ports on UNO with a TFT shield
  pinMode(DHT22_DATA, INPUT_PULLUP);  // keep the data pin from just hanging around

  noInterrupts();                       // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = UPDATER;                      // pre-calculated re-read time.
  TCCR1B |= (1 << CS10) | (1 << CS12);  // 1024 prescaler (see header)
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  interrupts();                         // enable all interrupts

  if (temperature.reading == -1)
  {
    screen.setTextSize(text.large);
   { 
    delay(2500);                                    // wait for it to catch its breath or it will whinge and crash.
    dht22.read(&humidity.reading, &temperature.reading);
    #ifndef TOPLESS
    blankArea(0, 0, tft.width, tft.height);
   }
    #endif
  }
  #ifndef TOPLESS
  
  screen.setRotation(tft.rotateDefault);
  
  initGraphPoints();
  initMainScreen();
  
    #ifdef CLOCKWISE
    drawRadials();
    #endif
    
  #endif
}

void drawRadials(void)
{
  uint16_t theta = 0;

  for (theta = 0; theta < 360; theta += 8)
  {
    float x = cos(radians(theta));
    float y = sin(radians(theta));
    
    uint16_t innerX = x * radials.innerRadius + radials.tRadialX;
    uint16_t innerY = y * radials.innerRadius + radials.tRadialY;
    uint16_t outerX = x * radials.outerRadius + radials.tRadialX;
    uint16_t outerY = y * radials.outerRadius + radials.tRadialY;
    screen.drawLine(innerX, innerY, outerX, outerY, GREEN);
    screen.drawLine(innerX + radials.hRadial, innerY, outerX + radials.hRadial, outerY, RED);
  } 
}

void loop()
{
  /*
    Open by checking if it's time to take the current readings from the DHT22
    the "timeToRead" variable is incremented by the interupt service routine
    once every second.
    After three seconds we take a new read. Use a larger int if you prefer.
    Area temperatures don't vary much unless the sensor is in a drafty corner!
  */

  if (isrTimings.timeToRead == 3)
  {
    takeReadings();
    showReadings();
  }

showUptime();
checkAlarm();
annunciators();
checkButton();
}

void annunciators(void)
{
  // Dry air, damp air and frost annunciator

  if (testAlarm(alarm.frost) == true)
  {
    printMessage(text.frostWarnX, text.frostWarnY, text.colour.defaultForeground, text.colour.defaultBackground, text.small, messages.frost);
  }
  else
  {
    printMessage(text.frostWarnX, text.frostWarnY, text.colour.defaultBackground, text.colour.defaultBackground, text.small, messages.frost);
  }

  if (testAlarm(alarm.damp) == true)
  {
    printMessage(text.mouldWarnX, text.mouldWarnY, text.colour.defaultForeground, text.colour.defaultBackground, text.small, messages.damp);
  }
  else
  {
    printMessage(text.mouldWarnX, text.mouldWarnY, text.colour.defaultBackground, text.colour.defaultBackground, text.small, messages.damp);
  }

  if (testAlarm(alarm.dry) == true)
  {
    printMessage(text.dryWarnX, text.dryWarnY, text.colour.defaultForeground, text.colour.defaultBackground, text.small, messages.dry);
  }
  else
  {
    printMessage(text.dryWarnX, text.dryWarnY, text.colour.defaultBackground, text.colour.defaultBackground, text.small, messages.dry);
  }
}

void setAlarmFlag(uint8_t flag)
{
  switch (flag)
  {
    case alarm.frost:
      alarm.semaphore = alarm.semaphore | alarm.frost;
      break;

    case alarm.damp:
      alarm.semaphore = alarm.semaphore | alarm.damp;
      break;

    case alarm.dry:
      alarm.semaphore = alarm.semaphore | alarm.dry;
      break;

    case alarm.overTemp:
      alarm.semaphore = alarm.semaphore | alarm.overTemp;
      break;
  }
}

void clearAlarmFlag(uint8_t flag)
{
  switch (flag)
  {
    case alarm.frost:
      // bitwise AND (&) with the inverse of the flag using XOR (^) 0xFF
      alarm.semaphore = alarm.semaphore & (alarm.frost ^ 0xFF);
      break;

    case alarm.damp:
      alarm.semaphore = alarm.semaphore & (alarm.damp ^ 0xFF);
      break;

    case alarm.dry:
      alarm.semaphore = alarm.semaphore & (alarm.dry ^ 0xFF);
      break;

    case alarm.overTemp:
      alarm.semaphore = alarm.semaphore & (alarm.overTemp ^ 0xFF);
      break;
  }
}

bool testAlarm(uint8_t flag)
{
  return (alarm.semaphore & flag);
}

void displayGraph(void)
{
  if (graph.updateGraphReadings == false)
  {
    return;
  }
  graph.updateGraphReadings = false;

  uint16_t xPosition = 0;             // These values can get larger than 255 so we need 16 bits
  uint8_t index      = 0;

  drawReticles();
  // convert the temperature and humidity.reading readings into something that scales to the chart.
  // the FSD is 100 points giving a temp range of 0 - 50c (32 - 122f)
  // the first few lines just wall off temperatures from under freezing and above 50.

  if (temperature.cumulativeMovingAverage > 50)
  {
    temperature.Y = (graph.Y + graph.height) - 100;
  }
  else if (temperature.cumulativeMovingAverage < 0)
  {
    temperature.Y = (graph.Y + graph.height);
  }
  else
  {
    temperature.Y = (graph.Y + graph.height) - (round(temperature.cumulativeMovingAverage) * 2);
  }

  humidity.Y = (graph.Y + graph.height) - round(humidity.cumulativeMovingAverage);

  //put the latest readings at the end of the pipe.
  humidity.pipe[graph.width    - 1] = humidity.Y;
  temperature.pipe[graph.width - 1] = temperature.Y;

  // clear the old lines
  for (index = 2; index < graph.width; index ++)
  {
    xPosition = index + graph.X;
    screen.drawLine(xPosition - 1, humidity.pipe[index    - 2], xPosition, humidity.pipe[index - 1],    BLACK);
    screen.drawLine(xPosition - 1, temperature.pipe[index - 2], xPosition, temperature.pipe[index - 1], BLACK);
  }

  //draw in new ones (this is supposed to reduce flashing but it's "meh")
  for (index = 1; index < graph.width; index ++)
  {
    xPosition = index + graph.X;

    screen.drawLine(xPosition - 1, humidity.pipe[index    - 1],    xPosition, humidity.pipe[index],    humidity.trace);
    screen.drawLine(xPosition - 1, temperature.pipe[index - 1],    xPosition, temperature.pipe[index], temperature.trace);
    temperature.pipe[index - 1] = temperature.pipe[index];
    humidity.pipe[index - 1]    = humidity.pipe[index];
    drawMainAxes();
  }
}

void drawMainAxes(void)
{
  screen.drawFastHLine(graph.X,     graph.Y    + graph.FSD, graph.width, text.colour.defaultForeground);
  screen.drawFastVLine(graph.X - 1, graph.Y,     graph.FSD, text.colour.defaultForeground);
  screen.drawFastVLine(graph.X   +  graph.width, graph.Y,   graph.FSD, text.colour.defaultForeground);
}

void drawReticles(void)
{
  uint8_t index      = 0;
  uint16_t xPosition = 0;             // These values can get larger than 255 so we need 16 bits
  uint8_t humidityMax    = (graph.Y + graph.height) - (humidity.maxComfort + humidity.guard);
  uint8_t humidityMin    = (graph.Y + graph.height) - (humidity.minComfort - humidity.guard);
  uint8_t temperatureMax = (graph.Y + graph.height) - ((temperature.maxComfort + temperature.guard) * 2);
  uint8_t temperatureMin = (graph.Y + graph.height) - ((temperature.minComfort - temperature.guard) * 2);

  for (index = 1; index < graph.width; index++)     // draws vertical blanking strokes and reticules
  {
    xPosition  = index + graph.X;

    if (index % (graph.width / 8) == 0)              // seven vertical divisions
    {
      screen.drawFastVLine(xPosition , graph.Y, graph.height, text.colour.reticleColour);
    }
  }

  for (index = 0; index < graph.height + 20; index = index + 20)
  {
    screen.drawFastHLine(graph.X, graph.Y + index, graph.width, text.colour.reticleColour);
  }

#ifdef SHOW_BANDS
  for (index = 1; index < graph.width; index += 10)     // draws vertical blanking strokes and reticules
  {
    screen.drawFastHLine(graph.X + index,    humidityMax, 3, BROWNISH);
    screen.drawFastHLine(graph.X + index,    humidityMin, 3, BROWNISH);
    screen.drawFastHLine(graph.X + index, temperatureMax, 3, PURPLEISH);
    screen.drawFastHLine(graph.X + index, temperatureMin, 3, PURPLEISH);
  }
#endif
}
 
/*
   A slightly hacky way of keeping the display tidy
   by sticking a leading zero in front of the times
*/
void printLeadingZero(uint8_t value)
{
  if (value < 10)
  {
    screen.print(F("0"));
  }
  screen.print(value);
}

/*
   Approximate the "Heat index" per Steadman 1994. While the dry bulb temperature
   may be well within safe limits for humans, the addition of humidity.reading
   prevents our bodies from effectively evaporatively cooling with the result
   that our internal temperature rises - and the different of just a few degrees
   C can cause fatigue, aggression and eventually heat stroke and possibly death.
   These figures assume the person is doing mildly stressful work such as housework
   Workers in more extreme physical labour will suffer faster and vice versa.

   26–32 °C Caution: fatigue is possible with prolonged exposure and activity.
            Continuing activity could result in heat cramps.
   32–41 °C Extreme caution: heat cramps and heat exhaustion are possible.
            Continuing activity could result in heat stroke.
   41–54 °C Danger: heat cramps and heat exhaustion are likely.
            Heat stroke is probable with continued activity.
   > 54 °C  Extreme danger: heat stroke is imminent.
*/

float heatIndex(float T, float R)
{
  /*
      Check the "heat index" there's a very wide range here
      but the idea is to broadly test to ensure that the
      current environment is not too hot for people to live
      and work. High heat and humidity.reading can cause serious
      illness and even (rarely) death if the person is
      not removed. This is becoming a much more widespread
      problem as our climate changes.

    Wikipedia https://en.wikipedia.org/wiki/Heat_index
    Steadman's 1994 approximation for heat in given humidity.reading

  */
  const float c1 = -8.78469475556;
  const float c2 =  1.61139411;
  const float c3 =  2.33854883889;
  const float c4 = -0.14611605;
  const float c5 = -0.012308094;
  const float c6 = -0.0164248277778;
  const float c7 =  0.002211732;
  const float c8 =  0.00072546;
  const float c9 = -0.000003582;
  return (c1 + (c2 * T) + (c3 * R) + (c4 * T * R) + (c5 * (T * T)) + (c6 * (R * R)) + (c7 * (T * T) * R) + (c8 * T * (R * R)) + (c9 * (T * T) * (R * R)));
}

float magnusDewpoint(float RH, float T)
{
  // https://en.wikipedia.org/wiki/Dew_point
  // Magnus dew point constants

  const double a = 17.62;     
  const double b = 243.12;  
  double c = (a * T) / (b + T);
  double r = log(RH/100);
  
  return (float) b * (r + c) / (a - (r + c));
}

void takeReadings(void)
{
   UniversalDHT::Response reading = dht22.read(&humidity.reading, &temperature.reading);
  
  /*
    check that the DHT22 didn't develop a fault or break
    during since the last read. If it did, we're going
    to stop work and report a service fault giving the
    failure time so engineers can figure out how reliable
    these devices are in their environment.
  */
  if (reading.error != 0)
  { 
    sensorFailed(reading);
  }

temperature.reading = temperature.reading + temperature.correction ;
humidity.reading = humidity.reading + humidity.correction;

isrTimings.timeToRead = 0;

#ifdef DEBUG_OVERTEMP_ALARM
  temperature.reading = DEBUG_OVERTEMP_ALARM;
#endif

#ifdef DEBUG_EXCESS_DAMP_ALARM
  humidity.reading = DEBUG_EXCESS_DAMP_ALARM;
#endif

#ifdef DEBUG_LOW_TEMP_ALARM
  temperature.reading = DEBUG_LOW_TEMP_ALARM;
#endif

#ifdef DEBUG_FROST_ALARM
  temperature.reading = DEBUG_FROST_ALARM;
#endif

#ifdef DEBUG_DRY_AIR_ALARM
  humidity.reading = DEBUG_DRY_AIR_ALARM;
#endif


  // cumulative moving averages are a form of mean that doesn't need to track every single value
  // using these avoids little odd spikes from throwing the graph and smooths it out too.

  humidity.cmaCounter = humidity.cmaCounter + 1;
  humidity.cumulativeMovingAverage = humidity.cumulativeMovingAverage + ((humidity.reading - humidity.cumulativeMovingAverage) / humidity.cmaCounter);

  temperature.cmaCounter = temperature.cmaCounter + 1;
  temperature.cumulativeMovingAverage = temperature.cumulativeMovingAverage + ((temperature.reading - temperature.cumulativeMovingAverage) / temperature.cmaCounter);

  // Note the instant we register "freezing" we set the alarm
  // this is by design, it's not a bug!
  if (temperature.reading <= 1.0 && alarm.silenced == false)   // 1.0 degrees (C) to allow for errors in the sensor.
  {
    setAlarmFlag(alarm.frost);
  }

  // Note the watershed is 4C and the AVERAGE needs go above that
  // this is by design, it's not a bug!
  if (temperature.cumulativeMovingAverage > temperature.frostWatershed)
  {
    clearAlarmFlag(alarm.frost);
    if (alarm.semaphore == 0)
    {
      alarm.silenced = true;
    }
  }

  if (humidity.cumulativeMovingAverage > humidity.dampAirWatershed)
  {
    setAlarmFlag(alarm.damp);
  }

  if (humidity.cumulativeMovingAverage < humidity.dryAirWatershed)
  {
    setAlarmFlag(alarm.dry);
  }

  if (humidity.cumulativeMovingAverage <= humidity.dampAirWatershed)
  {
    clearAlarmFlag(alarm.damp);
    if (alarm.semaphore == 0)
    {
      alarm.silenced = true;
    }
  }

  if (humidity.cumulativeMovingAverage >= humidity.dryAirWatershed)
  {
    clearAlarmFlag(alarm.dry);
    if (alarm.semaphore == 0)
    {
      alarm.silenced = true;
    }
  }

  if (isrTimings.timeInSeconds == 0) // this ticks every minute
  {
    graph.updateGraphReadings = true;
  }

  if (isrTimings.timeInSeconds == 0 && isrTimings.timeInMinutes == 0) // this ticks every hour
  {
    temperature.cmaCounter = 0;
    humidity.cmaCounter    = 0;
  }
}

/*
   Produce warnings in the lower half of the screen to stop or reduce activity
   for health and safety. Sedentary workers (or just relaxing on the beach) we
   are able to tolerate higher apparent temperatures because our bodies are
   not producing as much heat.
*/
 
void doHeatIndex(float T, float H)
{

  // Note that the following temperatures are giving in degrees C for simplicity in coding.

  int8_t apparentTemperature = 0;

  apparentTemperature = (int8_t) heatIndex(T, H);


  // heat index routine only works reliably(ish) for temps >26 celcius and RH >= 40%
  if ((apparentTemperature < 26) || T < 26 || H < 40)
  {
    tft.warnDanger = false;
    return;
  }

  // This flags up that the lower half of the display is set to warning!
  tft.warnDanger = true;

#ifndef TOPLESS
  blankArea(0, 100, tft.width, tft.height);
#endif

  if (apparentTemperature >= 26 && (apparentTemperature <= temperature.caution))
  {
    flashText(messages.caution, centerText(messages.msg[messages.caution], text.baseWidth * text.large), tft.height / 2, text.colour.defaultForeground, text.colour.defaultBackground);
    ewt(apparentTemperature);
  }

  if (apparentTemperature >= temperature.caution && apparentTemperature <= temperature.warning)
  {
    flashText(messages.xcaution, centerText(messages.msg[messages.xcaution], text.baseWidth * text.large), tft.height / 2, YELLOW, text.colour.defaultBackground);
    ewt(apparentTemperature);
  }

  if (apparentTemperature >= temperature.warning  && apparentTemperature <= temperature.risk)
  {
    flashText(messages.danger, centerText(messages.msg[messages.danger], text.baseWidth * text.large), tft.height / 2, RED, text.colour.defaultBackground);
    ewt(apparentTemperature);
  }
  if (apparentTemperature >= temperature.risk)
  {
    flashText(messages.xdanger, centerText(messages.msg[messages.xdanger], text.baseWidth * text.large), tft.height / 2, RED, YELLOW);
    ewt(apparentTemperature);
  }
}

void ewt(float apparentTemperature)
{
  String message = (F("Working temperature:         "));  // allocate sufficient space for concatenation
  message = (F("Working temperature:"));
  screen.setTextSize(text.large);

  if (temperature.useMetric == true)
  {
    printMessage(text.leftMargin, text.heatIndexY + 60, text.colour.defaultForeground, text.colour.defaultBackground, text.medium, messages.working);
    screen.print(apparentTemperature);
    printMessage(messages.c);
  }
  else
  {
    printMessage(text.leftMargin, text.heatIndexY + 60, text.colour.defaultForeground, text.colour.defaultBackground, text.medium, messages.working);
    screen.print(round(apparentTemperature * 1.8 + 32));
    printMessage(messages.f);
  }
}

void sensorFailed(UniversalDHT::Response response)
{
  #ifdef SENSOR_MISSING_OR_BUSTED
    return;
  #endif
  screen.fillRect(0, 0, tft.width, tft.height, text.colour.defaultBackground);
  const char * failed =  " -Sensor Fail-";
  const char * times =  "             Y  M  D  H";
  const char * age =  "Sensor age: ";
  String message;

  printMessage(text.leftMargin, 80, RED, text.colour.defaultBackground, text.large, failed);
  printMessage(text.leftMargin, 120, RED, text.colour.defaultBackground, text.small, times);
  printMessage(text.leftMargin, 140, RED, text.colour.defaultBackground, text.small, age);

  fail.failTime[fail.Y] = isrTimings.timeInYears;
  fail.failTime[fail.W] = isrTimings.timeInWeeks;
  fail.failTime[fail.D] = isrTimings.timeInWeeks;
  fail.failTime[fail.H] = isrTimings.timeInHours;

  printLeadingZero(fail.failTime[fail.Y]);
  screen.print(F(":"));
  printLeadingZero(fail.failTime[fail.W]);
  screen.print(F(":"));
  printLeadingZero(fail.failTime[fail.D]);
  screen.print(F(":"));
  printLeadingZero(fail.failTime[fail.H]);

  // High 8bits are time duration (not shown)
  // Low 8bits are error code.
  // @see https://github.com/winlinvip/SimpleDHT/issues/25

  screen.setCursor(text.leftMargin, 160);
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

#ifndef TOPLESS

void labelTemperature(void)
{
  if (temperature.useMetric == true)
  {
    printMessage(text.axisYPosition, text.leftAxisLabel, text.colour.defaultForeground, text.colour.defaultBackground, text.small, tft.rotatePortrait, messages.temperatureScale, messages.c);
  }
  else
  {
    printMessage(text.axisYPosition, text.leftAxisLabel, text.colour.defaultForeground, text.colour.defaultBackground, text.small, tft.rotatePortrait, messages.temperatureScale, messages.f);
  }
  drawUnits();
}

void initMainScreen(void)
{
  drawGraphLines();
  drawHeadingTexts();
  screen.fillRect(0, text.uptimeTimeY, tft.width, text.small * text.baseHeight + 2, GREY); //just that little Uptime display, a nod to *nix.
}

void blankArea(uint16_t X, uint8_t Y, uint16_t width, uint8_t height)
{
  screen.fillRect(X, Y, width, height, text.colour.defaultBackground);
}

void initGraph(void)
{
  if (tft.graphActive == true)
  {
    return;
  }
  blankArea(0, 90, tft.width, tft.height);
  tft.graphActive = true;
}

void initGraphPoints(void)
{
  uint8_t index;

 // This only runs once to set clear everything in case of memory junk
 // so we know not to plot these until a real one is recorded
 // No point storing real numbers when single a byte (Y-coord) will do!
  for (index = 0; index < graph.width; index++)
  {
    humidity.pipe[index]    = (graph.Y + graph.height);
    temperature.pipe[index] = (graph.Y + graph.height);
  }
}

void drawHeadingTexts(void)
{
  //printMessage(text.leftMargin, text.temperatureY, text.colour.defaultForeground, text.colour.defaultBackground, text.large, messages.temperature);
  //printMessage(text.leftMargin, text.humidityY,    text.colour.defaultForeground, text.colour.defaultBackground, text.large, messages.humidity);
  drawUnits();
  screen.setCursor(text.percentX, text.humidityY);
  screen.print(F(" %"));
}

void drawUnits(void)
{
  screen.setTextSize(text.small);
  screen.setCursor(text.degreeSymbolX, text.degreeSymbolY);
  screen.print(F("o"));         // poor man's degree symbol

  screen.setTextSize(text.large);
  screen.setCursor(text.scaleX, text.temperatureY);
  if (temperature.useMetric == true)
  {
    printMessage(messages.c);
  }
  else
  {
    printMessage(messages.f);
  }
}

void drawGraphLines(void)
{
  labelTemperature();
  printMessage(text.axisYPosition, 
        tft.width - (text.small * text.baseWidth),  
        text.colour.defaultForeground, 
        text.colour.defaultBackground, 
        text.small, 
        tft.rotatePortrait, 
        messages.humidityScale);

  // Insert the scale and graduation marks

  for (uint8_t index = 0; index < 120; index = index + 20)
  {
    screen.setCursor(graph.X - 22, (graph.Y + graph.height - 4) - index);

    if (temperature.useMetric == true)
    {
      if (index < 10)
      {
        screen.print(F(" "));
      }
      screen.print(index / 2);
    }
    else
    {
      screen.print(round((index / 2) * 1.8 + 32));
    }

    screen.setCursor(graph.X + graph.width + 5, (graph.Y + graph.height - 4) - index);

    if (index < 10)
    {
      screen.print(F(" "));
    }

    if (index < 100)
    {
      screen.print(F(" "));
    }
    screen.print(index);
  }
}

#endif

void checkAlarm(void)
{
  if (alarm.silenced == false)
  {
    digitalWrite(ALARM_PIN, LOW);
  }

  if (testAlarm(alarm.all) == true)
  {
    if (tft.flashing)
    {
      digitalWrite(ALARM_PIN, HIGH);
    }
    else
    {
      digitalWrite(ALARM_PIN, LOW);
    }
  }
}

void checkButton(void)
{
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    if (button.timer != 0)
    {
      if (button.timer < button.shortPress) // button.shortPress)
      {
        alarm.silenced = true;
        alarm.semaphore = 0;
        button.timer = 0;
      }
    }
  }
  else
  {
    if (button.timer == 0)
    {
      button.timer = 1;
    }
    else
    {
      button.timer += 1;
    }
  }

  if (button.timer > button.longPress)
  {
          // Toggle metric/imperial
          (temperature.useMetric = !temperature.useMetric);
          screen.fillRect(text.lowTempX,       text.lowTempY,   72,  8,     text.colour.defaultBackground);
          screen.fillRect(text.leftMargin - 2, text.lowHumidY + 12, 20, 40, text.colour.defaultBackground);
          button.timer = 0;

          showReadings();
          #ifndef TOPLESS
            drawUnits();
            drawGraphLines();
          #endif
  }
}

void showReadings(void)
{
  uint16_t colour;
  #ifndef TOPLESS
  displayGraph();
  #endif

  doHeatIndex(temperature.reading, humidity.reading);

  temperature.previousRead = temperature.reading;
  humidity.previousRead    = humidity.reading;

  if (temperature.reading < temperature.lowestReading)
  {
    temperature.lowestReading = temperature.reading;
  }

  if (temperature.reading > temperature.highestReading)
  {
    temperature.highestReading = temperature.reading;
  }

  if (humidity.reading < humidity.lowestReading)
  {
    humidity.lowestReading = humidity.reading;
  }

  if (humidity.reading > humidity.highestReading)
  {
    humidity.highestReading = humidity.reading;
  }


  screen.setFont(&LCD1414pt7b);

  screen.setCursor(text.bigReadXTemp, 60);
  colour = colourValue((float)temperature.reading, temperature.minComfort, temperature.maxComfort, temperature.guard);
  printNumber(colour, text.colour.defaultBackground, 0, 0, temperature.reading, temperature.useMetric);
/*
  screen.setCursor(text.bigReadXHumid + text.baseWidth * text.small, text.humidityY);
  colour = colourValue((float)humidity.reading, humidity.minComfort, humidity.maxComfort, humidity.guard);
  printNumber(colour, text.colour.defaultBackground, text.small, text.small, humidity.reading, true);

  screen.setCursor(text.lowTempX, text.lowTempY);
  printNumber(text.colour.defaultForeground, text.colour.defaultBackground, text.small, text.small, temperature.lowestReading, temperature.useMetric);
  printMessage(messages.slash);
  printNumber(text.colour.defaultForeground, text.colour.defaultBackground, text.small, text.small, temperature.highestReading, temperature.useMetric);
*/
  screen.setFont(NULL);

  screen.setTextSize(text.small);
  screen.setCursor(text.lowHumidX-60, text.lowHumidY);
  screen.print(magnusDewpoint(humidity.reading, temperature.reading));
 
  screen.setTextSize(text.small);
  screen.setCursor(text.lowHumidX, text.lowHumidY);
  screen.print(humidity.lowestReading, 1);
  printMessage(messages.slash);
  screen.print(humidity.highestReading, 1);
}

uint16_t colourValue(float value, uint16_t lowerLimit, uint16_t upperLimit, uint16_t guard)
{
  if (value < lowerLimit - guard)
  {
    return BLUE;
  }
  else if (value > upperLimit + guard)
  {
    return RED;
  }

  return text.colour.defaultForeground;
}

void showUptime(void)
{
  /*
    This block produces the uptime data at the base
    of the screen as a quick check that the machine
    hasn't suffered a power loss.
  */

  printMessage(text.leftMargin, tft.errorY, text.colour.defaultBackground, GREY, text.small, messages.uptime);
  screen.print(F(""));

  screen.print(isrTimings.timeInYears);
  screen.print(F(" years, "));

  screen.print(isrTimings.timeInWeeks);
  screen.print(F(" Weeks, "));

  screen.print(isrTimings.timeInDays);
  screen.print(F(" Days, "));

  printLeadingZero(isrTimings.timeInHours);
  screen.print(F(" Hours"));

  screen.print(F(":"));
  printLeadingZero(isrTimings.timeInMinutes);

  screen.print(F(":"));
  printLeadingZero(isrTimings.timeInSeconds);

}

void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t rotation, uint8_t text, uint8_t text2 )
{
  screen.setRotation(rotation);
  printMessage(X, Y, foregroundColour, backgroundColour, characterSize, text);
  printMessage(text2);
  screen.setRotation(tft.rotateDefault);
}

void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t rotation, uint8_t text)
{
  screen.setRotation(rotation);
  printMessage(X, Y, foregroundColour, backgroundColour, characterSize, text);
  screen.setRotation(tft.rotateDefault);
}

void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, const char * pText)
{
  screen.setCursor(X, Y);
  screen.setTextColor(foregroundColour, backgroundColour);
  screen.setTextSize(characterSize);
  printMessage(pText, foregroundColour);
}

void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t text)
{
  screen.setCursor(X, Y);
  screen.setTextColor(foregroundColour, backgroundColour);
  screen.setTextSize(characterSize);
  printMessage(text);
}

void printMessage(uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t text)
{
  screen.setTextColor(foregroundColour, backgroundColour);
  screen.setTextSize(characterSize);
  printMessage(text);
}

void printMessage(const char * pText, uint16_t col)
{
  screen.setTextColor(col, text.colour.defaultBackground);
  screen.print(pText);
}

void printMessage(uint8_t text)
{
  screen.print(messages.msg[text]);
}

void printNumber(uint16_t foregroundColour, uint16_t backgroundColour, uint8_t largeCharacterSize, uint8_t smallCharacterSize, float number, bool metric)
{
  if (number < 0) 
  {
    screen.setTextColor(foregroundColour, backgroundColour);
    screen.setTextSize(largeCharacterSize);
    printMessage("ICE ", RED);
    return;
  }

  if (metric == false)
  {
    number = number * 1.8 + 32;
  }
  printNumber(foregroundColour, backgroundColour, largeCharacterSize, smallCharacterSize, number);
}

void printNumber(uint16_t foregroundColour, uint16_t backgroundColour, uint8_t largeCharacterSize, uint8_t smallCharacterSize, float number)
{
  double fraction;
  double integer;

  screen.setTextColor(foregroundColour, backgroundColour);
  screen.setTextSize(largeCharacterSize);

  if (number >= 0 && number < 100)
  {
    screen.print(" ");
  }

  if (number >= 0 && number < 10)
  {
    screen.print(" ");
  }

  fraction = modf(number, &integer);
  screen.print(integer,0);
  
  modf(fraction * 10, &integer);
  screen.setTextSize(smallCharacterSize);
  screen.print(".");
  screen.print(integer,0);
}

void flashText(uint8_t message, uint8_t X, uint8_t Y, uint16_t colour1, uint16_t colour2)
{
  if (tft.flashing == true)
  {
    printMessage(X, Y, colour1, colour2, text.large, message);
  }
  else
  {
    printMessage(X, Y, colour2, colour1, text.large, message);
  }
}

uint8_t centerText(String text, uint8_t charWidth)
{
  return ((tft.width - (text.length() * charWidth)) / 2);
}

ISR(TIMER1_OVF_vect)    // interrupt service routine for overflow
{
  TCNT1 = UPDATER;     // preload timer

  isrTimings.timeToRead ++;

  tft.flashing = !(tft.flashing); // flip the boolean for flashing items

  isrTimings.timeInSeconds = isrTimings.timeInSeconds + 1;  // this is determined by the ISR calculation at the head of the sketch.

  if (isrTimings.timeInSeconds == 60)
  {
    isrTimings.timeInSeconds = 0;
    isrTimings.timeInMinutes++;

    if (isrTimings.timeInMinutes == 60)
    {
      isrTimings.timeInMinutes = 0;
      isrTimings.timeInHours++;

      if (isrTimings.timeInHours == 24)
      {
        isrTimings.timeInHours = 0;
        isrTimings.timeInDays++;

        if (isrTimings.timeInDays == 7)
        {
          isrTimings.timeInWeeks = 0;
          isrTimings.timeInWeeks++;

          if (isrTimings.timeInWeeks == 52)
          {
            isrTimings.timeInWeeks = 0;
            isrTimings.timeInYears++;
          }
        }
      }
    }
  }
}
