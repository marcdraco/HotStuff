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
  #define SJ0 0x0800
  #define SK0 0x1000
  #define SL0 0x2000
  #define SMX 0x4000
  #define SN0 0x8000


constexpr uint16_t sixteenSegCodes[40] =
{
    '0', B11111100,     //0xfA
    '1', B01100000,     
    '2', B11011010,     
    '3', B11110010,
    '4', B01100110,
    '5', B10110110,     
    '6', B10111110,
    '7', B11100000,
    '8', B00000011 * 256 + B11111111,
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

    uint8_t translateChar(const char glyph)
    {
        uint8_t i = 255;    // start at -1 because the counter "pre increments" but do...while loops are faster

        do 
        {
            i++;
        } while (glyph != sevenSegCodes[(i << 1)]);

        return sevenSegCodes[(i << 1) +1 ];
    }

    uint8_t translateChar16(const char glyph)
    {
        uint16_t i = 0xFFFF;

        do 
        {
            i++;
        } while (glyph != sixteenSegCodes[(i << 1)]);

        return sixteenSegCodes[i << 1];
    };

    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawRLSegment(const coordinate_t X, const coordinate_t Y, const uint8_t shift, const uint8_t onFlag);
    void drawLRSegment(const coordinate_t X, const coordinate_t Y, const uint8_t shift, const uint8_t onFlag);
    void drawDP(const coordinate_t X, const coordinate_t Y, const uint8_t radius, const uint8_t onFlag);
};

#endif