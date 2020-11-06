
#ifndef __FIXEDFONTANONYMOUSPROBOLDTTF8
#define __FIXEDFONTANONYMOUSPROBOLDTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x00, 0x3C, 0x46, 0x87, 0x8F, 0x9D, 0xB9, 0xF1, 0xF1, 0x62, 0x3C, 0x10,
  0x43, 0x3C, 0x10, 0x41, 0x04, 0x11, 0xF0, 0x3E, 0x62, 0x41, 0x81, 0x02,
  0x0E, 0x1C, 0x39, 0x71, 0x7F, 0x7A, 0x18, 0x41, 0x18, 0x10, 0x71, 0xC5,
  0xF0, 0x18, 0x30, 0xE3, 0x44, 0x99, 0x3F, 0x84, 0x08, 0x7C, 0xFC, 0x80,
  0x80, 0xFC, 0xC2, 0x01, 0x01, 0x21, 0x31, 0x1E, 0x7C, 0xC0, 0x80, 0xBC,
  0xC2, 0x81, 0x81, 0x81, 0x42, 0x3C, 0xFF, 0x06, 0x10, 0x40, 0x81, 0x04,
  0x08, 0x10, 0x20, 0x7D, 0x06, 0x0C, 0x17, 0xD8, 0xE0, 0xC1, 0x86, 0xF8,
  0x3C, 0xC2, 0x81, 0x81, 0x81, 0x43, 0x3D, 0x01, 0x03, 0x3E, 0xFE, 0x02,
  0xCE, 0x54, 0xE6, 0x82, 0x0C, 0x13, 0x6B, 0x96, 0x18, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {32,     0,   1,   1,   9,    0,    0 },   // 0x00 ' ' 
  {48,     1,   8,  10,   9,    0,   -9 },   // 0x01 '0' 
  {49,    11,   6,  10,   9,    0,   -9 },   // 0x02 '1' 
  {50,    19,   8,  10,   9,   -1,   -9 },   // 0x03 '2' 
  {51,    29,   6,  10,   9,    1,   -9 },   // 0x04 '3' 
  {52,    37,   7,  10,   9,    0,   -9 },   // 0x05 '4' 
  {53,    46,   8,  10,   9,    0,   -9 },   // 0x06 '5' 
  {54,    56,   8,  10,   9,    0,   -9 },   // 0x07 '6' 
  {55,    66,   7,  10,   9,    0,   -9 },   // 0x08 '7' 
  {56,    75,   7,  10,   9,    0,   -9 },   // 0x09 '8' 
  {57,    84,   8,  10,   9,    0,   -9 },   // 0x0A '9' 
  {45,    94,   7,   1,   9,    0,   -3 },   // 0x0B '-' 
  {37,    95,   7,  11,   8,    0,  -10 },   // 0x0C '%' 
  {46,   105,   2,   2,   9,    3,   -1 }   // 0x0D '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  14,// total glyphs in the string
  11,  // newline distance (y axis)
    -1,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     8,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 218 bytes -  but your mileage may vary.

#endif