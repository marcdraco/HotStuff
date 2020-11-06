
#ifndef __FIXEDFONTREPETTTF12
#define __FIXEDFONTREPETTTF12
const uint8_t HotStuff12Bitmaps[] PROGMEM = {
  0x00, 0x37, 0x86, 0xF3, 0x01, 0xE0, 0x3C, 0x07, 0x80, 0xC0, 0x06, 0x03,
  0xC0, 0x78, 0x0F, 0x01, 0x80, 0x0C, 0x07, 0x80, 0xCD, 0xE1, 0xBC, 0x18,
  0x33, 0x66, 0xC1, 0x83, 0x00, 0x0C, 0x18, 0x30, 0x60, 0x01, 0x83, 0x37,
  0xEF, 0x37, 0x86, 0xF3, 0x01, 0xE0, 0x30, 0x06, 0x00, 0xC0, 0x00, 0x0C,
  0x01, 0x80, 0xC0, 0x18, 0x00, 0x03, 0x00, 0x60, 0x3D, 0xFF, 0xBF, 0x37,
  0x86, 0xF3, 0x01, 0xE0, 0x30, 0x06, 0x00, 0xC0, 0x01, 0xBC, 0x37, 0x80,
  0x0C, 0x01, 0x80, 0x0C, 0x07, 0x80, 0xCD, 0xE1, 0xBC, 0x01, 0x80, 0x30,
  0x1E, 0x03, 0xC3, 0x18, 0x63, 0x00, 0x06, 0x0C, 0xC1, 0x9E, 0xFF, 0xDF,
  0x80, 0x00, 0x18, 0x03, 0x00, 0x60, 0x0C, 0xF7, 0xFE, 0xFF, 0x00, 0x60,
  0x0F, 0x79, 0xEF, 0x00, 0x00, 0x03, 0x00, 0x60, 0x0C, 0x01, 0x80, 0x0C,
  0x07, 0x80, 0xCD, 0xE1, 0xBC, 0x07, 0x80, 0xF0, 0xC0, 0x18, 0x0C, 0x01,
  0x80, 0x00, 0x07, 0xBC, 0xF7, 0x98, 0x0F, 0x01, 0x80, 0x0C, 0x07, 0x80,
  0xCD, 0xE1, 0xBC, 0xF7, 0xFE, 0xFC, 0x01, 0x80, 0x30, 0x18, 0x03, 0x00,
  0x00, 0x30, 0x06, 0x06, 0x00, 0xC0, 0x00, 0x0C, 0x01, 0x80, 0x30, 0x06,
  0x00, 0x37, 0x86, 0xF3, 0x01, 0xE0, 0x3C, 0x07, 0x80, 0xC0, 0x01, 0xBC,
  0x37, 0x98, 0x0F, 0x01, 0x80, 0x0C, 0x07, 0x80, 0xCD, 0xE1, 0xBC, 0x37,
  0x86, 0xF3, 0x01, 0xE0, 0x3C, 0x07, 0x80, 0xC0, 0x01, 0xBF, 0x37, 0xE0,
  0x0C, 0x01, 0x80, 0x00, 0x18, 0x03, 0x0D, 0x81, 0xB0, 0xFF, 0xF0, 0xF0,
  0x7E, 0x0F, 0xC1, 0xF8, 0x30, 0x1E, 0x03, 0xC0, 0x00, 0x30, 0x06, 0x06,
  0x00, 0xC0, 0x00, 0x0C, 0x1F, 0x83, 0xF0, 0x7E, 0x0F, 0xFF, 0xFF };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff12Glyphs[] PROGMEM = {
  {32,     0,   1,   1,  13,    0,    0 },   // 0x00 ' ' 
  {48,     1,  11,  16,  13,    1,  -15 },   // 0x01 '0' 
  {49,    23,   7,  16,  13,    3,  -15 },   // 0x02 '1' 
  {50,    37,  11,  16,  13,    1,  -15 },   // 0x03 '2' 
  {51,    59,  11,  16,  13,    1,  -15 },   // 0x04 '3' 
  {52,    81,  11,  16,  13,    1,  -15 },   // 0x05 '4' 
  {53,   103,  11,  16,  13,    1,  -15 },   // 0x06 '5' 
  {54,   125,  11,  16,  13,    1,  -15 },   // 0x07 '6' 
  {55,   147,  11,  16,  13,    1,  -15 },   // 0x08 '7' 
  {56,   169,  11,  16,  13,    1,  -15 },   // 0x09 '8' 
  {57,   191,  11,  16,  13,    1,  -15 },   // 0x0A '9' 
  {45,   213,   6,   2,  13,    3,   -6 },   // 0x0B '-' 
  {37,   215,  11,  16,  13,    1,  -15 },   // 0x0C '%' 
  {46,   237,   4,   4,  13,    4,   -3 }   // 0x0D '.' 
};

const gfxfont_t HotStuff12 PROGMEM = 
{
  (uint8_t  *)HotStuff12Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff12Glyphs, //< Glyph array
  14,// total glyphs in the string
  16,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
    12,  // maximum X - right most
    16}; // maximum Y - top most
// Approx. 351 bytes -  but your mileage may vary.

#endif