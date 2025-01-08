#pragma once
#include "Button.h"
#include "HorizontalLayout.h"

struct SettingsPage {
	sf::Rect<int> rect;
	Widgets::Layout::HorizontalLayout* btnLayout;
	Button lightModeBtn;
	Button darkModeBtn;
};

SettingsPage* createSettingsPage(sf::Rect<int> rect);
void runSettingsPage(SettingsPage& page, const Mouse& mouse);
