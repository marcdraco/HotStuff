
#ifndef __FIXEDFONTANONYMOUSPROBOLDTTF8
#define __FIXEDFONTANONYMOUSPROBOLDTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x3C, 0x46, 0x87, 0x8F, 0x9D, 0xB9, 0xF1, 0xF1, 0x62, 0x3C, 0x10, 0x43,
  0x3C, 0x10, 0x41, 0x04, 0x11, 0xF0, 0x3E, 0x62, 0x41, 0x81, 0x02, 0x0E,
  0x1C, 0x39, 0x71, 0x7F, 0x7A, 0x18, 0x41, 0x18, 0x10, 0x71, 0xC5, 0xF0,
  0x18, 0x30, 0xE3, 0x44, 0x99, 0x3F, 0x84, 0x08, 0x7C, 0xFC, 0x80, 0x80,
  0xFC, 0xC2, 0x01, 0x01, 0x21, 0x31, 0x1E, 0x7C, 0xC0, 0x80, 0xBC, 0xC2,
  0x81, 0x81, 0x81, 0x42, 0x3C, 0xFF, 0x06, 0x10, 0x40, 0x81, 0x04, 0x08,
  0x10, 0x20, 0x7D, 0x06, 0x0C, 0x17, 0xD8, 0xE0, 0xC1, 0x86, 0xF8, 0x3C,
  0xC2, 0x81, 0x81, 0x81, 0x43, 0x3D, 0x01, 0x03, 0x3E, 0x00, 0xFE, 0x08,
  0x20, 0xFA, 0x08, 0x20, 0x82, 0x00, 0x3F, 0x43, 0x81, 0x80, 0x80, 0x80,
  0x80, 0x86, 0x84, 0x78, 0xFE, 0x02, 0x0C, 0x10, 0x60, 0x83, 0x04, 0x18,
  0x20, 0xC1, 0x82, 0x0C, 0x00, 0x02, 0xCE, 0x54, 0xE6, 0x82, 0x0C, 0x13,
  0x6B, 0x96, 0x18, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {48,     0,   8,  10,   9,    0,   -9 },   // 0x00 '0' 
  {49,    10,   6,  10,   9,    0,   -9 },   // 0x01 '1' 
  {50,    18,   8,  10,   9,   -1,   -9 },   // 0x02 '2' 
  {51,    28,   6,  10,   9,    1,   -9 },   // 0x03 '3' 
  {52,    36,   7,  10,   9,    0,   -9 },   // 0x04 '4' 
  {53,    45,   8,  10,   9,    0,   -9 },   // 0x05 '5' 
  {54,    55,   8,  10,   9,    0,   -9 },   // 0x06 '6' 
  {55,    65,   7,  10,   9,    0,   -9 },   // 0x07 '7' 
  {56,    74,   7,  10,   9,    0,   -9 },   // 0x08 '8' 
  {57,    83,   8,  10,   9,    0,   -9 },   // 0x09 '9' 
  {32,    93,   1,   1,   9,    0,    0 },   // 0x0A ' ' 
  {70,    94,   6,  10,   9,    1,   -9 },   // 0x0B 'F' 
  {67,   102,   8,  10,   9,    0,   -9 },   // 0x0C 'C' 
  {45,   112,   7,   1,   9,    0,   -3 },   // 0x0D '-' 
  {47,   113,   7,  13,   9,    0,  -10 },   // 0x0E '/' 
  {37,   125,   7,  11,   8,    0,  -10 },   // 0x0F '%' 
  {46,   135,   2,   2,   9,    3,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
    -1,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     8,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 269 bytes -  but your mileage may vary.

#endif