
#ifndef __FIXEDFONTANONYMOUSPROBOLDTTF12
#define __FIXEDFONTANONYMOUSPROBOLDTTF12
const uint8_t HotStuff12Bitmaps[] PROGMEM = {
  0x00, 0x1F, 0x07, 0xF1, 0xC7, 0x30, 0x6C, 0x1F, 0x87, 0xF1, 0xDE, 0x73,
  0xDC, 0x7F, 0x0F, 0xC1, 0xB0, 0x67, 0x1C, 0x7F, 0x07, 0xC0, 0x0C, 0x0C,
  0x1C, 0x3C, 0xFC, 0xCC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F,
  0x3F, 0x3E, 0x1F, 0xEE, 0x3B, 0x07, 0xC1, 0xC0, 0x70, 0x38, 0x1E, 0x0F,
  0x07, 0x83, 0xC1, 0xE6, 0xE1, 0xBF, 0xEF, 0xF8, 0x1F, 0x0F, 0xE7, 0x1D,
  0x83, 0x60, 0xC0, 0x70, 0xFC, 0x3E, 0x01, 0x80, 0x3C, 0x0F, 0x83, 0x71,
  0xDF, 0xE1, 0xF0, 0x07, 0x00, 0xE0, 0x3C, 0x0F, 0x81, 0xB0, 0x66, 0x1C,
  0xC3, 0x18, 0xC3, 0x1F, 0xFF, 0xFF, 0x81, 0x80, 0x30, 0x1F, 0xC3, 0xF8,
  0x7F, 0xCF, 0xF9, 0x80, 0x30, 0x06, 0x00, 0xDE, 0x1F, 0xF3, 0x86, 0x00,
  0x60, 0x0F, 0x81, 0xB0, 0x37, 0x0C, 0x7F, 0x87, 0xC0, 0x1F, 0x07, 0xF9,
  0xC2, 0x30, 0x0C, 0xF1, 0xBF, 0x3C, 0x77, 0x07, 0xC0, 0x78, 0x0F, 0x01,
  0xB0, 0x37, 0x0C, 0x7F, 0x87, 0xC0, 0xFF, 0xFF, 0xFC, 0x1B, 0x04, 0xC3,
  0x01, 0x80, 0x40, 0x30, 0x0C, 0x02, 0x01, 0x80, 0x60, 0x18, 0x06, 0x01,
  0x80, 0x3F, 0x1F, 0xEE, 0x1F, 0x03, 0xC0, 0xD8, 0x63, 0xF0, 0xFC, 0x61,
  0xB0, 0x3C, 0x0F, 0x03, 0xE1, 0xDF, 0xE3, 0xF0, 0x1F, 0x0F, 0xF1, 0x83,
  0x60, 0x2C, 0x07, 0x80, 0xF0, 0x1B, 0x07, 0x7F, 0xE3, 0xEC, 0x01, 0x80,
  0x62, 0x1C, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFC, 0x00, 0x4F, 0x0F, 0xF3,
  0x66, 0xEC, 0xD9, 0xFE, 0x1F, 0xC0, 0x30, 0x0C, 0x03, 0x80, 0x67, 0x19,
  0xF7, 0x36, 0xC6, 0xF0, 0xFA, 0x0E, 0xFF, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff12Glyphs[] PROGMEM = {
  {32,     0,   1,   1,  13,    0,    0 },   // 0x00 ' ' 
  {48,     1,  11,  15,  13,    0,  -14 },   // 0x01 '0' 
  {49,    22,   8,  15,  13,    0,  -14 },   // 0x02 '1' 
  {50,    37,  10,  15,  13,    1,  -14 },   // 0x03 '2' 
  {51,    56,  10,  15,  13,    0,  -14 },   // 0x04 '3' 
  {52,    75,  11,  15,  13,    0,  -14 },   // 0x05 '4' 
  {53,    96,  11,  15,  13,    0,  -14 },   // 0x06 '5' 
  {54,   117,  11,  15,  13,    0,  -14 },   // 0x07 '6' 
  {55,   138,  10,  15,  13,    1,  -14 },   // 0x08 '7' 
  {56,   157,  10,  15,  13,    0,  -14 },   // 0x09 '8' 
  {57,   176,  11,  15,  13,    0,  -14 },   // 0x0A '9' 
  {45,   197,  11,   2,  13,    0,   -6 },   // 0x0B '-' 
  {37,   200,  11,  16,  13,    0,  -15 },   // 0x0C '%' 
  {46,   222,   3,   3,  13,    4,   -2 }   // 0x0D '.' 
};

const gfxfont_t HotStuff12 PROGMEM = 
{
  (uint8_t  *)HotStuff12Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff12Glyphs, //< Glyph array
  14,// total glyphs in the string
  16,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
    11,  // maximum X - right most
    16}; // maximum Y - top most
// Approx. 336 bytes -  but your mileage may vary.

#endif