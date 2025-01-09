#pragma once
#include "Button.h"
#include "HorizontalLayout.h"

struct Checkbox {
	sf::Rect<int> rect;
	Widgets::Layout::HorizontalLayout* layout;
	Button button;

	sf::Rect<int> textRect;
	sf::Text text;

	static constexpr int32_t checkboxSize = 48;
};

Checkbox* createCheckbox(sf::Rect<int> rect);
void runCheckbox(Checkbox& checkbox , const Mouse& mouse);
void drawCheckbox(sf::RenderWindow& window, Checkbox& checkbox);
void freeMem(Checkbox* checkbox);