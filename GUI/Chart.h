#pragma once
#ifndef CHART_H_INCLUDED
#define CHART_H_INCLUDED
#include "GUICommon.h"
#include "graphics.h"


#define ORIGIN_X 0
#define ORIGIN_Y 0
struct Chart{
    int x , y;
    Size s;

    Size unitSizeBase;
    Size unitSizeCurrent;

    int offsetX;
    int offsetY;
    double zoom;
};

void initChart(Chart* chart , int x , int y , Size size0);
void runChart(Chart* chart);
void drawChart(Chart* chart);
void setChartZoom(Chart* chart , float zoom);
void destroyChart(Chart* chart);
#endif // CHART_H_INCLUDED
