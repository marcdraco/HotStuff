
#ifndef __FIXEDFONTDEJAVUSERIFBOLDTTF7
#define __FIXEDFONTDEJAVUSERIFBOLDTTF7
const uint8_t HotStuff7Bitmaps[] PROGMEM = {
   };

// Glyph, Offset to bitmap, Width, Height, xAdvance, xOffset, yOffset

const gfxglyph_t HotStuff7Glyphs[] PROGMEM = {
};

const gfxfont_t HotStuff7 PROGMEM = 
{
  (uint8_t  *)HotStuff7Bitmaps, //< Glyph bitmaps, concatenated 
  (gfxglyph_t *)HotStuff7Glyphs, //< Glyph array
  0,// total glyphs in the string
   0,  // newline distance (y axis)
     0,  // minimum X - left most
     0,  // minimum Y - bottom most (descenders can drive this negative)
     0,  // maximum X - right most
     0}; // maximum Y - top most
// Approx. 14 bytes -  but your mileage may vary.

#endif