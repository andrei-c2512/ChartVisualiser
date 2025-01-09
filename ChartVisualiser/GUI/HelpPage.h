#pragma once
#include "GUICommon.h"
#include "SFML/Graphics.hpp"


struct HelpPage {
	sf::Rect<int> rect;
	sf::Sprite wasdControlsSprite;
	sf::Texture texture;

	sf::Texture mouseLeftTexture;
	sf::Texture mouseRightTexture;

	sf::Sprite mouseLeftSprite;
	sf::Sprite mouseRightSprite;
};


void initHelpPage(HelpPage* page , sf::Rect<int> rect);
void drawHelpPage(sf::RenderWindow&, HelpPage* page);


