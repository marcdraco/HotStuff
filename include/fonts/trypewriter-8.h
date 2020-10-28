
#ifndef __FIXEDFONTKINGTHINGSTRYPEWRITERTTF8
#define __FIXEDFONTKINGTHINGSTRYPEWRITERTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x3C, 0x42, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x62, 0x3C, 0x70, 0x20,
  0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0xB1, 0xF8, 0x79, 0x8A, 0x18, 0x20,
  0xC3, 0x1C, 0x20, 0x81, 0xFC, 0xFE, 0x18, 0x61, 0xE0, 0xC0, 0xC1, 0x82,
  0x04, 0x30, 0xC2, 0x00, 0x08, 0x30, 0x61, 0x42, 0x89, 0x32, 0x7F, 0x08,
  0x10, 0x20, 0xFA, 0x08, 0x28, 0xD8, 0x20, 0x42, 0x08, 0x6E, 0x20, 0x0C,
  0x61, 0x02, 0x07, 0x88, 0xE0, 0xA1, 0x44, 0x70, 0xFF, 0x08, 0x10, 0x40,
  0x81, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7D, 0x8A, 0x0A, 0x17, 0xD0, 0x60,
  0xC1, 0xC2, 0xF8, 0x2C, 0x82, 0x0C, 0x04, 0x2C, 0x86, 0x81, 0x00, 0x08,
  0xE0, 0x00, 0x00, 0xFE, 0xC4, 0x89, 0x73, 0xC7, 0x0B, 0x10, 0x61, 0xE0,
  0x3C, 0xCD, 0x1C, 0x18, 0x10, 0x30, 0x23, 0x7C, 0x78, 0xFE, 0x04, 0x10,
  0xC2, 0x08, 0x41, 0x0C, 0x30, 0x84, 0x10, 0x82, 0x00, 0x72, 0x29, 0x25,
  0x0A, 0x87, 0x80, 0x78, 0x54, 0x29, 0x25, 0x13, 0x80, 0x5F, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {48,     0,   8,  10,   9,    0,   -9 },   // 0x00 '0' 
  {49,    10,   7,  11,   9,    1,  -10 },   // 0x01 '1' 
  {50,    20,   7,  10,   9,    1,   -9 },   // 0x02 '2' 
  {51,    29,   7,  12,   9,    1,   -9 },   // 0x03 '3' 
  {52,    40,   7,  11,   9,    1,  -10 },   // 0x04 '4' 
  {53,    50,   6,  12,   9,    2,   -9 },   // 0x05 '5' 
  {54,    59,   7,  10,   9,    1,  -10 },   // 0x06 '6' 
  {55,    68,   7,  11,   9,    1,   -9 },   // 0x07 '7' 
  {56,    78,   7,  10,   9,    1,   -9 },   // 0x08 '8' 
  {57,    87,   7,  12,   9,    1,  -10 },   // 0x09 '9' 
  {32,    98,   1,   1,   9,    0,    0 },   // 0x0A ' ' 
  {70,    99,   7,  10,   9,    1,   -9 },   // 0x0B 'F' 
  {67,   108,   7,  10,   9,    1,   -8 },   // 0x0C 'C' 
  {45,   117,   7,   1,   9,    1,   -4 },   // 0x0D '-' 
  {47,   118,   6,  14,   9,    1,  -11 },   // 0x0E '/' 
  {37,   129,   9,  10,   9,    0,   -9 },   // 0x0F '%' 
  {46,   141,   3,   3,   9,    3,   -2 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     9,  // maximum X - right most
    12}; // maximum Y - top most
// Approx. 276 bytes -  but your mileage may vary.

#endif