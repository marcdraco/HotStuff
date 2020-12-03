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

#ifndef __DRACO_HOTSTUFF_GRAPH_H
#define __DRACO_HOTSTUFF_GRAPH_H

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <Wire.h>

#include <Adafruit_GFX.h>     // Core graphics library by AdaFruit
#include <MCUFRIEND_kbv.h>    // David Prentice's Hardware-specific library - your shield might vary
#include "UniversalDHT.h"     // @winlinvip's DHT11/22 library functions modified by Tim Harper

#include "Alarm.h"
#include "Display.h"
#include "Environmental.h"
#include "Fonts.h"
#include "Flags.h"
#include "Graph.h"
#include "hotstuff_fonts.h"
#include "hotstuff.h"
#include "Messages.h"
#include "Reading.h"
#include "Sevensegments.h"
#include "Trig.h"
#include "types.h"

class Graph
{
  private:
    
    uint8_t m_xStep         {27}; // X - reticle
    uint8_t m_yStep         {20}; // Y reticle
    uint8_t m_circular       {0};
    int16_t m_temperature[GRAPH_WIDTH];
    int16_t m_humidity[GRAPH_WIDTH];

  public:

  Graph() 
  {
    for (uint8_t i {0}; i < GRAPH_WIDTH; ++i)
    {
      m_temperature[i] = 0;
      m_humidity[i]    = 0;
    }
  };

  void drawPointers();

  void draw(const triangle_t* polygon, const colours_t ink, const colours_t outline);
  void draw(const quadrilateral_t* polygon, const colours_t ink, const colours_t outline);

  void translate(triangle_t* polygon, const coordinates_t cords);
  void translate(quadrilateral_t* polygon, const coordinates_t cords);
    
  void rotate(triangle_t* polygon, const angle_t theta);
  void rotate(quadrilateral_t* polygon, const angle_t theta);

  void drawIBar(const ucoordinate_t x, const reading_t reading, int16_t minimum, int16_t maximum, const int8_t scale, const colours_t ink, const bool pointer);
  void drawMinMax(const ucoordinate_t x, const reading_t reading, const int16_t min, const int16_t max, const int8_t scale, const colours_t ink);
  void drawDiamond(const ucoordinate_t x, const reading_t reading, const uint16_t scale, const uint8_t size, const colours_t ink);
  void drawTarget(const ucoordinate_t x, const reading_t reading, const uint16_t scale, const uint8_t size, const colours_t ink);

  /**
   * @brief Displays the main graph
   * 
   * convert the temperature and humidity.reading readings into something that scales to the chart.
   * the FSD is 100 points giving a temp range of 0 - 50c (32 - 122f)
   * The flag determines which "phase" we're in (clear readings or set new ones)
   */

  void drawGraph();

  /**
   * @brief  Overdraws the graph outline in the current foreground
   * 
   */  
  void drawMainAxes();
  void drawGraphScaleMarks();

  /**
   * @brief Draw the graph lines and chart calibration markings
   * 
   */  
  void drawReticles(const uint8_t xDivs, const uint8_t yDivs);
  
  /**
   * @brief draws circular plots for the analogue version
   * 
   */
  void drawRadials();

  void postReadings();

  int getGraphX()
  {
    return ((TFT_WIDTH - GRAPH_WIDTH) >> 1);
  }

};

extern Graph graph;

#endif