
#ifndef __FIXEDFONTNINEPINTTF6
#define __FIXEDFONTNINEPINTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x34, 0x02, 0x0C, 0x30, 0x12, 0x68, 0xC1, 0x00, 0x68, 0x20, 0x28, 0x40,
  0x10, 0x84, 0x05, 0x40, 0x34, 0x02, 0x0C, 0x10, 0x00, 0x84, 0x10, 0x01,
  0x6C, 0x34, 0x02, 0x08, 0x10, 0x06, 0x80, 0xC1, 0x00, 0x68, 0x82, 0x02,
  0x0C, 0x10, 0x16, 0xC0, 0x81, 0x00, 0x04, 0xB6, 0x02, 0x04, 0x00, 0x16,
  0x80, 0x81, 0x01, 0x68, 0x34, 0x02, 0x0C, 0x00, 0x16, 0xA0, 0xC1, 0x00,
  0x68, 0xB6, 0x00, 0x08, 0x10, 0x00, 0x81, 0x08, 0x00, 0x20, 0x34, 0x02,
  0x0C, 0x10, 0x06, 0xA0, 0xC1, 0x00, 0x68, 0x34, 0x02, 0x0C, 0x10, 0x06,
  0xC0, 0xC1, 0x00, 0x68, 0x00, 0xB6, 0x02, 0x04, 0x00, 0x16, 0xA0, 0x40,
  0x01, 0x00, 0x34, 0x02, 0x0C, 0x00, 0x10, 0x20, 0x41, 0x00, 0x68, 0xB4,
  0x02, 0x00, 0x08, 0x20, 0x02, 0x08, 0x40, 0x01, 0x00, 0x02, 0x02, 0x8D,
  0x20, 0x02, 0x09, 0xC3, 0x01, 0x00, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const fixedgfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   7,  10,   8,    0,   -9 },   // 0x00 '0' 
  {49,     9,   5,  10,   8,    1,   -9 },   // 0x01 '1' 
  {50,    16,   7,  10,   8,    0,   -9 },   // 0x02 '2' 
  {51,    25,   7,  10,   8,    0,   -9 },   // 0x03 '3' 
  {52,    34,   7,  10,   8,    0,   -9 },   // 0x04 '4' 
  {53,    43,   7,  10,   8,    0,   -9 },   // 0x05 '5' 
  {54,    52,   7,  10,   8,    0,   -9 },   // 0x06 '6' 
  {55,    61,   7,  10,   8,    0,   -9 },   // 0x07 '7' 
  {56,    70,   7,  10,   8,    0,   -9 },   // 0x08 '8' 
  {57,    79,   7,  10,   8,    0,   -9 },   // 0x09 '9' 
  {32,    88,   1,   1,   8,    0,    0 },   // 0x0A ' ' 
  {70,    89,   7,  10,   8,    0,   -9 },   // 0x0B 'F' 
  {67,    98,   7,  10,   8,    0,   -9 },   // 0x0C 'C' 
  {45,   107,   6,   1,   8,    0,   -4 },   // 0x0D '-' 
  {47,   108,   7,  10,   8,    0,   -9 },   // 0x0E '/' 
  {37,   117,   7,  10,   8,    0,   -9 },   // 0x0F '%' 
  {46,   126,   1,   1,   7,    3,    0 }   // 0x10 '.' 
};

const fixedgfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (fixedgfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
  10,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     7,  // maximum X - right most
    10}; // maximum Y - top most
// Approx. 260 bytes -  but your mileage may vary.

#endif