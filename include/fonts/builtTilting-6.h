
#ifndef __FIXEDFONTBUILTTITLINGRGTTF6
#define __FIXEDFONTBUILTTITLINGRGTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x69, 0x99, 0x99, 0x99, 0x96, 0x22, 0xE6, 0x66, 0x66, 0x6F, 0x69, 0x99,
  0x12, 0x24, 0xCF, 0x69, 0x91, 0x61, 0x99, 0x96, 0x22, 0x66, 0x66, 0xAF,
  0x22, 0x74, 0x4E, 0x51, 0x99, 0x96, 0x69, 0x98, 0xE9, 0x99, 0x96, 0xF3,
  0x22, 0x22, 0x64, 0x44, 0x69, 0x99, 0x69, 0x99, 0x96, 0x69, 0x99, 0x9F,
  0x22, 0x24, 0x00, 0xF2, 0x49, 0xE4, 0x90, 0x6D, 0x99, 0x88, 0x99, 0xF6,
  0xE0, 0x11, 0x22, 0x22, 0x24, 0x44, 0x48, 0x80, 0xCE, 0x75, 0xAE, 0x7C,
  0xEB, 0x5A, 0xC0, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   4,  10,   4,    0,   -9 },   // 0x00 '0' 
  {49,     5,   4,  10,   4,    0,   -9 },   // 0x01 '1' 
  {50,    10,   4,  10,   4,    0,   -9 },   // 0x02 '2' 
  {51,    15,   4,  10,   4,    0,   -9 },   // 0x03 '3' 
  {52,    20,   4,  10,   4,    0,   -9 },   // 0x04 '4' 
  {53,    25,   4,  10,   4,    0,   -9 },   // 0x05 '5' 
  {54,    30,   4,  10,   4,    0,   -9 },   // 0x06 '6' 
  {55,    35,   4,  10,   4,    0,   -9 },   // 0x07 '7' 
  {56,    40,   4,  10,   4,    0,   -9 },   // 0x08 '8' 
  {57,    45,   4,  10,   4,    0,   -9 },   // 0x09 '9' 
  {32,    50,   1,   1,   2,    0,    0 },   // 0x0A ' ' 
  {70,    51,   3,  10,   3,    0,   -9 },   // 0x0B 'F' 
  {67,    55,   4,  10,   4,    0,   -9 },   // 0x0C 'C' 
  {45,    60,   3,   1,   3,    0,   -5 },   // 0x0D '-' 
  {47,    61,   4,  13,   4,    0,  -10 },   // 0x0E '/' 
  {37,    68,   5,  10,   5,    0,   -9 },   // 0x0F '%' 
  {46,    75,   1,   1,   2,    0,    0 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     5,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 209 bytes -  but your mileage may vary.

#endif