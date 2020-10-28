
#ifndef __FIXEDFONTNOVAMONOTTF6
#define __FIXEDFONTNOVAMONOTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x74, 0xE7, 0x5A, 0xE7, 0x31, 0x70, 0x2E, 0x92, 0x49, 0x20, 0x74, 0x62,
  0x11, 0x11, 0x18, 0xF8, 0xF8, 0x88, 0x47, 0x06, 0x31, 0x70, 0x08, 0x61,
  0x8A, 0x49, 0x2F, 0xC2, 0x08, 0x72, 0x21, 0x0F, 0x26, 0x31, 0x70, 0x74,
  0x63, 0x0F, 0x46, 0x31, 0x70, 0xF8, 0x84, 0x42, 0x21, 0x18, 0x80, 0x74,
  0x63, 0xB7, 0x46, 0x31, 0x70, 0x74, 0x63, 0x17, 0x86, 0x31, 0x70, 0x00,
  0xF8, 0x88, 0xF8, 0x88, 0x80, 0x74, 0x63, 0x08, 0x42, 0x31, 0x70, 0xF8,
  0x04, 0x10, 0x82, 0x10, 0x43, 0x08, 0x21, 0x04, 0x20, 0x80, 0x61, 0x21,
  0x88, 0x61, 0x0C, 0x23, 0x85, 0x0E, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   9,   7,    1,   -8 },   // 0x00 '0' 
  {49,     6,   3,   9,   7,    1,   -8 },   // 0x01 '1' 
  {50,    10,   5,   9,   7,    1,   -8 },   // 0x02 '2' 
  {51,    16,   5,   9,   7,    1,   -8 },   // 0x03 '3' 
  {52,    22,   6,   9,   7,    0,   -8 },   // 0x04 '4' 
  {53,    29,   5,   9,   7,    1,   -8 },   // 0x05 '5' 
  {54,    35,   5,   9,   7,    1,   -8 },   // 0x06 '6' 
  {55,    41,   5,   9,   7,    1,   -8 },   // 0x07 '7' 
  {56,    47,   5,   9,   7,    1,   -8 },   // 0x08 '8' 
  {57,    53,   5,   9,   7,    1,   -8 },   // 0x09 '9' 
  {32,    59,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    60,   4,   9,   7,    1,   -8 },   // 0x0B 'F' 
  {67,    65,   5,   9,   7,    1,   -8 },   // 0x0C 'C' 
  {45,    71,   5,   1,   7,    1,   -4 },   // 0x0D '-' 
  {47,    72,   6,  13,   7,    0,  -10 },   // 0x0E '/' 
  {37,    82,   7,   9,   7,    0,   -8 },   // 0x0F '%' 
  {46,    90,   2,   2,   7,    3,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   9,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 224 bytes -  but your mileage may vary.

#endif