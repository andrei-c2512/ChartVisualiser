#pragma once
#ifndef FUNCTIONVIEW_H_INCLUDED
#define FUNCTIONVIEW_H_INCLUDED
#include "StackedView.h"
#include "OptionTab.h"


struct FunctionView{
	sf::Vector2i pos;
	sf::Vector2i size;

	OptionTab* optionTab;
	StackedView* stackedView;
	int rightMargin;
};

void initFunctionView(FunctionView* view , sf::Vector2i pos , sf::Vector2i size);
void runFunctionView(FunctionView* view, const Mouse& mouse , const Keyboard& kb);
void drawFunctionView(sf::RenderWindow& window, FunctionView* view);
void destroyFunctionView(FunctionView* view);

#endif // FUNCTIONVIEW_H_INCLUDED
