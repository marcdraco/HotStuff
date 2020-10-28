
#ifndef __FIXEDFONTDEALERPLATECALIFORNIATTF8
#define __FIXEDFONTDEALERPLATECALIFORNIATTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x69, 0x99, 0x99, 0x99, 0x99, 0x99, 0x60, 0x67, 0x18, 0xC6, 0x31, 0x8C,
  0x63, 0x18, 0xCF, 0x80, 0x74, 0x86, 0x21, 0x18, 0x88, 0x44, 0x21, 0x0F,
  0x80, 0x69, 0x11, 0x11, 0x31, 0x11, 0x19, 0xF0, 0x44, 0x44, 0x4C, 0x89,
  0x99, 0xF1, 0x10, 0xF8, 0x88, 0x8F, 0x91, 0x11, 0x19, 0x70, 0x32, 0x64,
  0xC8, 0xF9, 0x99, 0x99, 0x60, 0xF8, 0xC4, 0x23, 0x10, 0x84, 0x62, 0x10,
  0x84, 0x00, 0x69, 0x99, 0x99, 0xF9, 0x99, 0x99, 0x70, 0x69, 0x99, 0x99,
  0xF1, 0x12, 0x24, 0xC0, 0x00, 0xFC, 0x21, 0x08, 0x43, 0xD0, 0x84, 0x21,
  0x08, 0x00, 0x69, 0x98, 0x88, 0x88, 0x89, 0x99, 0x60, 0xE0, 0x24, 0x94,
  0x92, 0x49, 0x49, 0x00, 0xE6, 0xAA, 0xAA, 0xF0, 0x41, 0x08, 0x3D, 0x55,
  0x55, 0x9C, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {48,     0,   4,  13,   6,    1,  -12 },   // 0x00 '0' 
  {49,     7,   5,  13,   6,    1,  -12 },   // 0x01 '1' 
  {50,    16,   5,  13,   6,    1,  -12 },   // 0x02 '2' 
  {51,    25,   4,  13,   6,    1,  -12 },   // 0x03 '3' 
  {52,    32,   4,  13,   6,    1,  -12 },   // 0x04 '4' 
  {53,    39,   4,  13,   6,    1,  -12 },   // 0x05 '5' 
  {54,    46,   4,  13,   6,    1,  -12 },   // 0x06 '6' 
  {55,    53,   5,  13,   6,    1,  -12 },   // 0x07 '7' 
  {56,    62,   4,  13,   6,    1,  -12 },   // 0x08 '8' 
  {57,    69,   4,  13,   6,    1,  -12 },   // 0x09 '9' 
  {32,    76,   1,   1,   3,    0,    0 },   // 0x0A ' ' 
  {70,    77,   5,  13,   6,    1,  -12 },   // 0x0B 'F' 
  {67,    86,   4,  13,   6,    1,  -12 },   // 0x0C 'C' 
  {45,    93,   3,   1,   3,    0,   -6 },   // 0x0D '-' 
  {47,    94,   3,  14,   3,    0,  -12 },   // 0x0E '/' 
  {37,   100,   6,  13,   6,    0,  -12 },   // 0x0F '%' 
  {46,   110,   1,   1,   3,    1,    0 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  17,// total glyphs in the string
  13,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
    13}; // maximum Y - top most
// Approx. 244 bytes -  but your mileage may vary.

#endif