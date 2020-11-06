
#ifndef __FIXEDFONTDEALERPLATECALIFORNIATTF8
#define __FIXEDFONTDEALERPLATECALIFORNIATTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x00, 0x69, 0x99, 0x99, 0x99, 0x99, 0x99, 0x60, 0x67, 0x18, 0xC6, 0x31,
  0x8C, 0x63, 0x18, 0xCF, 0x80, 0x74, 0x86, 0x21, 0x18, 0x88, 0x44, 0x21,
  0x0F, 0x80, 0x69, 0x11, 0x11, 0x31, 0x11, 0x19, 0xF0, 0x44, 0x44, 0x4C,
  0x89, 0x99, 0xF1, 0x10, 0xF8, 0x88, 0x8F, 0x91, 0x11, 0x19, 0x70, 0x32,
  0x64, 0xC8, 0xF9, 0x99, 0x99, 0x60, 0xF8, 0xC4, 0x23, 0x10, 0x84, 0x62,
  0x10, 0x84, 0x00, 0x69, 0x99, 0x99, 0xF9, 0x99, 0x99, 0x70, 0x69, 0x99,
  0x99, 0xF1, 0x12, 0x24, 0xC0, 0xE0, 0xE6, 0xAA, 0xAA, 0xF0, 0x41, 0x08,
  0x3D, 0x55, 0x55, 0x9C, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {32,     0,   1,   1,   3,    0,    0 },   // 0x00 ' ' 
  {48,     1,   4,  13,   6,    1,  -12 },   // 0x01 '0' 
  {49,     8,   5,  13,   6,    1,  -12 },   // 0x02 '1' 
  {50,    17,   5,  13,   6,    1,  -12 },   // 0x03 '2' 
  {51,    26,   4,  13,   6,    1,  -12 },   // 0x04 '3' 
  {52,    33,   4,  13,   6,    1,  -12 },   // 0x05 '4' 
  {53,    40,   4,  13,   6,    1,  -12 },   // 0x06 '5' 
  {54,    47,   4,  13,   6,    1,  -12 },   // 0x07 '6' 
  {55,    54,   5,  13,   6,    1,  -12 },   // 0x08 '7' 
  {56,    63,   4,  13,   6,    1,  -12 },   // 0x09 '8' 
  {57,    70,   4,  13,   6,    1,  -12 },   // 0x0A '9' 
  {45,    77,   3,   1,   3,    0,   -6 },   // 0x0B '-' 
  {37,    78,   6,  13,   6,    0,  -12 },   // 0x0C '%' 
  {46,    88,   1,   1,   3,    1,    0 }   // 0x0D '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  14,// total glyphs in the string
  13,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
    13}; // maximum Y - top most
// Approx. 201 bytes -  but your mileage may vary.

#endif