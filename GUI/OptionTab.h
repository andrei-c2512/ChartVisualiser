#pragma once
#include "Button.h"

struct OptionTab {
	sf::Rect<int> rect;

	sf::Color backgroundColor;
	sf::Color separationMarginColor;
	std::vector<Button*> optionList;

	int32_t lastSelected = 0;

	Options currentOption = Options::FunctionList;
};

void initOptionTab(OptionTab* tab , sf::Rect<int> rect);
void runOptionTab(OptionTab* tab , const Mouse& mouse);
void drawOptionTab(sf::RenderWindow& window, OptionTab* tab);
void destroyOptionTab(OptionTab* tab);