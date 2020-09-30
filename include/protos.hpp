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

void annunciators(void);
void setAlarm(uint8_t);
void clearAlarm(uint8_t);
bool testAlarm(uint8_t);

void printMessage(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t);
void printMessage(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t);
void printMessage(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, const char *);
void printMessage(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t);
void printMessage(uint16_t, uint16_t, uint8_t, uint8_t);
void printMessage(uint8_t, uint8_t);
void printMessage(const char * pText, uint16_t, uint16_t);
void printMessage(const char * pText, uint16_t);
void printMessage(uint8_t);
void printNumber(uint16_t, uint16_t, uint8_t, uint8_t, float);
void printNumber(uint16_t, uint16_t, uint8_t, uint8_t, float, bool);
void printLeadingZero(uint8_t, uint8_t);
void displayGraph(void);
void drawMainAxes(void);
void drawReticles(void);
void takeReadings(void);
void doHeatIndex(float, float);
void flashText(uint8_t, uint8_t, uint8_t, uint16_t, uint16_t);
void unsafeTempWarnings(float);
void drawGraphLines(void);
void labelTemperature(void);
void postMainTemperature(float, uint16_t, uint16_t, uint16_t);
void blankArea(uint16_t, uint8_t, uint16_t, uint8_t);
void sensorFailed(UniversalDHT::Response);
void initGraphPoints(void);
void initGraph(void);
void initMainScreen(void);
void setup(void);
void loop(void);
void checkHumidityCondtions(void);
void checkTemperatureConditions(void);
void checkAlarm(void);
void checkButton(void);
void drawHeadingTexts(void);
void drawUnits(void);
void showReadings(void);
void postTemperatures(void);
void showUptime(void);
void resetTextColour(void);
void drawRadials(void);
float magnusDewpoint(float, float);
uint8_t centerText(String, uint8_t);
uint16_t colourValue(float, uint16_t, uint16_t, uint16_t);