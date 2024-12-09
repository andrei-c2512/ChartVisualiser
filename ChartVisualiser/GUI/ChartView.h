#pragma once
#ifndef CHARTVIEW_H_INCLUDED
#define CHARTVIEW_H_INCLUDED

#include "ChartBackgrounnd.h"
#include "Chart.h"
#include "GUICommon.h"
#include <conio.h>
#include "Mouse.h"

struct ChartView{
    Chart* chart;
    ChartBackground* background;

    //remembers the area that needs to be shown
    Margins margin;
    Rect viewport;

    int x , y;
    int borderWidth;
    Size s;

    bool redraw = true;
    const Mouse* mouse;
};

void initChartView(ChartView* view , int x , int y , Size size0 , const Mouse* mouse);
void runChartView(ChartView* view);
void drawChartView(sf::RenderWindow& window, ChartView* view);
void destroyChartView(ChartView* view);
void moveChartX(ChartView* view, int x);
void moveChartY(ChartView* view, int y);

#endif // CHARTVIEW_H_INCLUDED
