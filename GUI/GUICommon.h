#pragma once
#include <iostream>
#include <assert.h>
#include <stack>
#include "../FunctionProcessor.h"
#include "SFML/Graphics.hpp"

#define CHART_UNIT_SIZE 40.0
#define MIN_ZOOM 0.001f
#define MAX_ZOOM 50.0f



struct Margins{
    int left;
    int top;
    int right;
    int bottom;
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


sf::Rect<int> adjustRectToMargins(const sf::Rect<int>& rect , const Margins& margin);
int horizontalSizeByStretchFactor(int width , int segments , int stretch);
std::vector<sf::Vector2i> getAlignedPositions(const sf::Rect<int>& rect, int items , const sf::Vector2i& itemSize);
int32_t getCenteredX(int32_t x, int32_t width, int32_t itemWidth) noexcept;
double multiplierByZoom(double zoom);
