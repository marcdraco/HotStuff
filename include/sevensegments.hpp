#ifndef __DRACO_SEVENSEGMENTS_H
#define __DRACO_SEVENSEGMENTS_H

#include <Arduino.h>
#include <inttypes.h>
#include "types.hpp"

class Sevensegments 
{
    public:

    void drawGlyphA(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, uint8_t scale);
    void drawGlyphB(const coordinate_t X, const coordinate_t Y, const uint8_t glyph, uint8_t scale);
    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t height, const colours_t ink);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t width, const colours_t ink);
};

#endif