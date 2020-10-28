
#ifndef __FIXEDFONTCOURIERPRIMEREGULARTTF8
#define __FIXEDFONTCOURIERPRIMEREGULARTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x33, 0x41, 0x04,
  0x10, 0x41, 0x04, 0xFC, 0x78, 0x88, 0x10, 0x20, 0xC3, 0x0C, 0x31, 0xFE,
  0xFA, 0x10, 0x41, 0x38, 0x10, 0x61, 0x78, 0x08, 0x30, 0xA2, 0x4C, 0x9F,
  0xC2, 0x04, 0x3E, 0xFA, 0x08, 0x3E, 0x84, 0x10, 0x61, 0x78, 0x1D, 0x84,
  0x3E, 0x86, 0x18, 0x61, 0x78, 0xFE, 0x30, 0x82, 0x10, 0x43, 0x08, 0x60,
  0x7A, 0x18, 0x61, 0x7A, 0x38, 0x61, 0x78, 0x7A, 0x28, 0x61, 0x7C, 0x10,
  0x86, 0xE0, 0x00, 0xFF, 0x90, 0x48, 0x24, 0x83, 0xC1, 0x20, 0x80, 0x40,
  0xF8, 0x00, 0x3F, 0x43, 0x81, 0x80, 0x80, 0x80, 0x80, 0x41, 0x3E, 0xFE,
  0x04, 0x30, 0x86, 0x10, 0xC2, 0x18, 0x41, 0x08, 0x20, 0x70, 0x44, 0xE2,
  0xCE, 0x80, 0x80, 0x98, 0x92, 0x89, 0x03, 0x00, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {48,     0,   8,   9,  10,    1,   -8 },   // 0x00 '0' 
  {49,     9,   6,   9,  10,    1,   -8 },   // 0x01 '1' 
  {50,    16,   7,   9,  10,    1,   -8 },   // 0x02 '2' 
  {51,    24,   6,   9,  10,    2,   -8 },   // 0x03 '3' 
  {52,    31,   7,   9,  10,    1,   -8 },   // 0x04 '4' 
  {53,    39,   6,   9,  10,    2,   -8 },   // 0x05 '5' 
  {54,    46,   6,   9,  10,    2,   -8 },   // 0x06 '6' 
  {55,    53,   6,   9,  10,    2,   -8 },   // 0x07 '7' 
  {56,    60,   6,   9,  10,    2,   -8 },   // 0x08 '8' 
  {57,    67,   6,   9,  10,    2,   -8 },   // 0x09 '9' 
  {32,    74,   1,   1,  10,    0,    0 },   // 0x0A ' ' 
  {70,    75,   9,   9,  10,    0,   -8 },   // 0x0B 'F' 
  {67,    86,   8,   9,  10,    1,   -8 },   // 0x0C 'C' 
  {45,    95,   7,   1,  10,    1,   -4 },   // 0x0D '-' 
  {47,    96,   6,  12,  10,    2,   -9 },   // 0x0E '/' 
  {37,   105,   9,   9,  10,    0,   -8 },   // 0x0F '%' 
  {46,   116,   2,   2,  10,    3,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  17,// total glyphs in the string
   9,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     9,  // maximum X - right most
    10}; // maximum Y - top most
// Approx. 250 bytes -  but your mileage may vary.

#endif