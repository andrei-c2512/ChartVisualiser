#pragma once
#ifndef MAINLAYOUT_H_INCLUDED
#define MAINLAYOUT_H_INCLUDED
#include "FunctionView.h"
#include "ChartView.h"
#include "SFML/System/Vector2.hpp"
#include "Keyboard.h"

struct MainLayout{
    FunctionView* functionView;
    ChartView* chartView;
    sf::Font font;
    int x , y;
    Margins margin;
    Size s;

    bool redraw;

    int functionViewStretch;
    int chartStretch;

    const Mouse* mouse;
};


void initMainLayout(MainLayout* layout, Size s , const Mouse* mouse);
//this function will handle the logic , and if needed , will also call the draw function
void runMainLayout(MainLayout* layout, const Mouse& mouse, const Keyboard& kb);
void drawMainLayout(sf::RenderWindow& window , MainLayout* layout);
void destroyMainLayout(MainLayout* layout);

#endif // MAINLAYOUT_H_INCLUDED
