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



#ifndef __DRACO_HOTSTUFF_H
#define __DRACO_HOTSTUFF_H

#include <Arduino.h>
#include "types.hpp"


// remove this line to have the unit read in fahrenheit
#define USE_METRIC                   
 
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

inline gfxglyph_t* pgm_read_glyph_ptr(const gfxfont_t*gfxFont, uint8_t c) 
{
  #ifdef __AVR__
    return &(((gfxglyph_t *)pgm_read_pointer(&gfxFont->glyph))[c]);
  #else
    // expression in __AVR__ section may generate "dereferencing type-punned
    // pointer will break strict-aliasing rules" warning In fact, on other
    // platforms (such as STM32) there is no need to do this pointer magic as
    // program memory may be read in a usual way So expression may be simplified
    return gfxFont->glyph + c;
  #endif //__AVR__
}

inline uint8_t* pgm_read_bitmap_ptr(const gfxfont_t* gfxFont) 
{
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

  Flags()
  {
    semaphore = 0;
  }
  void clear(const semaphore_t flag)
  {
    semaphore &= (flag ^ 0xFFFF);
  }

  void set(const semaphore_t flag)
  {
    semaphore |= flag;
  }

  bool isSet(const semaphore_t flag)
  {
    return (semaphore & flag);
  }

  bool isClear(const semaphore_t flag)
  {
    return !(semaphore & flag);
  }

  void flip(const semaphore_t flag)
  {
    semaphore ^= flag;
  }
};

class Fonts
{
  private:
    
    uint16_t  m_X {0};
    uint16_t  m_Y {0};
    uint8_t   m_rotation {0};
    char*     m_pixelBuffer {nullptr};
    uint16_t  m_bufferWidth {FONT_BUFF_WIDTH};  
    uint16_t  m_bufferHeight {FONT_BUFF_HEIGHT};
    const gfxfont_t* m_pFont {nullptr};
    
  public:

    Fonts() 
    {}

    Fonts(gfxfont_t* font) 
    {
      m_pFont = font;
    };

    ~Fonts() {}

    void init();

    void setBufferDimensions(const uint16_t W, const uint16_t H)
    {
      m_bufferWidth  = W;
      m_bufferHeight = H;
    }

    void setRotation(const uint8_t R)
    {
      m_rotation = R;
    }

    uint8_t getRotation(const uint8_t R)
    {
      return m_rotation;
    }

    void setFont(const gfxfont_t* pNewSize)
    {
      m_pFont = pNewSize;
    }

    const gfxfont_t* getFont()
    {
      return m_pFont;
    }

    
    int16_t getX()
    {
      return m_X;
    }

    int16_t getY()
    {
      return m_Y;
    }

    uint8_t getYstep()
 
   {
      const gfxfont_t* font  = m_pFont;
      return pgm_read_byte(&font->newline);
    }

    uint8_t getXstep()
    {
      const gfxfont_t* font  = m_pFont;
      return pgm_read_byte(&font->xMax);
    }

    uint8_t drawImgGlyph(const glyph_t glyph);

    void prepImgGlyph(const glyph_t glyph, glyphdata_t* data);
    
    uint8_t bufferImgGlyph(const glyph_t glyph);

    glyph_t findGlyphCode(const glyph_t glyph);
    
    dimensions_t getGlyphDimensions(const glyph_t glyph);

    void bleachGlyph(const glyph_t glyph);

    void print(const char* b);

    void print(const String &string);

    void print(const __FlashStringHelper *flashString);

    void print(char* b);

    void print(char* b1, const bool switchFloats);

    void print(const int X, const int Y, char* buffer);

    void setTextColor(const colours_t ink, const colours_t paper);  

    void printPixel(coordinate_t X, coordinate_t Y, colours_t ink);

    void bufferPixel(const uint16_t X, const uint16_t Y);

    void showBuffer(const int X, const int Y);
};

class Display
{
  colours_t m_ink {defaultInk};
  colours_t m_paper {defaultPaper};
  uint8_t m_rotation {0};

  public:
  const uint16_t width  {TFT_WIDTH};
  const uint16_t height {TFT_HEIGHT};
  
  void setColours(const colours_t ink, const colours_t paper)
  {
    m_ink   = ink;
    m_paper = paper;
  }

  colours_t getInk()
  {
    return m_ink;
  }

