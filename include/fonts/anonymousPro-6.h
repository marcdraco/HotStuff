
#ifndef __FIXEDFONTANONYMOUSPROBOLDTTF6
#define __FIXEDFONTANONYMOUSPROBOLDTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x7B, 0x3D, 0xF7, 0xEF, 0xBC, 0xDE, 0x33, 0xBD, 0x63, 0x18, 0xCF, 0x76,
  0xF6, 0x33, 0x33, 0x7F, 0x76, 0xF6, 0x61, 0xEF, 0x6E, 0x18, 0xE7, 0x96,
  0xDB, 0xF1, 0x8F, 0xFB, 0x0C, 0x3E, 0x0C, 0x3C, 0xDE, 0x39, 0x8C, 0x3E,
  0xCF, 0x3C, 0xDE, 0xFF, 0x31, 0x86, 0x30, 0xC3, 0x0C, 0x7B, 0x3C, 0xDE,
  0xCF, 0x3C, 0xDE, 0x7B, 0x3C, 0xF3, 0x7C, 0x31, 0x9C, 0xFF, 0x0C, 0x3E,
  0xC3, 0x0C, 0x30, 0x3D, 0xBC, 0x30, 0xC3, 0x06, 0xCE, 0xFC, 0x0C, 0x31,
  0x86, 0x30, 0xC6, 0x18, 0xC3, 0x00, 0xE6, 0xAE, 0x84, 0x21, 0x75, 0x67,
  0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   6,   8,   7,    0,   -7 },   // 0x00 '0' 
  {49,     6,   5,   8,   7,    0,   -7 },   // 0x01 '1' 
  {50,    11,   5,   8,   7,    0,   -7 },   // 0x02 '2' 
  {51,    16,   5,   8,   7,    0,   -7 },   // 0x03 '3' 
  {52,    21,   6,   8,   7,    0,   -7 },   // 0x04 '4' 
  {53,    27,   6,   8,   7,    0,   -7 },   // 0x05 '5' 
  {54,    33,   6,   8,   7,    0,   -7 },   // 0x06 '6' 
  {55,    39,   6,   8,   7,    0,   -7 },   // 0x07 '7' 
  {56,    45,   6,   8,   7,    0,   -7 },   // 0x08 '8' 
  {57,    51,   6,   8,   7,    0,   -7 },   // 0x09 '9' 
  {32,    57,   0,   0,   7,    0,    1 },   // 0x0A ' ' 
  {70,    57,   6,   8,   7,    0,   -7 },   // 0x0B 'F' 
  {67,    63,   6,   8,   7,    0,   -7 },   // 0x0C 'C' 
  {45,    69,   6,   1,   7,    0,   -2 },   // 0x0D '-' 
  {47,    70,   6,  10,   7,    0,   -7 },   // 0x0E '/' 
  {37,    78,   6,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    84,   2,   2,   7,    2,   -1 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
     8}; // maximum Y - top most
// Approx. 218 bytes -  but your mileage may vary.

#endif