#pragma once
#ifndef LAYOUT_H_INCLUDED
#define LAYOUT_H_INCLUDED
#include "View.h"
#include "TextEdit.h"
#include "FunctionManagerPage.h"
#include "GUICommon.h"


struct StackedView{
    sf::Vector2i pos;
    sf::Vector2i size;

    FunctionManagerPage functionPage;
    Options option;
};

void initStackedView(StackedView* stackedView, sf::Vector2i pos, sf::Vector2i size);
void runStackedView(StackedView* stackedView, const Mouse& mouse, const Keyboard& kb);
void drawStackedView(sf::RenderWindow& window , StackedView* stackedView);
void destroyStackedView(StackedView* view);


#endif // LAYOUT_H_INCLUDED
