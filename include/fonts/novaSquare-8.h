
#ifndef __FIXEDFONTNOVASQUARETTF8
#define __FIXEDFONTNOVASQUARETTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x7E, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x7E,
  0x3F, 0xB6, 0xDB, 0x6D, 0xA0, 0x7E, 0xC3, 0xC3, 0xC3, 0x03, 0x03, 0x06,
  0x0C, 0x18, 0x30, 0x60, 0x7F, 0x7F, 0x03, 0x01, 0x81, 0x80, 0x80, 0xF8,
  0x06, 0x03, 0xC1, 0xE0, 0xF0, 0x6F, 0xE0, 0x01, 0x03, 0x81, 0xC1, 0xE1,
  0xB1, 0x98, 0xCC, 0xC6, 0xFF, 0x81, 0x80, 0xC0, 0x60, 0x3F, 0x10, 0x08,
  0x0C, 0x06, 0x03, 0xF8, 0x06, 0x03, 0xC1, 0xE0, 0xF0, 0x6F, 0xE0, 0x7E,
  0xC3, 0xC3, 0xC0, 0xC0, 0xFE, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x7E, 0x7F,
  0x06, 0x06, 0x06, 0x0C, 0x0C, 0x08, 0x18, 0x18, 0x10, 0x30, 0x30, 0x3E,
  0x31, 0x98, 0xCC, 0x66, 0x33, 0xFB, 0x07, 0x83, 0xC1, 0xE0, 0xF0, 0x6F,
  0xE0, 0x7E, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x7F, 0x03, 0x03, 0xC3, 0xC3,
  0x7E, 0x00, 0xFE, 0x31, 0x8C, 0x63, 0xF8, 0xC6, 0x31, 0x80, 0x7E, 0xC3,
  0xC3, 0xC3, 0xC0, 0xC0, 0xC0, 0xC0, 0xC3, 0xC3, 0xC3, 0x7E, 0xFE, 0x02,
  0x02, 0x06, 0x04, 0x0C, 0x08, 0x18, 0x10, 0x30, 0x20, 0x20, 0x40, 0x40,
  0xC0, 0x7C, 0x61, 0x8C, 0x83, 0x1B, 0x06, 0x34, 0x0C, 0x68, 0x0F, 0xA0,
  0x00, 0x5F, 0x01, 0xE3, 0x02, 0xC6, 0x0D, 0x8C, 0x13, 0x18, 0x63, 0xE0,
  0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {48,     0,   8,  12,  11,    2,  -11 },   // 0x00 '0' 
  {49,    12,   3,  12,   6,    1,  -11 },   // 0x01 '1' 
  {50,    17,   8,  12,  10,    1,  -11 },   // 0x02 '2' 
  {51,    29,   9,  12,  10,    1,  -11 },   // 0x03 '3' 
  {52,    43,   9,  12,   9,    0,  -11 },   // 0x04 '4' 
  {53,    57,   9,  12,  10,    1,  -11 },   // 0x05 '5' 
  {54,    71,   8,  12,  11,    2,  -11 },   // 0x06 '6' 
  {55,    83,   8,  12,   8,    0,  -11 },   // 0x07 '7' 
  {56,    95,   9,  12,  10,    1,  -11 },   // 0x08 '8' 
  {57,   109,   8,  12,  11,    2,  -11 },   // 0x09 '9' 
  {32,   121,   1,   1,   6,    0,    0 },   // 0x0A ' ' 
  {70,   122,   5,  12,   9,    2,  -11 },   // 0x0B 'F' 
  {67,   130,   8,  12,  11,    2,  -11 },   // 0x0C 'C' 
  {45,   142,   7,   1,   9,    1,   -5 },   // 0x0D '-' 
  {47,   143,   8,  14,   8,    0,  -12 },   // 0x0E '/' 
  {37,   157,  15,  12,  17,    1,  -11 },   // 0x0F '%' 
  {46,   180,   2,   2,   5,    1,   -1 }   // 0x10 '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  17,// total glyphs in the string
  12,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
    16,  // maximum X - right most
    13}; // maximum Y - top most
// Approx. 314 bytes -  but your mileage may vary.

#endif