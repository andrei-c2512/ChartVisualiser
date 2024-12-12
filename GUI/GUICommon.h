#pragma once
#ifndef GUICOMMON_H_INCLUDED
#define GUICOMMON_H_INCLUDED
#include <iostream>
#include <assert.h>

#define CHART_UNIT_SIZE 40
#define MIN_ZOOM 0.5f
#define MAX_ZOOM 4.0f

struct Size{
    int width;
    int height;
};

struct Margins{
    int left;
    int top;
    int right;
    int bottom;
};

struct Rect{
    int x , y;
    Size s;
};

enum ViewState{
    NONE,
    HOVERED,
    PRESSED,
    SELECTED,
    COUNT
};

enum Options {
    FunctionList,
    Analysis,
    Integral,
    Help,
    Count
};

char* intToString(int nr);
bool intersection(const Rect& rect1 , const Rect& rect2);
Size adjustSizeToMargins(const Size& s , const Margins& margin);
Size horizontalSizeByStretchFactor(const Size& totalSize , int segments , int stretch);

//for logging
void logSize(Size s);
#endif // GUICOMMON_H_INCLUDED
