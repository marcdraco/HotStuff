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
void setAlarmFlag(uint8_t flag);
void clearAlarmFlag(uint8_t flag);
bool testAlarm(uint8_t flag);
void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t rotation, uint8_t text, uint8_t text2 );
void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t rotation, uint8_t text);
void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, const char * pText);
void printMessage(uint16_t X, uint16_t Y, uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t text);
void printMessage(uint16_t foregroundColour, uint16_t backgroundColour, uint8_t characterSize, uint8_t text);
void printMessage(uint8_t characterSize, uint8_t text);
void printMessage(const char * pText, uint16_t col);
void printMessage(uint8_t text);
void printNumber(uint16_t foregroundColour, uint16_t backgroundColour, uint8_t largeCharacterSize, uint8_t smallCharacterSize, float number);
void printNumber(uint16_t foregroundColour, uint16_t backgroundColour, uint8_t largeCharacterSize, uint8_t smallCharacterSize, float number, bool metric);
void printLeadingZero(uint8_t value);
void displayGraph(void);
void drawMainAxes(void);
void drawReticles(void);
void takeReadings(void);
void doHeatIndex(float T, float H);
void flashText(uint8_t message, uint8_t X, uint8_t Y, uint16_t colour1, uint16_t colour2);
void unsafeTempWarnings(float apparentTemperature);
void drawGraphLines(void);
void labelTemperature(void);
void postMainTemperature(float value, uint16_t lowerLimit, uint16_t upperLimit, uint16_t guard);
void blankArea(uint16_t X, uint8_t Y, uint16_t width, uint8_t height);
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
uint8_t centerText(String text, uint8_t charWidth);
uint16_t colourValue(float value, uint16_t lowerLimit, uint16_t upperLimit, uint16_t guard);