
#ifndef __FIXEDFONTSOURCECODEPROBOLDTTF6
#define __FIXEDFONTSOURCECODEPROBOLDTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x73, 0x68, 0xAB, 0xBE, 0x2D, 0x9C, 0x77, 0x8C, 0x63, 0x18, 0xDF, 0xF4,
  0xC6, 0x31, 0x19, 0x9F, 0x79, 0x30, 0xC3, 0x38, 0x34, 0xFE, 0x1C, 0x38,
  0xB3, 0x64, 0xDF, 0xC3, 0x06, 0xFE, 0x31, 0xF1, 0x86, 0x7E, 0x7B, 0x2C,
  0x2E, 0xCB, 0x3C, 0x9C, 0xF8, 0xC4, 0x62, 0x11, 0x8C, 0x7E, 0x7E, 0xFD,
  0xC7, 0x2E, 0x76, 0xE3, 0x3E, 0x86, 0x7E, 0x00, 0xFE, 0x31, 0x8F, 0xE3,
  0x18, 0x7B, 0x3C, 0x20, 0x83, 0x0C, 0x9F, 0xF8, 0x08, 0xC4, 0x63, 0x11,
  0x88, 0xC6, 0x00, 0xE1, 0x46, 0x97, 0x40, 0xE5, 0x52, 0xE7, 0x7D, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   6,   8,   7,    1,   -7 },   // 0x00 '0' 
  {49,     6,   5,   8,   7,    1,   -7 },   // 0x01 '1' 
  {50,    11,   5,   8,   7,    1,   -7 },   // 0x02 '2' 
  {51,    16,   6,   8,   7,    0,   -7 },   // 0x03 '3' 
  {52,    22,   7,   8,   7,    0,   -7 },   // 0x04 '4' 
  {53,    29,   5,   8,   7,    1,   -7 },   // 0x05 '5' 
  {54,    34,   6,   8,   7,    1,   -7 },   // 0x06 '6' 
  {55,    40,   5,   8,   7,    1,   -7 },   // 0x07 '7' 
  {56,    45,   5,   8,   7,    1,   -7 },   // 0x08 '8' 
  {57,    50,   5,   8,   7,    1,   -7 },   // 0x09 '9' 
  {32,    55,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    56,   5,   8,   7,    1,   -7 },   // 0x0B 'F' 
  {67,    61,   6,   8,   7,    1,   -7 },   // 0x0C 'C' 
  {45,    67,   5,   1,   7,    1,   -3 },   // 0x0D '-' 
  {47,    68,   5,  10,   7,    1,   -7 },   // 0x0E '/' 
  {37,    75,   7,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    82,   3,   3,   7,    2,   -2 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
    -2,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
     8}; // maximum Y - top most
// Approx. 217 bytes -  but your mileage may vary.

#endif