
#ifndef __FIXEDFONTMONOIDAAAALADAATTF6
#define __FIXEDFONTMONOIDAAAALADAATTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x4B, 0x99, 0x9D, 0x99, 0x9E, 0xC4, 0x44, 0x44, 0x44, 0xF0, 0x41, 0x11,
  0x22, 0x44, 0x8F, 0x12, 0x26, 0x11, 0x11, 0xF0, 0x94, 0xA5, 0x29, 0x48,
  0x42, 0x10, 0x88, 0x8F, 0x11, 0x11, 0xF0, 0x28, 0x88, 0xF9, 0x99, 0x9F,
  0x11, 0x02, 0x20, 0x44, 0x00, 0x02, 0x52, 0x94, 0xB9, 0x31, 0x4B, 0x80,
  0x22, 0x43, 0x10, 0xA4, 0xA1, 0x0B, 0x80, 0x00, 0x84, 0x21, 0x0F, 0x42,
  0x10, 0x80, 0x11, 0x18, 0x20, 0x82, 0x08, 0x20, 0x81, 0xF0, 0xF0, 0x04,
  0x20, 0x84, 0x10, 0x82, 0x10, 0x42, 0x08, 0x00, 0x42, 0x88, 0x3B, 0x18,
  0x84, 0xA9, 0x24, 0x70, 0x50 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   4,  10,   7,    2,   -9 },   // 0x00 '0' 
  {49,     5,   4,   9,   7,    2,   -8 },   // 0x01 '1' 
  {50,    10,   4,  10,   7,    2,   -9 },   // 0x02 '2' 
  {51,    15,   4,   9,   7,    2,   -8 },   // 0x03 '3' 
  {52,    20,   5,   9,   7,    2,   -8 },   // 0x04 '4' 
  {53,    26,   4,   9,   7,    2,   -8 },   // 0x05 '5' 
  {54,    31,   4,  10,   7,    2,   -9 },   // 0x06 '6' 
  {55,    36,   4,   9,   7,    2,   -8 },   // 0x07 '7' 
  {56,    41,   5,  10,   7,    1,   -9 },   // 0x08 '8' 
  {57,    48,   5,  10,   7,    1,   -9 },   // 0x09 '9' 
  {32,    55,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    56,   5,   9,   7,    2,   -8 },   // 0x0B 'F' 
  {67,    62,   6,  10,   7,    1,   -9 },   // 0x0C 'C' 
  {45,    70,   4,   1,   7,    2,   -4 },   // 0x0D '-' 
  {47,    71,   6,  11,   7,    1,   -9 },   // 0x0E '/' 
  {37,    80,   6,  10,   7,    1,   -9 },   // 0x0F '%' 
  {46,    88,   2,   2,   7,    2,   -1 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
    10}; // maximum Y - top most
// Approx. 222 bytes -  but your mileage may vary.

#endif