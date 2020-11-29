
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

#ifndef __HOTSTUFF_ANNUCIATOR
#define __HOTSTUFF_ANNUCIATOR

void Annuciator::annunciators(void)
{
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

void Annuciator::checkAlarm(void)
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

void Annuciator::checkButton(void)
{
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    STOP
  }

  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    if (button.timer != 0)
    {
 
      if (button.timer < SHORTPRESS) // button.shortPress)
      {
        flags.clear(FROST | DAMP | DRY | OVERTEMP);
        button.timer = 0;
        digitalWrite(ALARM_PIN, LOW);
      }
    }
  }
  else
  {
    if (! button.timer)
    {
      button.timer = 1;
    }
    else
    {
      button.timer += 1;
    }
  }

  if (button.timer > LONGPRESS)
  {
    // Toggle metric/imperial
    (flags.flip(METRIC) );
    screen.fillRect(LOW_TEMP_X,       LOW_TEMP_Y,   72,  8,     defaultPaper);
    screen.fillRect(LEFTMARGIN - 2, LOWHUMID_Y + 12, 20, 40, defaultPaper);
    button.timer = 0;

    temperature.showReadings();
#ifndef TOPLESS
    chart.drawGraphScaleMarks();
#endif
  }
}

void Annuciator::sensorFailed(UniversalDHT::Response response)
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

#endif