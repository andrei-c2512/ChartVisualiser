#pragma once
#include "Button.h"
#include "HorizontalLayout.h"
#include "Checkbox.h"

struct SettingsPage {
	sf::Rect<int> rect;

	sf::Vector2i titlePos;
	sf::Text title;

	Widgets::Layout::HorizontalLayout* btnLayout;
	sf::Vector2i themeTextPos;
	sf::Text setThemeText;
	Button lightModeBtn;
	Button darkModeBtn;

	std::vector<Checkbox*> languageList;

	static constexpr int32_t themeButtonSize = 48;
};

SettingsPage* createSettingsPage(sf::Rect<int> rect);
void runSettingsPage(SettingsPage& page, const Mouse& mouse);
void drawSettingsPage(sf::RenderWindow& window , SettingsPage& page);
void freeMem(SettingsPage* page);
