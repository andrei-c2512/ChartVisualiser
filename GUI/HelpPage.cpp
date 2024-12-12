#include "HelpPage.h"
#include "SFHelper.h"

void initHelpPage(HelpPage* page, sf::Vector2i pos, sf::Vector2i size) {
	page->pos = pos;
	page->size = size;
	sf::Texture texture;
	if (!texture.loadFromFile("GUI/Resources/controlWASD.png"))
		std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	texture.setSmooth(true);

	page->wasdControlsSprite.setTexture(texture);
}
void drawHelpPage(sf::RenderWindow& window , HelpPage* page) {
	page->wasdControlsSprite.setPosition(SFHelper::toVec2f(page->pos));
	page->wasdControlsSprite.setPosition(0 , 0);
	//window.draw(page->wasdControlsSprite);
}