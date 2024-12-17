#pragma once
#ifndef GUICOMMON_H_INCLUDED
#define GUICOMMON_H_INCLUDED
#include <iostream>
#include <assert.h>
#include <stack>
#include "../FunctionProcessor.h"
#include "SFML/Graphics.hpp"

#define CHART_UNIT_SIZE 40.0f
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


struct FunctionString {
    std::string funcStr = "";
    int32_t index = 0;
    sf::Color color;
    std::stack<char> operators;
    std::stack<float> operands;
    std::vector<CalculationStep> steps;
    bool needsUpdate = false;
};

char* intToString(int nr);
bool intersection(const Rect& rect1 , const Rect& rect2);
Size adjustSizeToMargins(const Size& s , const Margins& margin);
Size horizontalSizeByStretchFactor(const Size& totalSize , int segments , int stretch);

//for logging
void logSize(Size s);
#endif // GUICOMMON_H_INCLUDED
