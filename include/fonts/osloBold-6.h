
#ifndef __FIXEDFONTOSLOIIBOLDTTF6
#define __FIXEDFONTOSLOIIBOLDTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0xF4, 0x63, 0x9C, 0xD6, 0xB3, 0x8B, 0xC0, 0xE1, 0x08, 0x42, 0x10, 0x84,
  0x27, 0xC0, 0x32, 0x62, 0x11, 0x10, 0x88, 0x87, 0xC0, 0x32, 0x62, 0x10,
  0x98, 0x31, 0x49, 0x80, 0x11, 0x94, 0xA9, 0x4A, 0x5F, 0x10, 0x80, 0xFC,
  0x3D, 0xB8, 0x84, 0x31, 0x59, 0x80, 0x74, 0x7F, 0xB8, 0xC6, 0x31, 0xDB,
  0x80, 0xFC, 0x64, 0x22, 0x10, 0x88, 0x44, 0x00, 0x74, 0x63, 0x18, 0xBB,
  0x31, 0x8B, 0x80, 0x74, 0x63, 0x18, 0xB8, 0x84, 0x44, 0x00, 0x00, 0xFC,
  0x21, 0x08, 0x7E, 0x10, 0x84, 0x00, 0x76, 0xE3, 0x18, 0x42, 0x31, 0x9B,
  0x80, 0xF8, 0xFF, 0x80, 0xFA, 0xE4, 0x44, 0x87, 0xDF, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,  10,   6,    0,   -9 },   // 0x00 '0' 
  {49,     7,   5,  10,   5,    0,   -9 },   // 0x01 '1' 
  {50,    14,   5,  10,   6,    0,   -9 },   // 0x02 '2' 
  {51,    21,   5,  10,   6,    0,   -9 },   // 0x03 '3' 
  {52,    28,   5,  10,   5,    0,   -9 },   // 0x04 '4' 
  {53,    35,   5,  10,   6,    0,   -9 },   // 0x05 '5' 
  {54,    42,   5,  10,   6,    0,   -9 },   // 0x06 '6' 
  {55,    49,   5,  10,   5,    0,   -9 },   // 0x07 '7' 
  {56,    56,   5,  10,   6,    0,   -9 },   // 0x08 '8' 
  {57,    63,   5,  10,   6,    0,   -9 },   // 0x09 '9' 
  {32,    70,   1,   1,   3,    0,    0 },   // 0x0A ' ' 
  {70,    71,   5,  10,   5,    0,   -9 },   // 0x0B 'F' 
  {67,    78,   5,  10,   6,    0,   -9 },   // 0x0C 'C' 
  {45,    85,   5,   1,   5,    0,   -4 },   // 0x0D '-' 
  {47,    86,   1,   9,   2,    0,   -8 },   // 0x0E '/' 
  {37,    88,   4,  10,   5,    0,   -9 },   // 0x0F '%' 
  {46,    93,   1,   1,   1,    0,    0 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     5,  // maximum X - right most
    10}; // maximum Y - top most
// Approx. 227 bytes -  but your mileage may vary.

#endif