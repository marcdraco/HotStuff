
#ifndef __FIXEDFONTREPETTTF6
#define __FIXEDFONTREPETTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x3A, 0x18, 0x61, 0x02, 0x18, 0x4E, 0x59, 0x20, 0x97, 0x3A, 0x10, 0x42,
  0x00, 0x42, 0x2F, 0x3A, 0x10, 0x4E, 0x00, 0x18, 0x4E, 0x08, 0x62, 0xA2,
  0x02, 0xF0, 0x82, 0xBE, 0x0B, 0x81, 0x00, 0x18, 0x4E, 0x18, 0x88, 0x2E,
  0x02, 0x18, 0x4E, 0xBC, 0x10, 0x84, 0x00, 0x88, 0x20, 0x3A, 0x18, 0x4E,
  0x02, 0x18, 0x4E, 0x3A, 0x18, 0x4F, 0x00, 0x10, 0x8C, 0x00, 0xBE, 0x08,
  0x2F, 0x02, 0x08, 0x20, 0x3A, 0x18, 0x20, 0x02, 0x08, 0x4E, 0xE0, 0x04,
  0x10, 0x88, 0x01, 0x08, 0x20, 0xA6, 0x90, 0xC4, 0x00, 0x88, 0xE3, 0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   6,   8,   7,    0,   -7 },   // 0x00 '0' 
  {49,     6,   3,   8,   7,    2,   -7 },   // 0x01 '1' 
  {50,     9,   6,   8,   7,    0,   -7 },   // 0x02 '2' 
  {51,    15,   6,   8,   7,    0,   -7 },   // 0x03 '3' 
  {52,    21,   6,   8,   7,    0,   -7 },   // 0x04 '4' 
  {53,    27,   6,   8,   7,    0,   -7 },   // 0x05 '5' 
  {54,    33,   6,   8,   7,    0,   -7 },   // 0x06 '6' 
  {55,    39,   6,   8,   7,    0,   -7 },   // 0x07 '7' 
  {56,    45,   6,   8,   7,    0,   -7 },   // 0x08 '8' 
  {57,    51,   6,   8,   7,    0,   -7 },   // 0x09 '9' 
  {32,    57,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    58,   6,   8,   7,    0,   -7 },   // 0x0B 'F' 
  {67,    64,   6,   8,   7,    0,   -7 },   // 0x0C 'C' 
  {45,    70,   3,   1,   7,    2,   -2 },   // 0x0D '-' 
  {47,    71,   6,   8,   7,    0,   -7 },   // 0x0E '/' 
  {37,    77,   6,   8,   7,    0,   -7 },   // 0x0F '%' 
  {46,    83,   2,   2,   7,    2,   -1 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
     8}; // maximum Y - top most
// Approx. 217 bytes -  but your mileage may vary.

#endif