#ifndef __DRACO_SEVENSEGMENTS_H
#define __DRACO_SEVENSEGMENTS_H

#include <Arduino.h>
#include <inttypes.h>
#include "types.hpp"

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
    void drawGlyph16(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t length, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void drawPercent(const coordinate_t X, const coordinate_t Y, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void slash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows);
    void backslash(const coordinate_t X, const coordinate_t Y, const uint8_t wide, const uint8_t high, const uint8_t rows);

    uint8_t translateChar(const char glyph);

    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawXSegment(const coordinate_t X, const coordinate_t Y, const uint8_t onFlag);
    void drawDP(const coordinate_t X, const coordinate_t Y, const uint8_t radius, const uint8_t onFlag);
};

#endif