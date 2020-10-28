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

/*
  Thanks to Steve Wood (ebay: audioSpectrumAnalysers) for the serial programmer.
  3.5" TFT shield supplied by A-Z Delivery via Amazon.  
*/

#ifndef __DRACO_HOTSTUFF_H
#define __DRACO_HOTSTUFF_H

#include <Arduino.h>
#include "types.hpp"

// remove this line to have the unit read in fahrenheit
// #define USE_METRIC                   
 
// Many (but maybe not all) non-AVR board installs define macros
// for compatibility with existing PROGMEM-reading AVR code.
// Do our own checks and defines here for good measure...

#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char*)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

inline fixedgfxglyph_t* pgm_read_glyph_ptr(const fixedgfxfont_t*gfxFont, uint8_t c) 
{
#ifdef __AVR__
  return &(((fixedgfxglyph_t *)pgm_read_pointer(&gfxFont->glyph))[c]);
#else
  // expression in __AVR__ section may generate "dereferencing type-punned
  // pointer will break strict-aliasing rules" warning In fact, on other
  // platforms (such as STM32) there is no need to do this pointer magic as
  // program memory may be read in a usual way So expression may be simplified
  return gfxFont->glyph + c;
#endif //__AVR__
}

inline uint8_t* pgm_read_bitmap_ptr(const fixedgfxfont_t* gfxFont) {
#ifdef __AVR__
  return (uint8_t*) pgm_read_pointer(&gfxFont->bitmap);
#else
  // expression in __AVR__ section generates "dereferencing type-punned pointer
  // will break strict-aliasing rules" warning In fact, on other platforms (such
  // as STM32) there is no need to do this pointer magic as program memory may
  // be read in a usual way So expression may be simplified
  return gfxFont->bitmap;
#endif //__AVR__
}

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

class Flags 
{
  private:
    semaphore_t semaphore;

  public:
    void clear(const semaphore_t &flag)
    {
      semaphore &= (flag ^ 0xFFFF);
    }

    void set(const semaphore_t &flag)
    {
      semaphore |= flag;
    }

    bool isSet(const semaphore_t &flag)
    {
      return (semaphore & flag);
    }

    bool isClear(const semaphore_t &flag)
    {
      return !(semaphore & flag);
    }

    void flip(const semaphore_t &flag)
    {
      semaphore ^= flag;
    }
};

class Fixed
{
  private:
    struct characters_t
    { 
      int16_t X;  
      uint8_t Y;   // Note ONE byte only for the Y to save precious RAM.  
      char glyph;  // default "fixed" cell count this uses 120 bytes!
    };

  static const int MAXCELLS {30};

    int16_t m_X {0};
    uint8_t m_Y {0};
    uint8_t m_xStep {0};
    uint8_t m_yStep {0};     

    const fixedgfxfont_t* m_pFont;
    characters_t* m_newCursors {nullptr};
    characters_t* m_oldCursors {nullptr};
    
    int8_t m_cell {0};  // cell is a printed charcacter position

  public:

    Fixed() 
    {
        m_newCursors = new characters_t[MAXCELLS]();
        m_oldCursors = new characters_t[MAXCELLS]();
    };

    Fixed(fixedgfxfont_t* font) 
    {
      m_pFont = font;
    };

    ~Fixed()
    {
      // never called but included to stop auto-code checkers whinging.
      delete[] m_newCursors;
      delete[] m_oldCursors;
    }

    void registerPosition(const glyph_t &glyph)
    {
      //m_newCursors[m_cell].glyph = glyph;
      //m_newCursors[m_cell].X = m_X;
      //m_newCursors[m_cell].Y = m_Y;
      ++m_cell;
      char b[90];
      sprintf(b, "Registered: '%c' at X: %d, Count: %d", glyph, m_X, m_cell);
      Serial.println(b);
    }
  
    bool bleachThis()
    {
      return ( (m_newCursors[m_cell].glyph == m_oldCursors[m_cell].glyph) && 
               (m_newCursors[m_cell].X == m_oldCursors[m_cell].X ) &&
               (m_newCursors[m_cell].Y == m_oldCursors[m_cell].Y ));
    }

