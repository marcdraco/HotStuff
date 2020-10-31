
#ifndef __FIXEDFONTDIGITALMONOTTF6
#define __FIXEDFONTDIGITALMONOTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0xFC, 0x63, 0x18, 0xC6, 0x3F, 0xFF, 0xF8, 0x42, 0x1F, 0x42, 0x1E, 0xF8,
  0x42, 0x17, 0x84, 0x3F, 0x0C, 0x63, 0x17, 0x84, 0x21, 0xF4, 0x21, 0x07,
  0x84, 0x3F, 0xF4, 0x21, 0x0F, 0xC6, 0x3F, 0xFC, 0x63, 0x10, 0x84, 0x21,
  0xFC, 0x63, 0x1F, 0xC6, 0x3F, 0xFC, 0x63, 0x17, 0x84, 0x3F, 0x00, 0xF8,
  0x88, 0xF8, 0x88, 0xF8, 0x88, 0x88, 0x8F, 0xE0, 0x08, 0x84, 0x02, 0x31,
  0x18, 0xEA, 0xAF, 0x04, 0x20, 0xF5, 0x57, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   8,   5,    0,   -7 },   // 0x00 '0' 
  {49,     5,   1,   8,   5,    4,   -7 },   // 0x01 '1' 
  {50,     6,   5,   8,   5,    0,   -7 },   // 0x02 '2' 
  {51,    11,   5,   8,   5,    0,   -7 },   // 0x03 '3' 
  {52,    16,   5,   8,   5,    0,   -7 },   // 0x04 '4' 
  {53,    21,   5,   8,   5,    0,   -7 },   // 0x05 '5' 
  {54,    26,   5,   8,   5,    0,   -7 },   // 0x06 '6' 
  {55,    31,   5,   8,   5,    0,   -7 },   // 0x07 '7' 
  {56,    36,   5,   8,   5,    0,   -7 },   // 0x08 '8' 
  {57,    41,   5,   8,   5,    0,   -7 },   // 0x09 '9' 
  {32,    46,   1,   1,   5,    0,    0 },   // 0x0A ' ' 
  {70,    47,   4,   8,   5,    0,   -7 },   // 0x0B 'F' 
  {67,    51,   4,   8,   5,    0,   -7 },   // 0x0C 'C' 
  {45,    55,   3,   1,   5,    1,   -3 },   // 0x0D '-' 
  {47,    56,   5,   8,   5,    0,   -7 },   // 0x0E '/' 
  {37,    61,   6,   8,   5,    0,   -7 },   // 0x0F '%' 
  {46,    67,   1,   1,   5,    2,    0 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
     8}; // maximum Y - top most
// Approx. 201 bytes -  but your mileage may vary.

#endif