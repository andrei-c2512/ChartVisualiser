#pragma once
#ifndef MAINLAYOUT_H_INCLUDED
#define MAINLAYOUT_H_INCLUDED
#include "FunctionView.h"
#include "ChartView.h"
#include "Keyboard.h"
#include "PreviewModeUI.h"
#include <future>


extern "C" {
    #include "../tinyfiledialogs.h"
}

struct MainLayout{
    FunctionView* functionView;
    ChartView* chartView;
    PreviewModeUI* previewModeUI;
    sf::Rect<int> rect;
    Margins margin;

    int functionViewStretch;
    int chartStretch;

    bool previewMode = false;

    const sf::RenderWindow* window;
    bool drawPreviewUI = false;

    bool screenshotQueued = false;
    sf::Clock* clock;
};


MainLayout* initMainLayout(const sf::RenderWindow* window , sf::Rect<int> rect);
//this function will handle the logic , and if needed , will also call the draw function
void setPreviewMode(MainLayout* layout  , bool state);
void saveChartToFile(MainLayout* layout);
void setComponentRatio(MainLayout* layout, int funcViewRatio , int chartViewRatio);
void runMainLayout(MainLayout* layout, const Mouse& mouse, const Keyboard& kb);
void drawMainLayout(sf::RenderWindow& window , MainLayout* layout);
void destroyMainLayout(MainLayout* layout);

#endif // MAINLAYOUT_H_INCLUDED