    characters_t getPrevGlyph()
    {
      return {m_oldCursors[m_cell].X, m_oldCursors[m_cell].Y, m_oldCursors[m_cell].glyph};        
    }

    int16_t getX()
    {
      return m_X;
    }

    int16_t getY()
    {
      return m_Y;
    }

    void moveTo(const int16_t &X, const int16_t &Y)
    {
      m_X = X;
      m_Y = Y;
    }

    void reset();

    int8_t getCount()
    {
      return m_cell;
    }
    
    int8_t getYstep()
    {
      return m_yStep;
    }

    void drawGlyph(const glyph_t &glyph);

    void printFixed(const char* buffer);

    void drawGlyphPrep(const glyph_t &glyph, glyphdata_t* data);

    glyph_t findGlyphCode(const glyph_t &glyph);
    
    dimensions_t getGlyphDimensions(const glyph_t &glyph);

    void setFixedFont(const fixedgfxfont_t* pNewSize);
};

class Display : public MCUFRIEND_kbv
{
  colours_t m_ink {defaultInk};
  colours_t m_paper {defaultPaper};
  uint8_t m_rotation {0};

  public:
  const uint16_t width  {TFT_WIDTH};
  const uint16_t height {TFT_HEIGHT};
  
  colours_t getInk()
  {
    return m_ink;
  }

  void setInk(const colours_t &C)
  {
    m_ink = C;
  }

  colours_t getPaper()
  {
    return m_paper;
  }

  void setPaper(const colours_t &C)
  {
    m_paper = C;
  }

  enum  
  {
    rotatePortraitNorth, 
    rotateDefaultNorth,
    rotatePortraitSouth, 
    rotateDefaultSouth
  };

};

class Graph : public Display
{
  public:

  Graph() {};

  void drawPointers();

  void draw(const triangle_t* polygon, const colours_t &ink, const colours_t &outline);
  void draw(const quadrilateral_t* polygon, const colours_t &ink, const  colours_t &outline);

  void translate(triangle_t* polygon, const coordinates_t &cords);
  void translate(quadrilateral_t* polygon, const coordinates_t &cords);
    
  void rotate(triangle_t* polygon, const angle_t &theta);
  void rotate(quadrilateral_t* polygon, const angle_t &theta);

  /**
   * @brief Displays the main graph
   * 
   * convert the temperature and humidity.reading readings into something that scales to the chart.
   * the FSD is 100 points giving a temp range of 0 - 50c (32 - 122f)
   * the first few lines just wall off temperatures from under freezing and above 50.
   */

  void displayGraph();

  /**
   * @brief  Overdraws the graph outline in the current foreground
   * 
   */  
  void drawMainAxes();

  void drawGraphScaleMarks();

  /**
   * @brief Draw the graph lines and chart calibration markings
   * 
   */  
  void drawReticles();

  /**
   * @brief Blanks the chart area if it's not already active 
   * 
   */
  void initGraph();

  /**
   * @brief draws circular plots for the analogue version
   * 
   */
  void drawRadials();
};

class Messages
{
  public:

  enum
  {
    c = 0, f, percent, slash, damp, dry, 
    frost, temperatureScale, humidityScale, work1, 
    work2, caution, xcaution, danger, xdanger
  };

  String translations[xdanger];

  char* pText;

  Messages() 
  {
    pText = nullptr;
    translations[c]        = F("c");
    translations[f]        = F("f");
    translations[percent]  = F("%");
    translations[caution]  = F("Extreme CAUTION");
    translations[slash]    = F("/");
    translations[damp]     = F("DAMP");
    translations[dry]      = F("DRY");
    translations[frost]    = F("FROST");
    translations[temperatureScale] = F("Temperature in ");
    translations[humidityScale] = F("Relative Humidity");
    translations[work1]    = F("High temp & humidity!");
    translations[work2]    = F("Temp Equivalent: ");
    translations[caution]  = F("CAUTION");
    translations[xcaution] = F("");
    translations[danger]   = F("DANGER");
    translations[xdanger]  = F("-DANGER TO LIFE-");
  };

