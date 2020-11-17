#ifndef __DRACO_SEVENSEGMENTS_H
#define __DRACO_SEVENSEGMENTS_H

#include <Arduino.h>
#include <inttypes.h>
#include "types.hpp"

;

// triangle, rect, triangle

constexpr segment_t A {0,240, 32,208, 32,240,
                       32,208,70,32,
                       102,240, 102,208, 134,240};

constexpr segment_t B {0,0, 32,32, 32,0,
                       32,0,70,33,
                       102,32, 134,0, 102,0};

constexpr segment_t C {0,0, 32,32, 32,0,
                       32,208,70,32,
                       102,32, 102,0, 134,32};
class Sevensegments 
{
    public:

    void drawGlyph();
    void fillGlyph(segment_t* p, float scale, colours_t ink);
    
};

#endif