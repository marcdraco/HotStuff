
#ifndef __FIXEDFONTREPETTTF8
#define __FIXEDFONTREPETTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x00, 0x5C, 0x02, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x82, 0x01, 0x70, 0x20,
  0x28, 0x42, 0x10, 0x84, 0x20, 0x2E, 0x5C, 0x02, 0x08, 0x10, 0x21, 0x84,
  0x08, 0x40, 0x03, 0x78, 0x5C, 0x02, 0x08, 0x10, 0x2B, 0x80, 0x81, 0x82,
  0x01, 0x70, 0x0C, 0x00, 0x72, 0x64, 0xD1, 0xB7, 0xEF, 0x0C, 0x00, 0x30,
  0xDE, 0x02, 0x06, 0xED, 0xC0, 0x40, 0x81, 0x82, 0x01, 0x70, 0x1C, 0x01,
  0x04, 0x08, 0x1B, 0xA0, 0xC1, 0x82, 0x01, 0x70, 0xDE, 0x00, 0x08, 0x60,
  0xC2, 0x10, 0x20, 0x80, 0x02, 0x00, 0x5C, 0x02, 0x0C, 0x18, 0x2B, 0xA0,
  0xC1, 0x82, 0x01, 0x70, 0x5C, 0x02, 0x0C, 0x18, 0x2B, 0xC0, 0x81, 0x0C,
  0x01, 0x40, 0xAD, 0x40, 0xC2, 0x03, 0x08, 0x70, 0xE2, 0x10, 0x20, 0x8E,
  0x02, 0x38, 0xA2, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {32,     0,   1,   1,   9,    0,    0 },   // 0x00 ' ' 
  {48,     1,   7,  11,   9,    1,  -10 },   // 0x01 '0' 
  {49,    11,   5,  11,   9,    2,  -10 },   // 0x02 '1' 
  {50,    18,   7,  11,   9,    1,  -10 },   // 0x03 '2' 
  {51,    28,   7,  11,   9,    1,  -10 },   // 0x04 '3' 
  {52,    38,   7,  11,   9,    1,  -10 },   // 0x05 '4' 
  {53,    48,   7,  11,   9,    1,  -10 },   // 0x06 '5' 
  {54,    58,   7,  11,   9,    1,  -10 },   // 0x07 '6' 
  {55,    68,   7,  11,   9,    1,  -10 },   // 0x08 '7' 
  {56,    78,   7,  11,   9,    1,  -10 },   // 0x09 '8' 
  {57,    88,   7,  11,   9,    1,  -10 },   // 0x0A '9' 
  {45,    98,   5,   2,   9,    2,   -4 },   // 0x0B '-' 
  {37,   100,   7,  11,   9,    1,  -10 },   // 0x0C '%' 
  {46,   110,   3,   3,   9,    3,   -2 }   // 0x0D '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  14,// total glyphs in the string
  11,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     8,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 224 bytes -  but your mileage may vary.

#endif