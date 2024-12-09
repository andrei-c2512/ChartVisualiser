#pragma once
#include "Button.h"

struct OptionTab {
	sf::Vector2i pos;
	sf::Vector2i size;

	sf::Color backgroundColor;
	sf::Color separationMarginColor;
	std::vector<Button*> optionList;

	int32_t lastSelected = 0;
};

void initOptionTab(OptionTab* tab , sf::Vector2i pos , sf::Vector2i size);
void runOptionTab(OptionTab* tab , const Mouse& mouse);
void drawOptionTab(sf::RenderWindow& window, OptionTab* tab);
void destroyOptionTab(OptionTab* tab);