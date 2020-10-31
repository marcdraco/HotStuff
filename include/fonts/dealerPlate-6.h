
#ifndef __FIXEDFONTDEALERPLATECALIFORNIATTF6
#define __FIXEDFONTDEALERPLATECALIFORNIATTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x65, 0x99, 0x99, 0x99, 0x56, 0x26, 0x22, 0x22, 0x22, 0x2F, 0x75, 0x11,
  0x22, 0x44, 0x8F, 0xC4, 0x96, 0x49, 0xBC, 0x24, 0x44, 0x44, 0x59, 0xF1,
  0xF8, 0x88, 0xF9, 0x11, 0x17, 0x12, 0x44, 0x47, 0x99, 0x56, 0xF1, 0x12,
  0x22, 0x22, 0x44, 0x65, 0x99, 0x75, 0x99, 0x97, 0x65, 0x95, 0x71, 0x12,
  0x24, 0x00, 0xF8, 0x88, 0xE8, 0x88, 0x88, 0x65, 0x98, 0x88, 0x89, 0x56,
  0xC0, 0x55, 0x56, 0xA8, 0xDD, 0xDE, 0x22, 0x57, 0x79, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   4,  10,   5,    0,   -9 },   // 0x00 '0' 
  {49,     5,   4,  10,   5,    0,   -9 },   // 0x01 '1' 
  {50,    10,   4,  10,   5,    0,   -9 },   // 0x02 '2' 
  {51,    15,   3,  10,   5,    1,   -9 },   // 0x03 '3' 
  {52,    19,   4,  10,   5,    0,   -9 },   // 0x04 '4' 
  {53,    24,   4,  10,   5,    0,   -9 },   // 0x05 '5' 
  {54,    29,   4,  10,   5,    0,   -9 },   // 0x06 '6' 
  {55,    34,   4,  10,   5,    0,   -9 },   // 0x07 '7' 
  {56,    39,   4,  10,   5,    0,   -9 },   // 0x08 '8' 
  {57,    44,   4,  10,   5,    0,   -9 },   // 0x09 '9' 
  {32,    49,   1,   1,   2,    0,    0 },   // 0x0A ' ' 
  {70,    50,   4,  10,   5,    0,   -9 },   // 0x0B 'F' 
  {67,    55,   4,  10,   5,    0,   -9 },   // 0x0C 'C' 
  {45,    60,   2,   1,   2,    0,   -5 },   // 0x0D '-' 
  {47,    61,   2,  11,   2,    0,  -10 },   // 0x0E '/' 
  {37,    64,   4,  10,   5,    0,   -9 },   // 0x0F '%' 
  {46,    69,   1,   1,   2,    1,    0 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     4,  // maximum X - right most
    11}; // maximum Y - top most
// Approx. 203 bytes -  but your mileage may vary.

#endif