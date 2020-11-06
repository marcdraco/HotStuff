
#ifndef __FIXEDFONTGOMMOGRATTF8
#define __FIXEDFONTGOMMOGRATTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x00, 0x73, 0x35, 0x83, 0x7E, 0xDF, 0xEB, 0x99, 0xE3, 0xFC, 0x77, 0xAE,
  0x79, 0xEF, 0x3D, 0xF7, 0xBD, 0xF3, 0xFB, 0x7F, 0xE7, 0xD2, 0x10, 0x80,
  0x0E, 0xC0, 0x38, 0x5F, 0x6B, 0xFC, 0x1E, 0x83, 0x52, 0xE9, 0xED, 0x45,
  0xC8, 0xB5, 0x57, 0x27, 0xFC, 0xFF, 0xB6, 0xF0, 0x02, 0x00, 0x90, 0xEF,
  0xFF, 0x9F, 0xF3, 0x1E, 0x63, 0xA0, 0xE2, 0x3E, 0x6F, 0xFB, 0x8A, 0xE8,
  0x38, 0x77, 0xFF, 0xFF, 0x85, 0x11, 0xDD, 0x00, 0x0A, 0x09, 0xFF, 0x3F,
  0xEE, 0x30, 0x16, 0x01, 0x90, 0x7E, 0x0F, 0x94, 0xF8, 0xC7, 0x17, 0xEB,
  0xFC, 0x7F, 0xDB, 0xFC, 0x85, 0x00, 0x04, 0xE2, 0x9D, 0x6F, 0xA9, 0xF4,
  0xFE, 0xAE, 0xF1, 0x9D, 0x73, 0x2F, 0xFF, 0xFF, 0x81, 0xD2, 0xB8, 0x3F,
  0x15, 0xE0, 0x60, 0x00, 0x2F, 0xB9, 0xFF, 0x1F, 0xE7, 0x1D, 0x75, 0xAE,
  0x41, 0xFF, 0x3F, 0xC0, 0x38, 0x2F, 0x33, 0xE7, 0xDE, 0xFF, 0xDB, 0xFE,
  0x84, 0x00, 0x43, 0x07, 0xFF, 0x9F, 0xC3, 0x98, 0xFA, 0x1C, 0x0B, 0xF0,
  0x7F, 0x8E, 0x3B, 0xC7, 0xF8, 0xEB, 0xF9, 0xFF, 0xAF, 0xE8, 0x68, 0x01,
  0x02, 0x19, 0xFF, 0x3F, 0xEE, 0x3C, 0x0F, 0x00, 0xD1, 0x3A, 0x67, 0x33,
  0xEB, 0xB0, 0xC6, 0x5B, 0x97, 0x71, 0xAE, 0x00, 0x1F, 0x00, 0x03, 0xE0,
  0xFC, 0xDF, 0xC7, 0xF9, 0xE3, 0xBC, 0xF5, 0xFC, 0x7F, 0x8F, 0x7B, 0xC7,
  0x39, 0xE7, 0xF9, 0x7F, 0x27, 0xDA, 0x5C, 0x09, 0x88, 0x57, 0xFE, 0x9F,
  0xE7, 0x3F, 0xE3, 0xFC, 0x7B, 0xFE, 0x7F, 0xC2, 0x7B, 0x17, 0x5B, 0xEB,
  0xF9, 0x7F, 0xE3, 0xB0, 0x88, 0x00, 0x01, 0x4A, 0x28, 0x80, 0xBF, 0xFC,
  0xE2, 0x08, 0xAA, 0x80, 0x00, 0x00, 0x00, 0x30, 0x40, 0x08, 0x00, 0x08,
  0x00, 0x00, 0x20, 0x20, 0x00, 0x41, 0x0C, 0x10, 0x22, 0xC3, 0x0A, 0x24,
  0x00, 0x1C, 0x39, 0xC0, 0x00 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {32,     0,   1,   1,   6,    0,    0 },   // 0x00 ' ' 
  {48,     1,  11,  16,  11,    0,  -15 },   // 0x01 '0' 
  {49,    23,  11,  16,  11,    0,  -15 },   // 0x02 '1' 
  {50,    45,  11,  16,  11,    0,  -15 },   // 0x03 '2' 
  {51,    67,  11,  16,  11,    0,  -15 },   // 0x04 '3' 
  {52,    89,  11,  16,  11,    0,  -15 },   // 0x05 '4' 
  {53,   111,  11,  16,  11,    0,  -15 },   // 0x06 '5' 
  {54,   133,  11,  16,  11,    0,  -15 },   // 0x07 '6' 
  {55,   155,  11,  16,  11,    0,  -15 },   // 0x08 '7' 
  {56,   177,  11,  16,  11,    0,  -15 },   // 0x09 '8' 
  {57,   199,  11,  16,  11,    0,  -15 },   // 0x0A '9' 
  {45,   221,   6,  16,   7,    0,  -15 },   // 0x0B '-' 
  {37,   233,   6,  16,   6,    0,  -15 },   // 0x0C '%' 
  {46,   245,   6,  15,   6,    0,  -14 }   // 0x0D '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  14,// total glyphs in the string
  16,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
    11,  // maximum X - right most
    16}; // maximum Y - top most
// Approx. 369 bytes -  but your mileage may vary.

#endif