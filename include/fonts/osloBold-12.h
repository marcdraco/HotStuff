
#ifndef __FIXEDFONTOSLOIIBOLDTTF12
#define __FIXEDFONTOSLOIIBOLDTTF12
const uint8_t HotStuff12Bitmaps[] PROGMEM = {
  0x00, 0x9E, 0x18, 0x64, 0x0B, 0x01, 0xA0, 0x68, 0x19, 0x06, 0x41, 0x88,
  0x62, 0x18, 0x46, 0x11, 0x82, 0x60, 0x98, 0x16, 0x05, 0x40, 0x98, 0x61,
  0xE4, 0xF8, 0x04, 0x02, 0x01, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
  0x02, 0x01, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x3F, 0xE0, 0x1E,
  0x08, 0x64, 0x0A, 0x01, 0x80, 0x40, 0x10, 0x04, 0x02, 0x01, 0x00, 0x40,
  0x20, 0x10, 0x08, 0x02, 0x01, 0x00, 0x80, 0x40, 0x10, 0x0F, 0xFC, 0x1E,
  0x08, 0x64, 0x0A, 0x01, 0x80, 0x40, 0x10, 0x04, 0x02, 0x01, 0x01, 0x80,
  0x10, 0x02, 0x00, 0x40, 0x18, 0x06, 0x01, 0x40, 0x88, 0x61, 0xE0, 0x01,
  0x00, 0xC0, 0x30, 0x14, 0x05, 0x02, 0x40, 0x90, 0x44, 0x11, 0x08, 0x42,
  0x11, 0x04, 0x41, 0x20, 0x4F, 0xFC, 0x04, 0x01, 0x00, 0x40, 0x10, 0xFF,
  0xE0, 0x08, 0x02, 0x00, 0x9E, 0x38, 0x4C, 0x0A, 0x01, 0x80, 0x60, 0x10,
  0x04, 0x01, 0x00, 0x60, 0x18, 0x06, 0x01, 0x40, 0x88, 0x61, 0xE0, 0x1E,
  0x18, 0x64, 0x0A, 0x01, 0x9E, 0x78, 0x6C, 0x0A, 0x01, 0x80, 0x60, 0x18,
  0x06, 0x01, 0x80, 0x60, 0x18, 0x06, 0x01, 0x40, 0x98, 0x61, 0xE0, 0xFF,
  0xE0, 0x28, 0x0A, 0x04, 0x81, 0x00, 0x80, 0x20, 0x10, 0x04, 0x01, 0x00,
  0x80, 0x20, 0x10, 0x04, 0x02, 0x00, 0x80, 0x40, 0x10, 0x08, 0x00, 0x1E,
  0x18, 0x64, 0x0A, 0x01, 0x80, 0x60, 0x18, 0x05, 0x02, 0x21, 0x07, 0x82,
  0x11, 0x02, 0x80, 0x60, 0x18, 0x06, 0x01, 0x40, 0x98, 0x61, 0xE0, 0x1E,
  0x18, 0x64, 0x0A, 0x01, 0x80, 0x60, 0x18, 0x05, 0x02, 0x61, 0x87, 0xC0,
  0x20, 0x10, 0x04, 0x02, 0x01, 0x00, 0x40, 0x20, 0x10, 0x08, 0x00, 0xFF,
  0xC0, 0x73, 0x16, 0x34, 0x67, 0x41, 0x02, 0x04, 0x10, 0x20, 0x41, 0x02,
  0x04, 0x17, 0x31, 0x63, 0x46, 0x70, 0xC0 };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff12Glyphs[] PROGMEM = {
  {32,     0,   1,   1,   5,    0,    0 },   // 0x00 ' ' 
  {48,     1,  10,  19,  11,    0,  -18 },   // 0x01 '0' 
  {49,    25,   9,  19,  11,    0,  -18 },   // 0x02 '1' 
  {50,    47,  10,  19,  11,    0,  -18 },   // 0x03 '2' 
  {51,    71,  10,  19,  11,    0,  -18 },   // 0x04 '3' 
  {52,    95,  10,  19,  11,    0,  -18 },   // 0x05 '4' 
  {53,   119,  10,  19,  11,    0,  -18 },   // 0x06 '5' 
  {54,   143,  10,  19,  11,    0,  -18 },   // 0x07 '6' 
  {55,   167,  10,  19,  11,    0,  -18 },   // 0x08 '7' 
  {56,   191,  10,  19,  11,    0,  -18 },   // 0x09 '8' 
  {57,   215,  10,  19,  11,    0,  -18 },   // 0x0A '9' 
  {45,   239,  10,   1,  11,    0,   -9 },   // 0x0B '-' 
  {37,   241,   7,  19,   8,    0,  -18 },   // 0x0C '%' 
  {46,   258,   1,   2,   2,    0,   -1 }   // 0x0D '.' 
};

const gfxfont_t HotStuff12 PROGMEM = 
{
  (uint8_t  *)HotStuff12Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff12Glyphs, //< Glyph array
  14,// total glyphs in the string
  19,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
    10,  // maximum X - right most
    19}; // maximum Y - top most
// Approx. 371 bytes -  but your mileage may vary.

#endif