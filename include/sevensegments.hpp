#ifndef __DRACO_SEVENSEGMENTS_H
#define __DRACO_SEVENSEGMENTS_H

#include <Arduino.h>
#include <inttypes.h>
#include "types.hpp"

class Sevensegments 
{
    public:

    void drawGlyph(const coordinate_t X, const coordinate_t Y, 
                              const uint8_t glyph, 
                              const uint8_t wide, const uint8_t size,
                              const uint8_t rows, const uint8_t bias);
    void drawHSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t height, const colours_t ink);
    void drawVSegment(const coordinate_t X, const coordinate_t Y, const uint8_t len, const uint8_t width, const colours_t ink);
};

#endif