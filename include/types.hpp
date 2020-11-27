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

#ifndef __DRACO_HOTSTUFF_TYPES_H
#define __DRACO_HOTSTUFF_TYPES_H

#include <Arduino.h>
#include <inttypes.h>
#include "constants.hpp"

using semaphore_t   = uint16_t;
using colours_t     = uint16_t;
using angle_t       = int16_t;
using glyph_t       = uint8_t;
using ucoordinate_t = uint16_t;
using coordinate_t  = int16_t;

using reading_t     = float;
using reading_int_t = int16_t;
using isrtiming_t   = uint8_t;
using byte_t        = uint8_t;


using coordinates_t  = struct 
{
  coordinate_t X; 
  coordinate_t Y;
};

using scale_t = struct
{
  uint8_t temperature;
  uint8_t humidity;
};


using ucoordinates_t  = struct 
{
  ucoordinate_t X; 
  ucoordinate_t Y;
};


/*
*  Highly optimised types SPECIFIC to small screens (<255 pixels in either dimension)
*  Sounds crazy, but smaller Arduinos are optimised for 8 bit operations.
*  and every last clock cycle we can save is a bonus, particularly in tight loops!
*/

using short_coordinateX_t = uint8_t;
using short_coordinateY_t = uint8_t;

using dimensions_t = struct 
{
  uint16_t W;
  uint16_t H;
};

using segment_t = struct 
{
    coordinates_t coords[12];
};

using readings_t = struct
{
  float H;
  float T;
};

using limits_t = struct 
{
  reading_t lower;
  reading_t upper;
};

using minmax_t = struct
{
  reading_t min;
  reading_t max;
};

using triangle_t = struct
{
  coordinates_t cords[3];
};

using quadrilateral_t = struct
{
  coordinates_t cords[4];
};

using glyphdata_t = struct     
{
  uint16_t      offset;
  dimensions_t  dimensions;
  byte_t        bits;
  byte_t        bit;
  int8_t        xo;
  int8_t        yo;
  colours_t     colour;
  uint8_t*      bitmap;
  int16_t       x;
  int16_t       y;
  glyph_t       glyph;
  coordinate_t  xAdvance;
};

using hieroglyphs_t = struct 
{
  int8_t total;
  glyph_t glyphics[];
};

struct 
{
  volatile isrtiming_t timeInSeconds {0};
  volatile isrtiming_t timeInMinutes {0};
  volatile isrtiming_t timeInHours   {0};
  volatile isrtiming_t timeInDays    {0};
  volatile isrtiming_t timeInWeeks   {0};
  volatile isrtiming_t timeInYears   {0};
  volatile isrtiming_t timeToRead    {0};
} isrTimings;

enum
{
  FONT1, // 6 x 8 
  FONT2, // 12 x 16
  FONT3, // 18 x 24
  FONT4, // 24 x 32
  FONT5  // 30 x 40
};

// a couple of variables to determine the button multi-functions.
struct 
{
  bool          pressed    {false};
  uint8_t       timer      {0};
  uint8_t       lastTimer  {0};
} button;

// The failure record array gets sensor age after a "catastrophic" failure
struct failures
{
//  bool sensorFailure = {false};
  enum 
  {
    Y, W, D, H, M
  };
  uint8_t failTime[5];
};

/*
* Font structures for newer Adafruit_GFX (1.1 and later).
* Example fonts are included in 'Fonts' directory.
* Font data stored PER GLYPH (character) and is based on Adafruit libarary
*/

typedef struct
{
    uint8_t  ascii;         ///< ASCII code for this glyph
    uint16_t bitmapOffset;  ///< Pointer into GFXfont->bitmap
    uint8_t  width;         ///< Bitmap dimensions in pixels
    uint8_t  height;        ///< Bitmap dimensions in pixels
    uint8_t  xAdvance;      ///< Distance to advance cursor (x axis)
    int8_t   xOffset;       ///< X dist from cursor pos to UL corner
    int8_t   yOffset;       ///< Y dist from cursor pos to UL corner
} gfxglyph_t;

/*
* Extended font data (based on Adafruit libarary)
*/

typedef struct FixedFontsNS
{
    uint8_t* bitmap;       ///< Glyph bitmaps, concatenated
    gfxglyph_t* glyph;     ///< Glyph array
    uint8_t glyphCount;    ///< Actual number of defined glyphs
    int8_t newline;       ///< Newline distance (y axis)
    int8_t xMin;           ///< Leftmost  
    int8_t yMin;           ///< Bottom Y
    int8_t xMax;       ///< Rightmost
    int8_t yMax;           ///< Upper Y
} gfxfont_t ;

#endif