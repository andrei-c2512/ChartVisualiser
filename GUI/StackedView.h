#pragma once
#ifndef LAYOUT_H_INCLUDED
#define LAYOUT_H_INCLUDED
#include "TextEdit.h"
#include "FunctionManagerPage.h"
#include "GUICommon.h"
#include "HelpPage.h"
#include "FunctionDetailsPage.h"
#include "Chart.h"
#include "SettingsPage.h"

struct StackedView{
    sf::Rect<int> rect;

    FunctionManagerPage functionPage;
    FunctionDetailsPage functionDetails;
    HelpPage helpPage;
    SettingsPage* settingsPage;

    Options option;
};

void initStackedView(StackedView* stackedView, sf::Rect<int> rect);
void runStackedView(StackedView* stackedView, const Mouse& mouse, const Keyboard& kb, Chart& chart);
void drawStackedView(sf::RenderWindow& window , StackedView* stackedView);
void freeMem(StackedView* page);

#endif // LAYOUT_H_INCLUDED
