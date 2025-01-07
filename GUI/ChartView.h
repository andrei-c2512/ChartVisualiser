#pragma once
#ifndef CHARTVIEW_H_INCLUDED
#define CHARTVIEW_H_INCLUDED

#include "ChartBackgrounnd.h"
#include "Chart.h"
#include "GUICommon.h"
#include <conio.h>
#include "Mouse.h"
#include "Keyboard.h"
#include "Button.h"

struct ChartView{
    Chart* chart;
    ChartBackground* background;
    sf::Rect<int> rect;
    //remembers the area that needs to be shown
    Margins margin;
    sf::Rect<int> viewport;

    int borderWidth;


    bool redraw = true;
    const Mouse* mouse;

    int32_t boundLeft;
    int32_t boundRight;
    int32_t boundTop;
    int32_t boundBottom;

    bool previewMode = false;
    Button goBackButton;
    Button saveButton;
};


bool cameraInBoundsX(ChartView* view, int32_t x);
bool cameraInBoundsY(ChartView* view, int32_t y);

void initChartView(ChartView* view , sf::Rect<int> rect);
void setChartViewRect(ChartView* view, sf::Rect<int> rect);


void runChartView(ChartView* view , const Mouse& mouse , const Keyboard& kb);
void drawChartView(sf::RenderWindow& window, ChartView* view);
void destroyChartView(ChartView* view);
void moveChartX(ChartView* view, int x);
void moveChartY(ChartView* view, int y);

#endif // CHARTVIEW_H_INCLUDED
