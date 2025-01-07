#pragma once
#ifndef CHARTBACKGROUNND_H_INCLUDED
#define CHARTBACKGROUNND_H_INCLUDED
#include "GUICommon.h"
#include "SFML/Graphics.hpp"
#include "Palette.h"

//the background will look like a math book
struct ChartBackground{
    sf::Rect<int> rect;

    sf::Vector2<double> rectSizeBase;
    sf::Vector2<double> rectSizeCurrent;

    
    const double* offsetX;
    const double* offsetY;
    double zoom;
};

void initChartBackground(ChartBackground* background ,sf::Rect<int> rect);
void setChartBackgroundRect(ChartBackground* background, sf::Rect<int> rect);
void drawChartBackground(sf::RenderWindow& window, ChartBackground* background);
void setChartBackgroundZoom(ChartBackground* background, double zoom);

#endif // CHARTBACKGROUNND_H_INCLUDED