  /**
   * @brief Print a short enumerated message
   * 
   * @param M Message number
   */

  void execute(const uint8_t &M);

  /**
   * @brief Print a buffer of text prepared by sprintf
   * 
   * @param pText char* to the buffer
   */

  void execute(const char* pText);

  /**
   * @brief Overwrite a predefined message in background
   * 
   * @param M enumerated message
   */

  void clear(const uint8_t &M);
  
  /**
   * @brief Get a pointed to an enumerated message block
   * 
   * @param M enumerated message
   * @return const char* to message string (NOT a string object!)
   */

  const char* getString(const uint8_t &M);

  /**
   * @brief Centers a block of text given character size
   * 
   * @param text String of characters
   * @param charWidth width of the current font
   * @return uint8_t central X offset based on the screen width
   */
  uint8_t centerText(const uint8_t &M, const uint8_t &charWidth);

  /**
     * @brief Horrible flashing test
     * 
     * @param M translate(triangle_t* triangle, const coordinates_t &cords)pre-defined message
     */
      
  void flashText(const uint8_t &M);

  void printNumber(const colours_t &ink, const uint8_t &characterSize, const uint8_t &number, const semaphore_t &flags);
  
  void rightAlign(const float &floaty, const char* buffer, const uint8_t &formatWidth, const uint16_t &integralWidth);
  /**
  * @brief A little nod to *nix systems
  * @remark This was developed on Linux due to the much faster compiler
  */
  void showUptime();
};

class Alarm
{

  private:
  using cursor = struct 
  {
    uint16_t X;
    uint16_t Y;
  };

  uint16_t m_timer;

  public:

  /**
   * @brief If an alarm condition is set, this flashes the LED pin
   * 
   */
  void checkAlarm();
  
  void annunciators();

  /**
  * @brief Polls for short AND long button pushes, acts accordingly
  * @bug Can be a bit fussy resetting the alarms.
  */
  void checkButton();

  /**
   * @brief Brings everthing to a halt if the DHT sensor breaks during use
   * 
   * @param response response Returned 16 bit from the DHT libary
   * @remarks  Displays warnings in the lower half of the screen to stop or reduce 
   * activity for health and safety. 
   */
  void sensorFailed(UniversalDHT::Response);

};

class Environmental
{
  public:
  /**
   * @brief Test the humidity is within watershed (and trigger alarms)
   * 
   */
  void checkHumidityConditions();

  /**
   * @brief Test the temperature is within watershed (and trigger alarms)
   * 
   */
  void checkTemperatureConditions();

  /**
   * @brief Set warning conditions if Steadman's temp is exceeded
   * 
   * @param T Temperature in C
   * @param H Relative humidity in %
   */
  void checkHeatIndex(const readings_t &readings);

  /**
   * @brief Display warnings about effective working temperature
   * 
   * @param T Steadman's Effective temperature in C
   * 
   * @remarks Displays warnings in the lower half of the screen to stop or reduce 
   * activity for health and safety. 
   */

  void unsafeTempWarnings(const float &);
  
   /**
   * @brief Steadman's 1994 approximation for heat in given humidity 
   * 
   * @param T Temperature in degrees C
   * @param R Relative humidity in %
   * @return float 
   * 
   * @remarks  Approximate the "Heat index" per Steadman 1994. While the dry bulb temperature
   *  may be well within safe limits for humans, the addition of humidity reading
   * prevents our bodies from effectively evaporatively cooling with the result
   * that our internal temperature rises - and the different of just a few degrees
   * C can cause fatigue, aggression and eventually heat stroke and possibly death.
   * These figures assume the person is doing mildly stressful work such as housework
   * Workers in more extreme physical labour will suffer faster and vice versa.
   * This is becoming a much more widespread problem as our climate changes.
   * 
   * Wikipedia https://en.wikipedia.org/wiki/Heat_index
   * 26–32 °C CAUTION: fatigue is possible with prolonged exposure and activity.
   *          Continuing activity could result in heat cramps.
   * 32–41 °C Extreme caution: heat cramps and heat exhaustion are possible.
   *          Continuing activity could result in heat stroke.
   * 41–54 °C Danger: heat cramps and heat exhaustion are likely.
   *          Heat stroke is probable with continued activity.
   * > 54 °C  Extreme danger: heat stroke is imminent.
   */

