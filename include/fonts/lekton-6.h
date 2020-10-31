
#ifndef __FIXEDFONTLEKTONBOLDTTF6
#define __FIXEDFONTLEKTONBOLDTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x31, 0x24, 0x92, 0xCD, 0x24, 0x9E, 0x13, 0xC1, 0x04, 0x10, 0x41, 0x1F,
  0x33, 0x20, 0x82, 0x10, 0x84, 0x1F, 0x31, 0x60, 0x86, 0x38, 0x30, 0xFE,
  0x20, 0x82, 0x12, 0x4B, 0x2F, 0xC2, 0x79, 0x04, 0x1E, 0x48, 0x30, 0xBE,
  0x08, 0xC6, 0x1E, 0xCB, 0x34, 0xDE, 0x7E, 0x42, 0x21, 0x10, 0x84, 0x31,
  0x24, 0x9A, 0x7B, 0x34, 0xDE, 0x66, 0xA3, 0x3F, 0x88, 0xCC, 0x00, 0xF8,
  0x88, 0xF8, 0x88, 0x39, 0x04, 0x30, 0xC1, 0x04, 0x1F, 0xF0, 0x04, 0x30,
  0x86, 0x10, 0x82, 0x10, 0xC2, 0x00, 0xCA, 0xEF, 0x04, 0x20, 0xF7, 0x57,
  0xF0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   6,   8,   6,    0,   -7 },   // 0x00 '0' 
  {49,     6,   6,   8,   6,    0,   -7 },   // 0x01 '1' 
  {50,    12,   6,   8,   6,    0,   -7 },   // 0x02 '2' 
  {51,    18,   6,   8,   6,    0,   -7 },   // 0x03 '3' 
  {52,    24,   6,   8,   6,    0,   -7 },   // 0x04 '4' 
  {53,    30,   6,   8,   6,    0,   -7 },   // 0x05 '5' 
  {54,    36,   6,   8,   6,    0,   -7 },   // 0x06 '6' 
  {55,    42,   5,   8,   6,    0,   -7 },   // 0x07 '7' 
  {56,    47,   6,   8,   6,    0,   -7 },   // 0x08 '8' 
  {57,    53,   5,   8,   6,    1,   -7 },   // 0x09 '9' 
  {32,    58,   1,   1,   6,    0,    0 },   // 0x0A ' ' 
  {70,    59,   4,   8,   6,    1,   -7 },   // 0x0B 'F' 
  {67,    63,   6,   8,   6,    0,   -7 },   // 0x0C 'C' 
  {45,    69,   4,   1,   6,    1,   -3 },   // 0x0D '-' 
  {47,    70,   6,  10,   6,    0,   -8 },   // 0x0E '/' 
  {37,    78,   6,   8,   6,    0,   -7 },   // 0x0F '%' 
  {46,    84,   2,   2,   6,    2,   -1 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   8,  // newline distance (y axis)
     0,  // minimum X - left most
    -1,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
     9}; // maximum Y - top most
// Approx. 218 bytes -  but your mileage may vary.

#endif