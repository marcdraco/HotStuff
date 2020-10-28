
#ifndef __FIXEDFONTKINGTHINGSTRYPEWRITERTTF6
#define __FIXEDFONTKINGTHINGSTRYPEWRITERTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x74, 0x63, 0x18, 0xC6, 0x2E, 0xE1, 0x08, 0x42, 0x10, 0x9F, 0xF4, 0x82,
  0x23, 0x22, 0x1F, 0xF9, 0x9C, 0x20, 0x84, 0x46, 0xC0, 0x11, 0x8C, 0xA5,
  0x7C, 0x42, 0xF4, 0x21, 0xE0, 0x84, 0x46, 0xC0, 0x32, 0x20, 0xE8, 0xC6,
  0x2E, 0xFC, 0x44, 0x22, 0x10, 0x84, 0x20, 0x79, 0x14, 0x5F, 0x6E, 0x18,
  0x5F, 0x54, 0x61, 0x17, 0x84, 0x02, 0x60, 0x00, 0xFA, 0x56, 0xA7, 0x29,
  0x1C, 0x7E, 0xE3, 0x08, 0x45, 0xCE, 0xF8, 0x11, 0x22, 0x44, 0x48, 0x88,
  0x6A, 0xAA, 0xAC, 0x7C, 0xD5, 0x53, 0x70 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   8,   7,    1,   -7 },   // 0x00 '0' 
  {49,     5,   5,   8,   7,    1,   -7 },   // 0x01 '1' 
  {50,    10,   5,   8,   7,    1,   -7 },   // 0x02 '2' 
  {51,    15,   5,   9,   7,    1,   -7 },   // 0x03 '3' 
  {52,    21,   5,   8,   7,    1,   -7 },   // 0x04 '4' 
  {53,    26,   5,   9,   7,    1,   -7 },   // 0x05 '5' 
  {54,    32,   5,   8,   7,    1,   -7 },   // 0x06 '6' 
  {55,    37,   5,   9,   7,    1,   -7 },   // 0x07 '7' 
  {56,    43,   6,   8,   7,    0,   -7 },   // 0x08 '8' 
  {57,    49,   5,   9,   7,    1,   -7 },   // 0x09 '9' 
  {32,    55,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    56,   5,   8,   7,    1,   -7 },   // 0x0B 'F' 
  {67,    61,   5,   8,   7,    1,   -6 },   // 0x0C 'C' 
  {45,    66,   5,   1,   7,    1,   -3 },   // 0x0D '-' 
  {47,    67,   4,  10,   7,    1,   -8 },   // 0x0E '/' 
  {37,    72,   6,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    78,   2,   2,   7,    2,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
     9}; // maximum Y - top most
// Approx. 212 bytes -  but your mileage may vary.

#endif