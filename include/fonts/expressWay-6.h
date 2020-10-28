
#ifndef __FIXEDFONTEXPRESSWAYRGTTF6
#define __FIXEDFONTEXPRESSWAYRGTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x73, 0x28, 0xE1, 0x86, 0x18, 0xF2, 0x70, 0x7D, 0xB6, 0xDB, 0x60, 0x74,
  0x42, 0x13, 0x32, 0x10, 0xF8, 0x72, 0x20, 0x8C, 0x08, 0x38, 0xA2, 0x70,
  0x0C, 0x18, 0x51, 0x22, 0x48, 0xBF, 0x82, 0x04, 0xFA, 0x08, 0x3E, 0xC8,
  0x10, 0xE2, 0x70, 0x31, 0x8C, 0x2E, 0xCA, 0x18, 0x72, 0x70, 0xFC, 0x30,
  0x84, 0x10, 0xC2, 0x08, 0x20, 0x39, 0x14, 0x4E, 0x47, 0x1C, 0x51, 0x38,
  0x72, 0x28, 0xA3, 0x8D, 0xE0, 0x84, 0x60, 0x00, 0xFC, 0x21, 0x0F, 0x42,
  0x10, 0x80, 0x38, 0x8E, 0x14, 0x08, 0x10, 0x20, 0x22, 0x38, 0xF0, 0x11,
  0x22, 0x22, 0x44, 0x44, 0x88, 0xE7, 0x4A, 0xA5, 0x4D, 0xC3, 0x4A, 0xA5,
  0x4E, 0xC0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   6,   9,   8,    1,   -8 },   // 0x00 '0' 
  {49,     7,   3,   9,   4,    0,   -8 },   // 0x01 '1' 
  {50,    11,   5,   9,   7,    1,   -8 },   // 0x02 '2' 
  {51,    17,   6,   9,   7,    1,   -8 },   // 0x03 '3' 
  {52,    24,   7,   9,   7,    0,   -8 },   // 0x04 '4' 
  {53,    32,   6,   9,   7,    1,   -8 },   // 0x05 '5' 
  {54,    39,   6,   9,   7,    1,   -8 },   // 0x06 '6' 
  {55,    46,   6,   9,   6,    0,   -8 },   // 0x07 '7' 
  {56,    53,   6,   9,   7,    0,   -8 },   // 0x08 '8' 
  {57,    60,   6,   9,   7,    1,   -8 },   // 0x09 '9' 
  {32,    67,   1,   1,   3,    0,    0 },   // 0x0A ' ' 
  {70,    68,   5,   9,   6,    1,   -8 },   // 0x0B 'F' 
  {67,    74,   7,   9,   8,    1,   -8 },   // 0x0C 'C' 
  {45,    82,   4,   1,   4,    0,   -4 },   // 0x0D '-' 
  {47,    83,   4,  12,   4,    0,  -10 },   // 0x0E '/' 
  {37,    89,   7,   9,   7,    0,   -8 },   // 0x0F '%' 
  {46,    97,   2,   1,   2,    0,    0 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   9,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
     8,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 231 bytes -  but your mileage may vary.

#endif