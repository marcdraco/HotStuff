
#ifndef __FIXEDFONTIBMPLEXMONOMEDIUMTTF6
#define __FIXEDFONTIBMPLEXMONOMEDIUMTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x38, 0x89, 0x16, 0xBD, 0x68, 0x91, 0x1C, 0x38, 0xF3, 0x60, 0xC1, 0x83,
  0x06, 0x3F, 0x74, 0x42, 0x33, 0x33, 0x1F, 0x79, 0x10, 0x4E, 0x04, 0x14,
  0x7E, 0x1C, 0x38, 0xB2, 0x64, 0xDF, 0xC3, 0x06, 0xFC, 0x21, 0x7C, 0x86,
  0x2E, 0x31, 0x0C, 0x3E, 0x8A, 0x38, 0x9C, 0xFC, 0x46, 0x23, 0x10, 0x8C,
  0x7C, 0x89, 0x11, 0xC4, 0x58, 0xD1, 0x1C, 0x39, 0x1C, 0x51, 0x7C, 0x30,
  0x8C, 0x00, 0xFC, 0x21, 0xF8, 0x42, 0x10, 0x7E, 0x61, 0x08, 0x43, 0x2F,
  0xE0, 0x08, 0xC4, 0x22, 0x10, 0x88, 0x46, 0x20, 0x63, 0x2A, 0x63, 0x00,
  0xC6, 0x54, 0xC6, 0x5C };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   7,   8,   7,    0,   -7 },   // 0x00 '0' 
  {49,     7,   7,   8,   7,    0,   -7 },   // 0x01 '1' 
  {50,    14,   5,   8,   7,    1,   -7 },   // 0x02 '2' 
  {51,    19,   6,   8,   7,    0,   -7 },   // 0x03 '3' 
  {52,    25,   7,   8,   7,    0,   -7 },   // 0x04 '4' 
  {53,    32,   5,   8,   7,    1,   -7 },   // 0x05 '5' 
  {54,    37,   6,   8,   7,    1,   -7 },   // 0x06 '6' 
  {55,    43,   5,   8,   7,    1,   -7 },   // 0x07 '7' 
  {56,    48,   7,   8,   7,    0,   -7 },   // 0x08 '8' 
  {57,    55,   6,   8,   7,    0,   -7 },   // 0x09 '9' 
  {32,    61,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    62,   5,   8,   7,    1,   -7 },   // 0x0B 'F' 
  {67,    67,   5,   8,   7,    1,   -7 },   // 0x0C 'C' 
  {45,    72,   3,   1,   7,    2,   -3 },   // 0x0D '-' 
  {47,    73,   5,  11,   7,    1,   -8 },   // 0x0E '/' 
  {37,    80,   7,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    87,   3,   2,   7,    2,   -1 }   // 0x10 '.' 
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
     9}; // maximum Y - top most
// Approx. 221 bytes -  but your mileage may vary.

#endif