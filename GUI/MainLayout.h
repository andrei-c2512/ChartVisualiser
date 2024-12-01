#ifndef MAINLAYOUT_H_INCLUDED
#define MAINLAYOUT_H_INCLUDED
#include "FunctionView.h"
#include "ChartView.h"

struct MainLayout{
    FunctionView* functionView;
    ChartView* chartView;

    int x , y;
    Margins margin;
    Size s;

    bool redraw;

    int functionViewStretch;
    int chartStretch;
};


void initMainLayout(MainLayout* layout, Size s);
//this function will handle the logic , and if needed , will also call the draw function
void runMainLayout(MainLayout* layout);
void drawMainLayout(MainLayout* layout);

void destroyMainLayout(MainLayout* layout);

#endif // MAINLAYOUT_H_INCLUDED
