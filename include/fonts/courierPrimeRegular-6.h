
#ifndef __FIXEDFONTCOURIERPRIMEREGULARTTF6
#define __FIXEDFONTCOURIERPRIMEREGULARTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x74, 0x63, 0x18, 0xC6, 0x2E, 0x23, 0x28, 0x42, 0x10, 0x9F, 0x74, 0x42,
  0x11, 0x11, 0x3F, 0x74, 0x42, 0x60, 0x86, 0x2E, 0x11, 0x94, 0xA9, 0x7C,
  0x47, 0xFC, 0x21, 0xE0, 0x86, 0x2E, 0x3A, 0x21, 0xE8, 0xC6, 0x2E, 0xFC,
  0x44, 0x22, 0x11, 0x08, 0x74, 0x62, 0xE8, 0xC6, 0x2E, 0x74, 0x63, 0x17,
  0x84, 0x5C, 0x00, 0xFD, 0x14, 0x10, 0x79, 0x04, 0x3C, 0x7C, 0x63, 0x08,
  0x42, 0x2E, 0xF8, 0x08, 0x44, 0x22, 0x11, 0x08, 0x44, 0x00, 0x60, 0x92,
  0x94, 0x68, 0x16, 0x29, 0x49, 0x06, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   8,   7,    1,   -7 },   // 0x00 '0' 
  {49,     5,   5,   8,   7,    1,   -7 },   // 0x01 '1' 
  {50,    10,   5,   8,   7,    1,   -7 },   // 0x02 '2' 
  {51,    15,   5,   8,   7,    1,   -7 },   // 0x03 '3' 
  {52,    20,   5,   8,   7,    1,   -7 },   // 0x04 '4' 
  {53,    25,   5,   8,   7,    1,   -7 },   // 0x05 '5' 
  {54,    30,   5,   8,   7,    1,   -7 },   // 0x06 '6' 
  {55,    35,   5,   8,   7,    1,   -7 },   // 0x07 '7' 
  {56,    40,   5,   8,   7,    1,   -7 },   // 0x08 '8' 
  {57,    45,   5,   8,   7,    1,   -7 },   // 0x09 '9' 
  {32,    50,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    51,   6,   8,   7,    0,   -7 },   // 0x0B 'F' 
  {67,    57,   5,   8,   7,    1,   -7 },   // 0x0C 'C' 
  {45,    62,   5,   1,   7,    1,   -3 },   // 0x0D '-' 
  {47,    63,   5,  10,   7,    1,   -7 },   // 0x0E '/' 
  {37,    70,   8,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    78,   2,   2,   7,    2,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     8,  // maximum X - right most
     8}; // maximum Y - top most
// Approx. 212 bytes -  but your mileage may vary.

#endif