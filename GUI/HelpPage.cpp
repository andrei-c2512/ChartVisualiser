#include "HelpPage.h"
#include "SFHelper.h"
#include "Palette.h"

void initHelpPage(HelpPage* page, sf::Rect<int> rect) {
	page->rect = rect;
	if (!page->texture.loadFromFile("GUI/Resources/keyboard320x360.png"))
		std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	//texture.setSmooth(true);

	page->wasdControlsSprite.setPosition(SFHelper::toVec2f(rect.getPosition()));
	page->wasdControlsSprite.setTexture(page->texture);



	auto posList = getAlignedPositionsX(rect, 2, sf::Vector2i(160, 160));

	if (!page->mouseLeftTexture.loadFromFile("GUI/Resources/mouseLeft160x160.png"))
		std::cout << "Failed to load image in help page";

	const int space = 20;
	page->mouseLeftSprite.setPosition(sf::Vector2f(posList[0].x, rect.top + rect.height / 2 + space));
	page->mouseLeftSprite.setTexture(page->mouseLeftTexture);

	if (!page->mouseRightTexture.loadFromFile("GUI/Resources/mouseRight160x160.png"))
		std::cout << "Failed to load image in help page";

	page->mouseRightSprite.setPosition(sf::Vector2f(posList[1].x, rect.top + rect.height / 2 + space));
	page->mouseRightSprite.setTexture(page->mouseRightTexture);
}
void drawHelpPage(sf::RenderWindow& window , HelpPage* page) {
	sf::Vector2f lineDirection0, lineDirection1;

	sf::RectangleShape thickLine;
	thickLine.setFillColor(sf::Color::Black);
	sf::Text text;
	const int characterSize = 30;
	text.setCharacterSize(characterSize);
	text.setFillColor(sf::Color::Black);
	text.setFont(Palette::font());

	window.draw(page->wasdControlsSprite);
	const int lineWidth = 3;
	auto wasdSize = page->texture.getSize();

	sf::Vector2f wLocation = sf::Vector2f(page->rect.left + wasdSize.x / 2,
		page->rect.top + wasdSize.y / 4) + sf::Vector2f(20 , 15);
	//the last vec is just some random offset;

	lineDirection0 =  sf::Vector2f(150, lineWidth);

	//W
	thickLine.setPosition(wLocation);
	thickLine.setSize(lineDirection0);
	
	text.setString("Move up");
	text.setPosition(wLocation + lineDirection0 + sf::Vector2f(10, -characterSize / 2));

	window.draw(thickLine);
	window.draw(text);

	//D
	sf::Vector2f dLocation = sf::Vector2f(page->rect.left + wasdSize.x / 6 * 5, page->rect.top + wasdSize.y / 2) + sf::Vector2f(20 , 0);
	lineDirection0 = sf::Vector2f(100, lineWidth);
	lineDirection1 = sf::Vector2f(-lineWidth , 50 - lineWidth);

	thickLine.setPosition(dLocation);
	thickLine.setSize(lineDirection0);

	window.draw(thickLine);

	thickLine.setPosition(dLocation + lineDirection0);
	thickLine.setSize(lineDirection1);

	window.draw(thickLine);

	text.setString("Move right");
	text.setPosition(dLocation + lineDirection0 + lineDirection1 + sf::Vector2f(-characterSize * 2 , 5));

	window.draw(text);

	//S
	sf::Vector2f sLocation = sf::Vector2f(page->rect.left + wasdSize.x / 2, page->rect.top + wasdSize.y / 2) + sf::Vector2f(20, 20);
	lineDirection0 = sf::Vector2f(lineWidth, 100);
	lineDirection1 = sf::Vector2f(100 - lineWidth, -lineWidth);

	thickLine.setPosition(sLocation);
	thickLine.setSize(lineDirection0);

	window.draw(thickLine);

	thickLine.setPosition(sLocation + lineDirection0);
	thickLine.setSize(lineDirection1);

	window.draw(thickLine);

	text.setPosition(sLocation + lineDirection0 + lineDirection1);
	text.setString("Move down");

	window.draw(text);
	//A
	sf::Vector2f aLocation = sf::Vector2f(page->rect.left + wasdSize.x / 4 - 30, page->rect.top + wasdSize.y / 2 + 30);
	lineDirection0 = sf::Vector2f(lineWidth, 100);

	thickLine.setPosition(aLocation);
	thickLine.setSize(lineDirection0);

	window.draw(thickLine);

	text.setString("Move left");
	text.setPosition(aLocation + lineDirection0 + sf::Vector2f(-characterSize , 0));

	window.draw(text);


	int signCharacterSize = 80;
	sf::Text sign;
	sign.setFont(Palette::font());
	sign.setCharacterSize(signCharacterSize);
	sign.setFillColor(sf::Color::Black);

	sf::Vector2f signPos = page->wasdControlsSprite.getPosition() + sf::Vector2f(40, wasdSize.y);

	const char signList[] = "+-";
	const char messageList[][10] = {"Zoom in" , "Zoom out"};
	int lineLength = 100;
	int convenientOffset = 0;
	for (int8_t i = 0; i < 2; i++) {
		sign.setString(signList[i]);
		sign.setPosition(signPos);

		window.draw(sign);

		lineDirection0 = sign.getPosition() + sf::Vector2f(signCharacterSize - convenientOffset, signCharacterSize / 3 * 2);
		lineDirection1 = sf::Vector2f(lineLength, lineWidth);

		thickLine.setPosition(lineDirection0);
		thickLine.setSize(lineDirection1);

		window.draw(thickLine);

		text.setPosition(lineDirection0 + lineDirection1 + sf::Vector2f(characterSize / 2, -characterSize / 4 * 3));
		text.setString(messageList[i]);

		window.draw(text);

		signPos.y += 50;
		signPos.x += 10;
		convenientOffset = 10;
	}

	window.draw(page->mouseLeftSprite);
	window.draw(page->mouseRightSprite);

	thickLine.setPosition(page->mouseLeftSprite.getPosition() +
		sf::Vector2f(page->mouseLeftTexture.getSize().x / 2 - 40, page->mouseLeftTexture.getSize().y / 2));
	lineDirection1 = sf::Vector2f(lineWidth, 200);
	thickLine.setSize(lineDirection1);

	window.draw(thickLine);

	text.setPosition(thickLine.getPosition() + lineDirection1 - sf::Vector2f(20 , 0));
	text.setString("Click to drag");

	window.draw(text);


	thickLine.setPosition(page->mouseRightSprite.getPosition() + sf::Vector2f(20 , 0) + 
		sf::Vector2f(page->mouseLeftTexture.getSize().x / 2 , page->mouseLeftTexture.getSize().y / 2));
	lineDirection0 = sf::Vector2f(lineWidth, 120);
	

	thickLine.setSize(lineDirection0);
	window.draw(thickLine);
	text.setPosition(thickLine.getPosition() + lineDirection0 - sf::Vector2f(characterSize * 4, 0));
	text.setString("Set breakpoint");

	window.draw(text);
}