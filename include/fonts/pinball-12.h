
#ifndef __FIXEDFONTPINBALLTTF12
#define __FIXEDFONTPINBALLTTF12
const uint8_t HotStuff12Bitmaps[] PROGMEM = {
  0x00, 0x0E, 0x10, 0x00, 0x03, 0x03, 0x00, 0x33, 0x5C, 0x00, 0x32, 0xC0,
  0xC0, 0x0C, 0x0D, 0x4E, 0x1C, 0x00, 0x0C, 0x19, 0x00, 0x00, 0x30, 0x00,
  0x03, 0x00, 0x00, 0x20, 0x0C, 0x00, 0x00, 0xC0, 0x30, 0xDC, 0x00, 0x10,
  0x0E, 0x20, 0x00, 0x18, 0x10, 0x06, 0x18, 0x00, 0x00, 0x0C, 0x00, 0x02,
  0x0A, 0x0D, 0xC0, 0x9C, 0x00, 0x00, 0x00, 0x30, 0x00, 0x14, 0x00, 0x32,
  0x01, 0x80, 0x00, 0x60, 0xEB, 0x80, 0xC2, 0x30, 0x00, 0x03, 0x02, 0x00,
  0x30, 0xC8, 0x00, 0x32, 0x01, 0x80, 0x00, 0x28, 0x0E, 0x00, 0x00, 0xCE,
  0x70, 0x00, 0x03, 0x00, 0x00, 0x37, 0x80, 0x00, 0x02, 0x00, 0xC0, 0x00,
  0x0C, 0x0E, 0xDC, 0x00, 0x0E, 0x10, 0x00, 0x03, 0x00, 0x00, 0x30, 0x08,
  0x80, 0x10, 0xC0, 0xC0, 0x04, 0x0D, 0x7F, 0x1C, 0x00, 0x9C, 0xC0, 0x40,
  0x00, 0x30, 0x00, 0x30, 0x00, 0x10, 0x0C, 0x00, 0x02, 0x0A, 0x05, 0x00,
  0x0E, 0x10, 0x00, 0x03, 0x03, 0x00, 0x30, 0x50, 0x80, 0x00, 0xC0, 0xC0,
  0x0C, 0x0D, 0x4E, 0x1C, 0x00, 0x4E, 0x30, 0x00, 0x03, 0x03, 0x00, 0x30,
  0xD4, 0xC0, 0x01, 0x00, 0xC0, 0x00, 0x0C, 0x0E, 0x5C, 0x00, 0xEE, 0x60,
  0x28, 0x04, 0x00, 0x34, 0x20, 0x00, 0x06, 0x00, 0x00, 0x30, 0x0C, 0x00,
  0x00, 0x85, 0xB0, 0x90, 0x00, 0x00, 0x40, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff12Glyphs[] PROGMEM = {
  {32,     0,   1,   1,  13,    0,    0 },   // 0x00 ' ' 
  {48,     1,  10,  13,  13,    1,  -13 },   // 0x01 '0' 
  {49,    18,  10,  14,  13,    1,  -13 },   // 0x02 '1' 
  {50,    36,   9,  13,  13,    1,  -13 },   // 0x03 '2' 
  {51,    51,   9,  13,  13,    2,  -13 },   // 0x04 '3' 
  {52,    66,  10,  13,  13,    1,  -13 },   // 0x05 '4' 
  {53,    83,  10,  13,  13,    1,  -13 },   // 0x06 '5' 
  {54,   100,  10,  13,  13,    1,  -13 },   // 0x07 '6' 
  {55,   117,   9,  13,  13,    2,  -13 },   // 0x08 '7' 
  {56,   132,  10,  13,  13,    1,  -13 },   // 0x09 '8' 
  {57,   149,  10,  13,  13,    1,  -13 },   // 0x0A '9' 
  {45,   166,   7,   1,  13,    2,   -7 },   // 0x0B '-' 
  {37,   167,  11,  14,  13,    0,  -13 },   // 0x0C '%' 
  {46,   187,   2,   2,  13,    5,   -2 }   // 0x0D '.' 
};

const gfxfont_t HotStuff12 PROGMEM = 
{
  (uint8_t  *)HotStuff12Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff12Glyphs, //< Glyph array
  14,// total glyphs in the string
  14,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
    11,  // maximum X - right most
    14}; // maximum Y - top most
// Approx. 300 bytes -  but your mileage may vary.

#endif