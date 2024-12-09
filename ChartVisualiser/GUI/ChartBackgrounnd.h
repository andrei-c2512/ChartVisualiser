#pragma once
#ifndef CHARTBACKGROUNND_H_INCLUDED
#define CHARTBACKGROUNND_H_INCLUDED
#include "GUICommon.h"
#include "SFML/Graphics.hpp"
#include "Palette.h"

//the background will look like a math book
struct ChartBackground{
    int x , y;
    Size s;

    Size rectSizeBase;
    Size rectSizeCurrent;

    int offsetX;
    int offsetY;
    float zoom;
};

void initChartBackground(ChartBackground* background , int x , int y , Size size0);
void drawChartBackground(sf::RenderWindow& window, ChartBackground* background);
void setChartBackgroundZoom(ChartBackground* background, float zoom);

#endif // CHARTBACKGROUNND_H_INCLUDED
