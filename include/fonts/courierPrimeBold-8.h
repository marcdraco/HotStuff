
#ifndef __FIXEDFONTCOURIERPRIMEBOLDTTF8
#define __FIXEDFONTCOURIERPRIMEBOLDTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x3C, 0x7E, 0xE7, 0xC3, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C, 0x33, 0xC3, 0x0C,
  0x30, 0xC3, 0x3F, 0xFC, 0x7C, 0xFD, 0x98, 0x30, 0xC3, 0x09, 0xBF, 0xFE,
  0x7B, 0xFC, 0xCE, 0x3C, 0x38, 0xFF, 0xF8, 0x18, 0x30, 0xA2, 0x4F, 0xFF,
  0xC6, 0x1F, 0x3E, 0xFF, 0xFC, 0x3E, 0xFC, 0x38, 0xFF, 0x78, 0x1E, 0x7E,
  0x60, 0xDE, 0xFF, 0xC3, 0xC3, 0x7F, 0x3C, 0xFF, 0xFF, 0x18, 0x60, 0xC3,
  0x06, 0x18, 0x30, 0x3C, 0xFD, 0x99, 0xE7, 0xF8, 0xF1, 0xFF, 0x7C, 0x3C,
  0xFE, 0xC3, 0xC3, 0xFF, 0x7B, 0x06, 0x3E, 0x38, 0x00, 0xFF, 0xFF, 0x63,
  0x7C, 0x7C, 0x60, 0x60, 0xF8, 0xF8, 0x3F, 0x7F, 0xE3, 0xC0, 0xC0, 0xC0,
  0xE1, 0x7F, 0x3E, 0xFF, 0xFC, 0x06, 0x0C, 0x30, 0x61, 0xC3, 0x06, 0x18,
  0x30, 0xC1, 0x86, 0x00, 0x71, 0x7C, 0xFE, 0xCE, 0xC0, 0xC1, 0xD9, 0xDE,
  0xCF, 0x03, 0x00, 0xFF, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {48,     0,   8,   9,  10,    1,   -8 },   // 0x00 '0' 
  {49,     9,   6,   9,  10,    2,   -8 },   // 0x01 '1' 
  {50,    16,   7,   9,  10,    1,   -8 },   // 0x02 '2' 
  {51,    24,   6,   9,  10,    2,   -8 },   // 0x03 '3' 
  {52,    31,   7,   9,  10,    1,   -8 },   // 0x04 '4' 
  {53,    39,   6,   9,  10,    2,   -8 },   // 0x05 '5' 
  {54,    46,   8,   9,  10,    1,   -8 },   // 0x06 '6' 
  {55,    55,   7,   9,  10,    1,   -8 },   // 0x07 '7' 
  {56,    63,   7,   9,  10,    1,   -8 },   // 0x08 '8' 
  {57,    71,   8,   9,  10,    1,   -8 },   // 0x09 '9' 
  {32,    80,   1,   1,  10,    0,    0 },   // 0x0A ' ' 
  {70,    81,   8,   9,  10,    1,   -8 },   // 0x0B 'F' 
  {67,    90,   8,   9,  10,    1,   -8 },   // 0x0C 'C' 
  {45,    99,   7,   2,  10,    1,   -5 },   // 0x0D '-' 
  {47,   101,   7,  12,  10,    1,   -9 },   // 0x0E '/' 
  {37,   112,   9,   9,  10,    0,   -8 },   // 0x0F '%' 
  {46,   123,   3,   3,  10,    3,   -2 }   // 0x10 '.' 
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
// Approx. 258 bytes -  but your mileage may vary.

#endif