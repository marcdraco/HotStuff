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

    public:

    Sevensegments(const colours_t lit, const colours_t unlit)
    {
        m_lit = lit;
        m_unlit = unlit;
    }

    void drawGlyph(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t wide, const uint8_t size, const uint8_t rows, const uint8_t bias);
    void drawGlyph16(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, const uint8_t wide, const uint8_t size, const uint8_t rows, const uint8_t bias);

    uint8_t translateChar(const char glyph);

    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t height, const uint8_t onFlag);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t width, const uint8_t onFlag);
    void drawXSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t width, const uint8_t onFlag);
    void drawDP(const coordinate_t X, const coordinate_t Y, const uint8_t radius, const uint8_t onFlag);
};

#endif