
#ifndef __FIXEDFONTERIKAORMIGTTF8
#define __FIXEDFONTERIKAORMIGTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x00, 0x3C, 0xCD, 0x0E, 0x1C, 0x38, 0x59, 0xBF, 0x3C, 0x19, 0xFE, 0x31,
  0x8C, 0x63, 0x18, 0xC0, 0x7B, 0x38, 0x41, 0x18, 0xC6, 0x30, 0xFC, 0x00,
  0x3C, 0x88, 0x18, 0x21, 0xC0, 0xC0, 0x83, 0x04, 0xF9, 0xC0, 0x08, 0x1C,
  0x1C, 0x3C, 0x6C, 0x6C, 0xCC, 0xFF, 0x0C, 0x0C, 0x0C, 0xFE, 0x08, 0x3E,
  0xCC, 0x10, 0x42, 0x3B, 0x80, 0x1D, 0xC4, 0x30, 0x83, 0xEC, 0xE1, 0x87,
  0x37, 0x80, 0x1E, 0xFF, 0xE4, 0x8C, 0x08, 0x18, 0x18, 0x10, 0x10, 0x10,
  0x10, 0x7D, 0x8F, 0x1E, 0x37, 0xD8, 0x60, 0xE1, 0xFE, 0xF0, 0x3C, 0xCF,
  0x1E, 0x36, 0x67, 0xC0, 0x83, 0x0C, 0x31, 0xE0, 0xFF, 0xFC, 0x03, 0x9F,
  0x97, 0x92, 0x8B, 0xC3, 0x40, 0x7C, 0x3A, 0x29, 0x35, 0x13, 0x88, 0x00,
  0x6F, 0x60 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {32,     0,   1,   1,  10,    0,    0 },   // 0x00 ' ' 
  {48,     1,   7,   9,  10,    1,   -8 },   // 0x01 '0' 
  {49,     9,   5,  10,  10,    2,   -9 },   // 0x02 '1' 
  {50,    16,   6,  10,  10,    2,   -8 },   // 0x03 '2' 
  {51,    24,   7,  11,  10,    1,   -8 },   // 0x04 '3' 
  {52,    34,   8,  11,  10,    1,   -9 },   // 0x05 '4' 
  {53,    45,   6,  10,  10,    2,   -8 },   // 0x06 '5' 
  {54,    53,   6,  11,  10,    2,  -10 },   // 0x07 '6' 
  {55,    62,   8,  11,  10,    1,   -9 },   // 0x08 '7' 
  {56,    73,   7,  10,   9,    1,   -9 },   // 0x09 '8' 
  {57,    82,   7,  11,  10,    1,   -8 },   // 0x0A '9' 
  {45,    92,   7,   2,  10,    1,   -4 },   // 0x0B '-' 
  {37,    94,   9,  12,  10,    1,  -10 },   // 0x0C '%' 
  {46,   108,   4,   3,  10,    3,   -2 }   // 0x0D '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  14,// total glyphs in the string
  12,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
    10,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 222 bytes -  but your mileage may vary.

#endif