  float heatIndex(const readings_t &);
  /**
 * @brief Magnus' Dew Point (condensation temperature) calculation 
 * 
 * @param T Temperature in degrees C
 * @param R Relative humidity in %
 * @return float 
 * @remarks 
 * https://en.wikipedia.org/wiki/Dew_point
 * 
 */
  float magnusDewpoint(const readings_t &);

  void setColour(const reading_t &value, const limits_t &limits);
};

class Reading
{
    private:
    using coordinates_t = struct 
    {
      int16_t X {0}; 
      int16_t Y {0};
    };

    reading_t m_lowRead;
    reading_t m_highRead;
    reading_t m_reading;
    reading_t m_mean;
    reading_t m_cumulativeMovingAverage {0};
    reading_t m_correction;
    uint16_t m_cmaCounter;
    coordinates_t m_position;
    colours_t m_trace;           // graph line colour
    uint8_t* m_pipe;

    public:
    
    Reading()
    {
      // cumulative moving averages are a form of mean that doesn't need to track every single value
      // using these avoids little odd spikes from throwing the graph and smooths it out too.
      m_cmaCounter = 0;
    
      // If we run out of memory here, we've got bigger problems!
      m_pipe = new uint8_t[GRAPH_WIDTH];

      for (auto i {0}; i < GRAPH_WIDTH; ++i)
      {
        m_pipe[i] = (GRAPH_Y + FSD);
      }
  }
  
  ~Reading() 
  {
    // this should ever be called, but it's good
    // practise to do this even if it's not.
    delete [] m_pipe;
  }

  void setPipe(const uint16_t &i, const uint8_t &value)
  {
    m_pipe[i] = value;
  } 

  uint8_t getPipe(const uint16_t &i)
  {
    return m_pipe[i];
  }

  colours_t getTrace()
  {
    return m_trace;
  }

  void setTrace(const colours_t &C)
  {
    m_trace = C;
  }

  reading_t getHighRead()
  {
    return m_highRead;
  }

  reading_t getLowRead()
  {
    return m_lowRead;
  }

  void setLowRead(const reading_t &R)
  {
    m_lowRead = R;
  }

  void setHighRead(const reading_t &R)
  {
    m_highRead = R;
  }

  void setReading(const reading_t &R)
  {
    m_reading = R;
  }

  reading_t getReading()
  {
    return m_reading;
  }

  void setMinMax()
  {
    if (m_reading < m_lowRead)
    {
      m_lowRead = m_reading;
    }

    if (m_reading > m_highRead)
    {
      m_highRead = m_reading;
    }
  }

  reading_t getCMA()
  {
    return m_cumulativeMovingAverage;
  }

  void resetCMA()
  {
    m_cmaCounter = 0;
    m_cumulativeMovingAverage = 0;
  }

  void setX(const int16_t &X)
  {
    m_position.X = X;
  }

  void setY(const int16_t &Y)
  {
    m_position.Y = Y;
  }

  int16_t getX()
  {
    return m_position.X;
  }

  int16_t getY()
  {
    return m_position.Y;
  }

  void updateReading(const reading_t &reading);

  /**
   * @brief Get the current RH and Temp from the DHT11/22
   * 
   */

  void takeReadings();

  /**
   * @brief Post the large humidity and temperature readings
   * 
   */
  
  void showReadings();

  /**
   * @brief Calls printReading with the current X,Y positions
   * 
   * @param newReading The current reading
   * @param oldReading The last reading
   * @param metric If this reading needs conversion to imperial (option)
   * @param metric set true when working on Celcius
   * @param showFloats shows the floating point part (metric temp only)
   * @param showTemp set to true when working on a metric temp
   * 
   */
  
  void printReading(const reading_t &newReading, const semaphore_t &flags);

};
#endif