  void setInk(const colours_t C)
  {
    m_ink = C;
  }

  colours_t getPaper()
  {
    return m_paper;
  }

  void setPaper(const colours_t C)
  {
    m_paper = C;
  }

  enum  
  {
    rotatePortraitNorth, 
    rotateLandscapeNorth,
    rotatePortraitSouth, 
    rotateLandscapeSouth
  };

};

class Graph
{
  private:
    
    const int FSD {100};
    const int GRAPH_WIDTH {189};
    const int GRAPH_HEIGHT {120};
    const int GRAPH_LEFT {63};
    const int xStep {27};
    const int yStep {20};
    const int GRAPH_Y {110};
    const int BASE {GRAPH_Y + FSD};
  
    int m_graphWidth {};

  public:

  Graph() {};

  void drawPointers();

  void draw(const triangle_t* polygon, const colours_t ink, const colours_t outline);
  void draw(const quadrilateral_t* polygon, const colours_t ink, const colours_t outline);

  void translate(triangle_t* polygon, const coordinates_t cords);
  void translate(quadrilateral_t* polygon, const coordinates_t cords);
    
  void rotate(triangle_t* polygon, const angle_t theta);
  void rotate(quadrilateral_t* polygon, const angle_t theta);

  void    drawIBar(const ucoordinate_t x, const reading_t reading, int16_t minimum, int16_t maximum, const int8_t scale, const colours_t ink);
  void  drawMinMax(const ucoordinate_t x, const reading_t reading, const int16_t min, const int16_t max, const int8_t scale, const colours_t ink);
  void drawDiamond(const ucoordinate_t x, const reading_t reading, const uint16_t scale, const uint8_t size, const colours_t ink);

  /**
   * @brief Displays the main graph
   * 
   * convert the temperature and humidity.reading readings into something that scales to the chart.
   * the FSD is 100 points giving a temp range of 0 - 50c (32 - 122f)
   * The flag determines which "phase" we're in (clear readings or set new ones)
   */

  void drawGraph(const int8_t flag);

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
  void drawReticles(const uint8_t xDivs, const uint8_t yDivs);

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

  void setGraphWidth(int W)
  {
    m_graphWidth = W;
  }

  int getGraphWidth()
  {
    return m_graphWidth;
  }

  int getGraphX()
  {
    return (TFT_WIDTH - m_graphWidth) / 2;
  }
};

class Messages
{
  public:

  enum
  {
    c, f, damp, dry, 
    frost, temperatureScale, humidityScale, work1, 
    work2, caution, xcaution, danger, xdanger
  };

  String translations[xdanger+1];

  char* pText;

  Messages() 
  {
    pText = nullptr;
    translations[c]        = F("c");
    translations[f]        = F("f");
    translations[caution]  = F("Extreme CAUTION");
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


  void debugger(const int X, const int Y, char* msg);

  /**
   * 
   * @brief Print a short enumerated message
   * 
   * @param M Message number
   */

  void execute(const uint8_t M);

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

  void clear(const uint8_t M);
  
  /**
   * @brief Get a pointed to an enumerated message block
   * 
   * @param M enumerated message
   * @return const char* to message string (NOT a string object!)
   */

  const char* getString(const uint8_t M);

  /**
   * @brief Centers a block of text given character size
   * 
   * @param text String of characters
   * @return uint8_t central X offset based on the screen width
   */
    uint16_t textWidth(char* message);
  
  /**
   * @brief Horrible flashing test
   * 
   * @param M 
   */
      
  void flashText(const uint8_t M);

  void printNumber(const colours_t ink, const uint8_t characterSize, const uint8_t number, const semaphore_t flags);
  
  void rightAlign(const float floaty, const char* buffer, const uint8_t formatWidth, const uint16_t integralWidth);
  /**
  * @brief A little nod to *nix systems
  * @remark This was developed on Linux due to the much faster compiler
  */
  void showUptime();
};

class Alarm
{

  private:

  uint16_t m_timer {};
  
  const int DRY_WARN_X  {0};
  const int DAMP_WARN_X {100};
  const int FROSTWARN_X {200};
  const int DRY_WARN_Y  {80};
  const int FROSTWARN_Y {80};
  const int DAMP_WARN_Y {80};

