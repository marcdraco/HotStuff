
#ifndef __FIXEDFONTPINBALLTTF6
#define __FIXEDFONTPINBALLTTF6
const uint8_t HotStuff6Bitmaps[] PROGMEM = {
  0x00, 0x13, 0xF4, 0xA0, 0x00, 0x04, 0x00, 0x63, 0x03, 0x20, 0x00, 0x12,
  0x23, 0x23, 0x20, 0x00, 0x17, 0x10, 0x80, 0x00, 0x13, 0xF0, 0x80, 0x20,
  0x00, 0x10, 0x10, 0x83, 0x00, 0x00, 0x11, 0xF4, 0xA0, 0x20, 0x00, 0x12,
  0x00, 0x40, 0x00, 0x12, 0xB4, 0xA0, 0x00, 0x00, 0x12, 0xD0, 0x81, 0x00,
  0x00, 0x00, 0x11, 0xE4, 0x63, 0x00, 0x00, 0x51, 0x84, 0x20, 0x00, 0x5C,
  0x00, 0x8C, 0x40, 0x40, 0x00, 0x00, 0x0C, 0x23, 0x00, 0xC0, 0x80 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff6Glyphs[] PROGMEM = {
  {48,     0,   5,   7,   7,    0,   -6 },   // 0x00 '0' 
  {49,     5,   5,   7,   7,    0,   -6 },   // 0x01 '1' 
  {50,    10,   5,   7,   7,    0,   -6 },   // 0x02 '2' 
  {51,    15,   4,   7,   7,    1,   -6 },   // 0x03 '3' 
  {52,    19,   5,   7,   7,    0,   -6 },   // 0x04 '4' 
  {53,    24,   5,   7,   7,    0,   -6 },   // 0x05 '5' 
  {54,    29,   5,   7,   7,    0,   -6 },   // 0x06 '6' 
  {55,    34,   4,   7,   7,    1,   -6 },   // 0x07 '7' 
  {56,    38,   5,   7,   7,    0,   -6 },   // 0x08 '8' 
  {57,    43,   5,   7,   7,    0,   -6 },   // 0x09 '9' 
  {32,    48,   1,   1,   7,    0,    0 },   // 0x0A ' ' 
  {70,    49,   5,   7,   7,    0,   -6 },   // 0x0B 'F' 
  {67,    54,   5,   7,   7,    0,   -6 },   // 0x0C 'C' 
  {45,    59,   4,   2,   7,    1,   -4 },   // 0x0D '-' 
  {47,    60,   5,   6,   7,    0,   -5 },   // 0x0E '/' 
  {37,    64,   6,   7,   7,    0,   -6 },   // 0x0F '%' 
  {46,    70,   1,   1,   7,    2,    0 }   // 0x10 '.' 
};

const gfxfont_t HotStuff6 PROGMEM = 
{
  (uint8_t  *)HotStuff6Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff6Glyphs, //< Glyph array
  17,// total glyphs in the string
   7,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     6,  // maximum X - right most
     7}; // maximum Y - top most
// Approx. 204 bytes -  but your mileage may vary.

#endif