
#ifndef __FIXEDFONTCOURIERPRIMEBOLDTTF6
#define __FIXEDFONTCOURIERPRIMEBOLDTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x76, 0xF7, 0xBD, 0xEF, 0x6E, 0x27, 0x08, 0x42, 0x10, 0x9F, 0xF4, 0x42,
  0x33, 0x33, 0x3F, 0xF4, 0xC6, 0xE1, 0x8C, 0x7E, 0x11, 0x8C, 0xE5, 0x7C,
  0x47, 0xFC, 0x21, 0xE1, 0x8C, 0x7E, 0x19, 0x8C, 0x3C, 0xCB, 0x2C, 0x9C,
  0xFC, 0xC4, 0x63, 0x11, 0x88, 0x74, 0x63, 0x17, 0x6F, 0x6E, 0x74, 0xE7,
  0x37, 0x8C, 0xDC, 0x00, 0xFD, 0x14, 0x10, 0x79, 0x04, 0x3C, 0x7A, 0x71,
  0x8C, 0x61, 0x0F, 0xF8, 0x08, 0xC4, 0x63, 0x11, 0x88, 0xC4, 0x00, 0xC1,
  0x42, 0x9E, 0x41, 0x04, 0xD2, 0xC3, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   8,   7,    1,   -7 },   // 0x00 '0' 
  {49,     5,   5,   8,   7,    1,   -7 },   // 0x01 '1' 
  {50,    10,   5,   8,   7,    1,   -7 },   // 0x02 '2' 
  {51,    15,   5,   8,   7,    1,   -7 },   // 0x03 '3' 
  {52,    20,   5,   8,   7,    1,   -7 },   // 0x04 '4' 
  {53,    25,   5,   8,   7,    1,   -7 },   // 0x05 '5' 
  {54,    30,   6,   8,   7,    1,   -7 },   // 0x06 '6' 
  {55,    36,   5,   8,   7,    1,   -7 },   // 0x07 '7' 
  {56,    41,   5,   8,   7,    1,   -7 },   // 0x08 '8' 
  {57,    46,   5,   8,   7,    1,   -7 },   // 0x09 '9' 
  {32,    51,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    52,   6,   8,   7,    0,   -7 },   // 0x0B 'F' 
  {67,    58,   5,   8,   7,    1,   -7 },   // 0x0C 'C' 
  {45,    63,   5,   1,   7,    1,   -3 },   // 0x0D '-' 
  {47,    64,   5,  10,   7,    1,   -7 },   // 0x0E '/' 
  {37,    71,   7,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    78,   2,   2,   7,    3,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
     8}; // maximum Y - top most
// Approx. 212 bytes -  but your mileage may vary.

#endif