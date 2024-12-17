#pragma once
#include "GUICommon.h"
#include "SFML/Graphics.hpp"

struct HelpPage {
	sf::Vector2i pos;
	sf::Vector2i size;
	sf::Sprite wasdControlsSprite;
};


void initHelpPage(HelpPage* page , sf::Vector2i pos , sf::Vector2i size);
void drawHelpPage(sf::RenderWindow&, HelpPage* page);


