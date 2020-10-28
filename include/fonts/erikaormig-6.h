
#ifndef __FIXEDFONTERIKAORMIGTTF6
#define __FIXEDFONTERIKAORMIGTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x77, 0xE3, 0x18, 0xE5, 0xC0, 0x3C, 0x92, 0x48, 0x74, 0x42, 0x26, 0x43,
  0xE0, 0x74, 0x42, 0x70, 0x84, 0x5C, 0x31, 0x9C, 0xAD, 0x7C, 0x42, 0xFC,
  0x3D, 0x10, 0x84, 0xDC, 0x3B, 0x11, 0x4D, 0xC5, 0x2E, 0xFA, 0x71, 0x0C,
  0x20, 0x82, 0x08, 0x74, 0x63, 0xE8, 0xC7, 0xC0, 0x76, 0xE3, 0xB7, 0x84,
  0x5C, 0x00, 0xFA, 0x56, 0xE5, 0x23, 0xC0, 0x7D, 0xBC, 0xE0, 0xCD, 0x77,
  0x80, 0xFF, 0xC0, 0x08, 0x44, 0x22, 0x31, 0x08, 0xC4, 0x00, 0x0C, 0xF2,
  0xE5, 0x8D, 0x45, 0x4C, 0xA6, 0xC0, 0x7D, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   7,   7,    1,   -6 },   // 0x00 '0' 
  {49,     5,   3,   7,   7,    2,   -6 },   // 0x01 '1' 
  {50,     8,   5,   7,   7,    1,   -6 },   // 0x02 '2' 
  {51,    13,   5,   8,   7,    1,   -6 },   // 0x03 '3' 
  {52,    18,   5,   8,   7,    1,   -6 },   // 0x04 '4' 
  {53,    23,   5,   8,   7,    1,   -6 },   // 0x05 '5' 
  {54,    28,   5,   8,   7,    1,   -7 },   // 0x06 '6' 
  {55,    33,   6,   8,   7,    1,   -6 },   // 0x07 '7' 
  {56,    39,   5,   7,   7,    1,   -6 },   // 0x08 '8' 
  {57,    44,   5,   8,   7,    1,   -6 },   // 0x09 '9' 
  {32,    49,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    50,   5,   7,   7,    1,   -6 },   // 0x0B 'F' 
  {67,    55,   6,   7,   8,    1,   -6 },   // 0x0C 'C' 
  {45,    61,   5,   2,   7,    1,   -3 },   // 0x0D '-' 
  {47,    63,   5,  10,   7,    1,   -8 },   // 0x0E '/' 
  {37,    70,   7,   9,   7,    0,   -7 },   // 0x0F '%' 
  {46,    78,   3,   3,   7,    2,   -2 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   7,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
     9}; // maximum Y - top most
// Approx. 213 bytes -  but your mileage may vary.

#endif