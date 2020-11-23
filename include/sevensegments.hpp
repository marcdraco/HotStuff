#ifndef __DRACO_ROSE_DIGITAL_H
#define __DRACO_ROSE_DIGITAL_H

#include <Arduino.h>
#include <inttypes.h>
#include "types.hpp"


constexpr uint8_t sevenSegCodes[40] =
{
    '0', B11111100,     //0xfA
    '1', B01100000,     //0x60
    '2', B11011010,     //0xDA
    '3', B11110010,
    '4', B01100110,
    '5', B10110110,     //0XB6
    '6', B10111110,
    '7', B11100000,
    '8', B11111111,
    '9', B11100110,
    'A', B11101111,
    'B', B00111111,
    'C', B10011101,
    'D', B01111011,
    'E', B10011110,
    'F', B10001110,
    '-', B00000010,
    'o', B11000110,
    'C', B00011010,
    '.', B00000001
};

  #define SA1 0x0001
  #define SA2 0x0002
  #define SB0 0x0004
  #define SC0 0x0008
  #define SD1 0x0010
  #define SD2 0x0020
  #define SE0 0x0040
  #define SF0 0x0080
  #define SG1 0x0100
  #define SG2 0x0200
  #define SH0 0x0400
  #define SI0 0x0800
  #define SJ0 0x1000
  #define SK0 0x2000
  #define SL0 0x4000
  #define SMX 0x8000

  #define X256(b,a) (unsigned int) ((a << 8) + b)

constexpr uint16_t sixteenSegCodes[108] =
{
    ' ', 0,                       //CHECK
    '0', 0Xff+SK0+SJ0,                       //CHECK
    '1', SI0+SL0+SD1+SD2+SA1,                // check 
    '2', SA1+SA2+SB0+SG1+SG2+SE0+SD1+SD2,    // check   
    '3', SA1+SA2+SB0+SC0+SD1+SD2+SG1+SG2,    // check 
    '4', SF0+SG1+SG2+SB0+SC0,                // check 
    '5', SA1+SA2+SH0+SG1+SG2+SC0+SD1+SD2,     // check  
    '6', SA1+SA2+SF0+SE0+SC0+SG1+SG2+SD1+SD2, // check 
    '7', SA1+SA2+SB0+SC0,                     // check 
    '8', 0xff+SG1+SG2,                        // check 
    '9', SA1+SA2+SF0+SB0+SG1+SG2+SC0,         // check 
    'A', SA1+SA2+SF0+SB0+SE0+SC0+SG1+SG2,     // CHECK
    'B', SA1+SA2+SI0+SL0+SB0+SC0+SG2+SD1+SD2, // check
    'C', SA1+SA2+SF0+SE0+SD1+SD2,             // check
    'D', SA1+SA2+SB0+SC0+SD1+SD2+SI0+SL0,     // check
    'E', SA1+SA2+SF0+SE0+SD1+SD2+SG1,         // check
    'F', SA1+SA2+SF0+SE0+SG1,                 // CHEK
    'G', SA1+SA2+SF0+SE0+SD1+SD2+SC0+SG2,  
    'H', SF0+SE0+SG1+SG2+SB0+SC0,
    'I', SA1+SA2+SD1+SD2+SI0+SL0, //check
    'J', SB0+SC0+SA2+SD1+SD2, //check
    'K', SF0+SE0+SG1+SJ0+SMX, //CHECK
    'L', SF0+SE0+SD1+SD2, //CHEC
    'M', SF0+SE0+SB0+SC0+SH0+SJ0,// CHECK
    'N', SF0+SE0+SB0+SC0+SH0+SMX, //CHECK
    'O', 0xFF, //CHECK
    'P', SF0+SE0+SA1+SA2+SB0+SG1+SG2,//CHECK
    'Q', 0xFF+SMX,//CHECK
    'R', SF0+SE0+SA1+SA2+SB0+SG1+SG2+SMX,//CHECK
    'S', SA1+SA2+SF0+SG1+SG2+SC0+SD1+SD2,     // check  
    'T', SA1+SA2+SI0+SL0,
    'U', SF0+SE0+SB0+SC0+SD1+SD2,
    'V', SE0+SF0+SK0+SJ0,
    'W', SF0+SE0+SB0+SC0+SK0+SMX, //CHECK
    'X', SH0+SJ0+SMX+SK0,
    'Y', SH0+SJ0+SL0,
    'Z', SA1+SA2+SD1+SD2+SJ0+SK0,
    '*', SJ0+SK0+SH0+SMX+SI0+SL0+SG1+SG2, //CHECK
    '[', SA1+SE0+SF0+SD1,
    ']', SA2+SB0+SC0+SD2,
    '\\', SH0+SMX,
    '/', SJ0+SK0,       // CHECK    
    '(', SJ0+SMX,
    ')', SH0+SK0,
    '$', SA1+SA2+SF0+SG1+SG2+SC0+SD1+SD2+SI0+SL0,
    '&', SF0+SA1+SI0+SG1+SE0+SD1+SD2+SMX,
    '|', SI0+SL0,
    '!', SF0+SE0,
    '%', SA2+SJ0+SK0+SD1,
    '?', SA1+SA2+SB0+SG2+SL0,
    '=', SG1+SG2+SD1+SD2,
    '-', B00000010,
    'o', B11000110,
    '.', B00000001
};

class Sevensegments 
{
    private:

    colours_t m_lit;
    colours_t m_unlit;
    uint8_t m_Xlength;       // length of each line X axes
    uint8_t m_Ylength;       // length of each line Y axes
    uint8_t m_XYlen;
    uint8_t m_rows;         // number of lines drawn
    uint8_t m_bias;         // spacing/cracks

    ucoordinate_t m_X;
    ucoordinate_t m_newline;

    public:

    Sevensegments(const colours_t lit, const colours_t unlit)
    {
        m_lit = lit;
        m_unlit = unlit;
    }

    void setBias(const uint8_t bias)
    {
        m_bias = bias;
    }

    void setXlen(const uint8_t length)
    {
        m_Xlength = length;
    }

    void setYlen(const uint8_t length)
    {
        m_Ylength = length;
    }

    void setXYlen(const uint8_t length)
    {
        m_XYlen = length;
    }

    void setRows(const uint8_t rows)
    {
        m_rows = rows;
    }

    void setLit(colours_t colour)
    {
        m_lit = colour;   
    }

    void setUnlit(colours_t colour)
    {
        m_lit = colour;   
    }

    void drawGlyph(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t length, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void drawGlyph16(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void drawPercent(const coordinate_t X, const coordinate_t Y, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void slash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows);
    void backslash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows);

    uint8_t translateChar(const uint8_t glyph)
    {
        uint8_t i = 255;    // start at -1 because the counter "pre increments" but do...while loops are faster

        do 
        {
            i++;
        } while (glyph != sevenSegCodes[(i << 1)]);

        return sevenSegCodes[(i << 1) +1];
    }

    uint16_t translateChar16(const uint8_t glyph)
    {
        uint16_t i = 0xFFFF;

        do 
        {
            i++;
        } while (glyph != sixteenSegCodes[(i << 1)]);
        return sixteenSegCodes[(i << 1) +1];
    };

    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawRLSegment(const coordinate_t X, coordinate_t Y, const uint8_t width, const uint8_t height, const uint8_t rows, const uint8_t onFlag);
    void drawLRSegment(const coordinate_t X, coordinate_t Y, const uint8_t width, const uint8_t height, const uint8_t rows, const uint8_t onFlag);
    void drawDP(const coordinate_t X, const coordinate_t Y, const uint8_t radius, const uint8_t onFlag);
};

#endif