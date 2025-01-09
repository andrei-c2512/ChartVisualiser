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
    Settings,
    Help,
    Count
};


sf::Rect<int> adjustRectToMargins(const sf::Rect<int>& rect , const Margins& margin);
int horizontalSizeByStretchFactor(int width , int segments , int stretch);
std::vector<sf::Vector2i> getAlignedPositionsX(const sf::Rect<int>& rect, int items , const sf::Vector2i& itemSize);
std::vector<sf::Vector2i> getAlignedPositionsY(const sf::Rect<int>& rect, int items, const sf::Vector2i& itemSize);
std::vector<sf::Vector2i> getDispersedPositionY(const sf::Rect<int>& rect, int items, const sf::Vector2i& itemSize);
sf::Vector2f topRight(const sf::Text& text);

template<typename T>
sf::Vector2<T> bottomLeft(const sf::Vector2<T>& pos, const sf::Vector2<T>& size) noexcept {
    return sf::Vector2<T>(pos.x, pos.y + size.y);
}

template<typename T>
sf::Vector2<T> topRight(const sf::Rect<T> rect) noexcept {
    return sf::Vector2<T>(rect.left + rect.width , rect.top);
}
int32_t getCentered(int32_t x, int32_t width, int32_t itemWidth) noexcept;
double multiplierByZoom(double zoom);

