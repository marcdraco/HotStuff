
/*
  Copyright 2020, Marc Draco & Daniel Melvin

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __HOTSTUFF_FIXED
#define __HOTSTUFF_FIXED

glyph_t Fixed::findGlyphCode(const glyph_t &glyph)
{
  // This searches the Flash memory for matching glyph
  // All this pulava is to reduce memory consumption
  // from a bunch of glyphs we'll never use. Bitmaps use 
  // a LOT of space we simply don't have any to waste.

  const FixedGFXfont *gfxFont = m_pFont;
  uint8_t glyphCount  = static_cast<uint8_t>(pgm_read_byte(&gfxFont->glyphCount));
  
  int i {0};
  for (; i != glyphCount; ++i)
  {
    FixedGFXglyph* theGlyph  = pgm_read_glyph_ptr(gfxFont, i);
    if (glyph == pgm_read_byte(&theGlyph->ascii))
    {
      return i;
    }
  }
  return 0;
}

void Fixed::drawGlyph(glyph_t glyph)
{
  screen.startWrite();

  if (bleachThis())
  {
    characters_t lastGlyph;
    lastGlyph = getPrevGlyph();
    glyph_t G = lastGlyph.glyph;
    glyphdata_t prevGlyph;
    drawGlyphPrep(findGlyphCode(G), &prevGlyph);
    prevGlyph.x = lastGlyph.X;
    prevGlyph.y = lastGlyph.Y;
    char b [80];
    sprintf(b,"Bleach: '%c' at: %d", G, prevGlyph.x);
    Serial.println(b);

    for (uint16_t i {0}; i < prevGlyph.dimensions.H; ++i) 
    {
      uint16_t X = prevGlyph.x + prevGlyph.xo;
      uint16_t Y = prevGlyph.y + prevGlyph.yo + i;

      for (uint16_t j {0}; j < prevGlyph.dimensions.W; ++j) 
      {
        if ((prevGlyph.bit & 0x07) == 0 ) 
        {
          prevGlyph.bits = pgm_read_byte(&prevGlyph.bitmap[prevGlyph.offset++]);
        }
        if (prevGlyph.bits & 0x80) 
        {
          screen.writePixel(X, Y, YELLOW);
        }
        ++X;
        ++prevGlyph.bit;
        prevGlyph.bits = prevGlyph.bits << 1;
      }
    }  
  }
  
  registerPosition(glyph);

  glyphdata_t thisGlyph;
  drawGlyphPrep(findGlyphCode(glyph), &thisGlyph);

  for (uint16_t i {0}; i < thisGlyph.dimensions.H; ++i) 
  {
    uint16_t X = thisGlyph.x + thisGlyph.xo;
    uint16_t Y = thisGlyph.y + thisGlyph.yo + i;

    for (uint16_t j {0}; j < thisGlyph.dimensions.W; ++j) 
    {
      if (! (thisGlyph.bit & 0x07)) 
      {
        thisGlyph.bits = pgm_read_byte(&thisGlyph.bitmap[thisGlyph.offset++]);
      }
      
      if (thisGlyph.bits & 0x80) 
      {
        screen.writePixel(X, Y, thisGlyph.colour);
      }

      ++X;
      ++thisGlyph.bit;
      thisGlyph.bits = thisGlyph.bits << 1;
    }
  }
  screen.endWrite();  
  moveTo(m_X + thisGlyph.xMax, m_Y);  
}

void Fixed::drawGlyphPrep(glyph_t g, glyphdata_t* data)
{
  const FixedGFXfont*  font  = m_pFont;
  FixedGFXglyph* glyph = pgm_read_glyph_ptr(font, g);
  
  data->bitmap = pgm_read_bitmap_ptr(font);
  data->offset = pgm_read_word(&glyph->bitmapOffset);
  data->dimensions.H = pgm_read_byte(&glyph->height);
  data->dimensions.W  = pgm_read_byte(&glyph->width);
  data->xo     = pgm_read_byte(&glyph->xOffset);
  data->yo     = pgm_read_byte(&glyph->yOffset);
  data->xMax   = pgm_read_byte(&glyph->xAdvance);
  data->bits   = 0;
  data->bit    = 0;
  data->x      = fixed.getX();
  data->y      = fixed.getY();
  data->glyph  = g;
  data->colour = display.ink;
}

void Fixed::printFixed(char* buffer)
{
  while (*buffer != 0)
  {
    if ( static_cast<char> (*buffer) == '.')
    {
      setFixedFont((FixedGFXfont*) &HOTSMALL);
    }

    glyph_t glyph = static_cast<char>(*buffer++);
    drawGlyph(glyph);
  }
  setFixedFont((FixedGFXfont*) &HOTLARGE);
}  

#endif