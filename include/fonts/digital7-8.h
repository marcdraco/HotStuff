
#ifndef __FIXEDFONTDIGITALMONOTTF8
#define __FIXEDFONTDIGITALMONOTTF8
const uint8_t HotStuff8Bitmaps[] PROGMEM = {
  0x00, 0xFC, 0x63, 0x18, 0xC6, 0x31, 0x8F, 0xC0, 0xFF, 0xC0, 0xF8, 0x42,
  0x1F, 0xC2, 0x10, 0x87, 0x80, 0xFC, 0x10, 0x41, 0x7C, 0x10, 0x41, 0x07,
  0xF0, 0x0C, 0x63, 0x1F, 0x84, 0x21, 0x08, 0x40, 0xF4, 0x21, 0x0F, 0x84,
  0x21, 0x0F, 0xC0, 0xF4, 0x21, 0x0F, 0xC6, 0x31, 0x8F, 0xC0, 0xFC, 0x63,
  0x18, 0x84, 0x21, 0x08, 0x40, 0xFC, 0x63, 0x1F, 0xC6, 0x31, 0x8F, 0xC0,
  0xFC, 0x63, 0x1F, 0x84, 0x21, 0x0F, 0xC0, 0xF8, 0xE7, 0x4B, 0xB0, 0x40,
  0x84, 0x08, 0x37, 0x4B, 0x9C, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff8Glyphs[] PROGMEM = {
  {32,     0,   1,   1,   7,    0,    0 },   // 0x00 ' ' 
  {48,     1,   5,  10,   7,    1,   -9 },   // 0x01 '0' 
  {49,     8,   1,  10,   7,    5,   -9 },   // 0x02 '1' 
  {50,    10,   5,  10,   7,    1,   -9 },   // 0x03 '2' 
  {51,    17,   6,  10,   7,    0,   -9 },   // 0x04 '3' 
  {52,    25,   5,  10,   7,    1,   -9 },   // 0x05 '4' 
  {53,    32,   5,  10,   7,    1,   -9 },   // 0x06 '5' 
  {54,    39,   5,  10,   7,    1,   -9 },   // 0x07 '6' 
  {55,    46,   5,  10,   7,    1,   -9 },   // 0x08 '7' 
  {56,    53,   5,  10,   7,    1,   -9 },   // 0x09 '8' 
  {57,    60,   5,  10,   7,    1,   -9 },   // 0x0A '9' 
  {45,    67,   5,   1,   7,    1,   -5 },   // 0x0B '-' 
  {37,    68,   7,  10,   7,    0,   -9 },   // 0x0C '%' 
  {46,    77,   1,   1,   7,    3,    0 }   // 0x0D '.' 
};

const gfxfont_t HotStuff8 PROGMEM = 
{
  (uint8_t  *)HotStuff8Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff8Glyphs, //< Glyph array
  14,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
    10}; // maximum Y - top most
// Approx. 190 bytes -  but your mileage may vary.

#endif