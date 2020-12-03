/*
  Copyright 2020, Marc Draco & Daniel Melvin

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

  3. Commercial use must include a per-unit donation of not less than 5% of the unit
  margin to the "Astro Nerd" cancer fund. Non commerical users may use this software
  without paying, but all donations to Rose's treatment are welcomed. Neither of the
  authors are connected to Rose DF, but it's hoped that this software, named in her
  honour will help raise awareness and some money to help take the rough edges of her 
  life. Cancer sucks people. It could hit any of us, at any time!

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


#ifndef __DRACO_ROSE_ASTRO_NERD_DIGITAL_H
#define __DRACO_ROSE_ASTRO_NERD_DIGITAL_H

#include <Arduino.h>
#include <inttypes.h>
#include "types.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b){int16_t t = a; a = b; b = t;}
#endif

constexpr uint8_t sevenSegCodes[44] =
{
    '0', B11111100,
    '1', B01100000,    
    '2', B11011010,    
    '3', B11110010,
    '4', B01100110,
    '5', B10110110,     
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
    '.', B00000001,
    '/', B11111110,
    ' ', B00000000
};

  constexpr uint16_t  SEG_A1 =0x0001;
  constexpr uint16_t  SEG_A2 =0x0002;
  constexpr uint16_t  SEG_B  =0x0004;
  constexpr uint16_t  SEG_C  =0x0008;
  constexpr uint16_t  SEG_D1 =0x0010;
  constexpr uint16_t  SEG_D2 =0x0020;
  constexpr uint16_t  SEG_E  =0x0040;
  constexpr uint16_t  SEG_F  =0x0080;
  constexpr uint16_t  SEG_G1 =0x0100;
  constexpr uint16_t  SEG_G2 =0x0200;
  constexpr uint16_t  SEG_H  =0x0400;
  constexpr uint16_t  SEG_I  =0x0800;
  constexpr uint16_t  SEG_J  =0x1000;
  constexpr uint16_t  SEG_K  =0x2000;
  constexpr uint16_t  SEG_L  =0x4000;
  constexpr uint16_t  SEG_M  =0x8000;
  constexpr uint16_t  SEG_A  = SEG_A1 + SEG_A2;
  constexpr uint16_t  SEG_D  = SEG_D1 + SEG_D2;
  constexpr uint16_t  SEG_G  = SEG_G1 + SEG_G2;


  #define X256(b,a) (unsigned int) ((a << 8) + b)

constexpr uint16_t sixteenSegCodes[120] =
{
    ' ', 0,                      
    '0', 0Xff + SEG_K + SEG_J,                      
    '1', SEG_I + SEG_L + SEG_D + SEG_A1,                
    '2', SEG_A + SEG_B + SEG_G + SEG_E + SEG_D,      
    '3', SEG_A + SEG_B + SEG_C + SEG_D + SEG_G,    
    '4', SEG_F + SEG_G + SEG_B + SEG_C,                
    '5', SEG_A + SEG_H + SEG_G + SEG_C + SEG_D,      
    '6', SEG_A + SEG_F + SEG_E + SEG_C + SEG_G + SEG_D, 
    '7', SEG_A + SEG_B + SEG_C,                     
    '8', 0xff + SEG_G,                        
    '9', SEG_A + SEG_F + SEG_B + SEG_G + SEG_C,         
    'A', SEG_A + SEG_F + SEG_B + SEG_E + SEG_C + SEG_G,     
    'B', SEG_A + SEG_I + SEG_L + SEG_B + SEG_C + SEG_G2 + SEG_D, 
    'C', SEG_A + SEG_F + SEG_E + SEG_D,             
    'D', SEG_A + SEG_B + SEG_C + SEG_D + SEG_I + SEG_L,     
    'E', SEG_A + SEG_F + SEG_E + SEG_D + SEG_G1,         
    'F', SEG_A + SEG_F + SEG_E + SEG_G1,                 
    'G', SEG_A + SEG_F + SEG_E + SEG_D + SEG_C + SEG_G2,  
    'H', SEG_F + SEG_E + SEG_G + SEG_B + SEG_C,
    'I', SEG_A + SEG_D + SEG_I + SEG_L,
    'J', SEG_B + SEG_C + SEG_A2 + SEG_D,
    'K', SEG_F + SEG_E + SEG_G1 + SEG_J + SEG_M,
    'L', SEG_F + SEG_E + SEG_D,
    'M', SEG_F + SEG_E + SEG_B + SEG_C + SEG_H + SEG_J,
    'N', SEG_F + SEG_E + SEG_B + SEG_C + SEG_H + SEG_M,
    'O', 0xFF,
    'P', SEG_F + SEG_E + SEG_A + SEG_B + SEG_G,
    'Q', 0xFF + SEG_M,
    'R', SEG_F + SEG_E + SEG_A + SEG_B + SEG_G + SEG_M,
    'S', SEG_A + SEG_F + SEG_G + SEG_C + SEG_D,      
    'T', SEG_A + SEG_I + SEG_L,
    'U', SEG_F + SEG_E + SEG_B + SEG_C + SEG_D,
    'V', SEG_E + SEG_F + SEG_K + SEG_J,
    'W', SEG_F + SEG_E + SEG_B + SEG_C + SEG_K + SEG_M,
    'X', SEG_H + SEG_J + SEG_M + SEG_K,
    'Y', SEG_H + SEG_J + SEG_L,
    'Z', SEG_A + SEG_D + SEG_J + SEG_K,
    '*', SEG_J + SEG_K + SEG_H + SEG_M + SEG_I + SEG_L + SEG_G,
    '[', SEG_A1 + SEG_E + SEG_F + SEG_D1,
    ']', SEG_A2 + SEG_B + SEG_C + SEG_D2,
    '\\', SEG_H + SEG_M,
    '/', SEG_J + SEG_K,          
    '(', SEG_J + SEG_M,
    ')', SEG_H + SEG_K,
    '$', SEG_A + SEG_F + SEG_G + SEG_C + SEG_D + SEG_I + SEG_L,
    '&', SEG_F + SEG_A1 + SEG_I + SEG_G1 + SEG_E + SEG_D + SEG_M,
    '|', SEG_I + SEG_L,
    '!', SEG_F + SEG_E,
    '%', SEG_A2 + SEG_J + SEG_K + SEG_D1,
    '?', SEG_A + SEG_B + SEG_G2 + SEG_L,
    '=', SEG_G + SEG_D,
    '-', SEG_G,
    '<', SEG_H + SEG_I + SEG_J,             // down arrow with tail
    '>', SEG_K + SEG_L + SEG_M,             // up arrow with tail
    '#', SEG_A2 + SEG_B + SEG_G2 + SEG_I,   // degree symbol
    '@', SEG_G + SEG_D + SEG_I + SEG_L,     // +/- 
    '{', SEG_H + SEG_J,                     // down arrow
    '}', SEG_K + SEG_M,                     // up arrow
    ':', SEG_H + SEG_J + SEG_K + SEG_M      // MULTIPLY
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

    Sevensegments(const colours_t lit)
    {
        m_lit = lit;
        setUnlit(lit);
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

    colours_t setLit(colours_t colour1, colours_t colour2)
    {
        setUnlit(colour2);
        return setLit(colour1);
    }

    colours_t setLit(colours_t colour)
    {
        colours_t c = m_lit;
        m_lit       = colour;
        return    c;
    }

    colours_t setUnlit(colours_t colour)
    {
        // NOTE returns the LIT colour! The dim colour is calculated. 
        m_unlit = Sevensegments::dimmer(colour, 2);
        return m_lit;
    }

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

    void drawGlyph(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t length, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void drawGlyph16(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void drawPercent(const coordinate_t X, const coordinate_t Y, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void slash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows);
    void backslash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows);
    void fastShortLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t ink); 
    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawRLSegment(coordinate_t X, coordinate_t Y, coordinate_t X1, coordinate_t Y1, const uint8_t rows, uint8_t onFlag);
    void drawLRSegment(coordinate_t X, coordinate_t Y, coordinate_t X1, coordinate_t Y1, const uint8_t rows, uint8_t onFlag);
    void drawDP(const coordinate_t X, const coordinate_t Y, const uint8_t radius, const uint8_t onFlag);
    int segmentedString(coordinate_t X, coordinate_t Y, char * b, uint8_t size, uint8_t rows, uint8_t bias, uint8_t step);
    static colours_t dimmer(colours_t C, uint8_t brightness);
};
extern Sevensegments segments;

#endif