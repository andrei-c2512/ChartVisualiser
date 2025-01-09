#pragma once
#ifndef FUNCTIONVIEW_H_INCLUDED
#define FUNCTIONVIEW_H_INCLUDED
#include "StackedView.h"
#include "OptionTab.h"


struct FunctionView{
	sf::Rect<int> rect;

	OptionTab* optionTab;
	StackedView* stackedView;
	int rightMargin;
};

void initFunctionView(FunctionView* view , sf::Rect<int> rect);
void runFunctionView(FunctionView* view, const Mouse& mouse , const Keyboard& kb , Chart& chart);
void setRect(FunctionView* view, sf::Rect<int> rect);
void drawFunctionView(sf::RenderWindow& window, FunctionView* view);
void destroyFunctionView(FunctionView* view);

void updatePalette(FunctionView& view);
#endif // FUNCTIONVIEW_H_INCLUDED