  const int LOW_TEMP_X  {42};
  const int LOW_TEMP_Y  {100};
  const int HIGHTEMP_y  {LOW_TEMP_Y};
  const int LOWHUMID_Y  {LOW_TEMP_Y};

  const int SHORTPRESS  {2};
  const int LONGPRESS   {10};

  const int LEFTMARGIN    {20};
  const int LEFTAXISLABEL {5};

  public:

  Alarm()
  {
    m_timer = 0;
  }

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

  const int CAUTION        {32};     // Three watermarks (32,41,54)
  const int WARNING        {41};     // per Steadman "safe" for working temperatures
  const int RISK           {54};     // Above 54c is very bad
  const float FROST_WATERSHED {4.0}; // ice can appear/persist around this temp
  const float DAMP_AIR_WATERSHED {MIN_COMFORT_HUMID - GUARD_HUMID};
  const float DRY_AIR_WATERSHED  {MAX_COMFORT_HUMID + GUARD_HUMID};

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
  void checkHeatIndex(const readings_t readings);

  /**
   * @brief Display warnings about effective working temperature
   * 
   * @param T Steadman's Effective temperature in C
   * 
   * @remarks Displays warnings in the lower half of the screen to stop or reduce 
   * activity for health and safety. 
   */

  void unsafeTempWarnings(const float T);
  
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

  float heatIndex(const readings_t R);
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
  float magnusDewpoint(const readings_t R);

  void setColour(const reading_t value, const limits_t limits);
};

class Reading
{
    private:

    float      m_cumulativeMovingAverage {};
    reading_t  m_correction {};
    reading_t  m_cmaCounter {};
    reading_t  m_minRead {};
    reading_t  m_maxRead {};
    reading_t  m_currRead {};
    int8_t     m_readPtr {};  // clock-like pointer to array
    colours_t  m_trace {};    // graph line colour
    int8_t*    m_max {};      // pointer to rouned integers for the graph
    int8_t*    m_min {};      // pointer to rouned integers for the graph
    reading_t* m_read {};     // floating point for actual readings.
    
    public:
    
    Reading()
    {
      // cumulative moving averages are a form of mean that doesn't need to track every single value
      // using these avoids little odd spikes from throwing the graph and smooths it out too.
      m_cmaCounter = 0.0;
      m_readPtr    = 0;
      m_cumulativeMovingAverage = 0.0;
      m_correction = 0.0;
      m_cmaCounter = 0;
      m_trace      = 0;   // graph line colour
      
      // If we run out of memory here, we've got bigger problems!
      m_min  = new int8_t[HOURS];
      m_max  = new int8_t[HOURS];
      m_read = new float[HOURS];    // floats are doubles by the looks of it!
  }
  
  ~Reading() 
  {
    // this should ever be called, but it's good
    // practise to do this even if it's not.
    delete [] m_max;
    delete [] m_min;
    delete [] m_read;
  }

  uint8_t getPtr()
  {
    return m_readPtr;
  } 
  
  colours_t getTrace()
  {
    return m_trace;
  }

  void setTrace(const colours_t C)
  {
    m_trace = C;
  }

  void initReads(const reading_t R)
  {
    m_cumulativeMovingAverage = R;

    for (auto i {0}; i < HOURS; ++i)
    {        
      m_max[i]  = 50;
      m_min[i]  = 50;
      m_read[i] = 126;
    }
  }

  reading_t getReading()
  {
    return m_currRead;
  }

  int8_t getMinRead(const int i)
  {
    return m_min[i];
  }

  int8_t getMaxRead(const int i)
  {
    return m_max[i];
  }

  void updateReading(const reading_t reading);

  /**
   * @brief Get the current RH and Temp from the DHT11/22
   * 
   */

  static void takeReadings();

  /**
   * @brief Post the large humidity and temperature readings
   * 
   */
  

  static void showReadings();

  /**
   * @brief Calls bufferReading with the current X,Y positions
   * 
   * @param newReading The current reading
   * @param oldReading The last reading
   * @param metric If this reading needs conversion to imperial (option)
   * @param metric set true when working on Celcius
   * @param showFloats shows the floating point part (metric temp only)
   * @param showTemp set to true when working on a metric temp
   * 
   */
    void bufferReading(const reading_t reading, char* buffer, const semaphore_t flags);

  
  reading_t getCMA()
  {
    return m_cumulativeMovingAverage;
  }

};
#endif