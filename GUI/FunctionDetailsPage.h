#pragma once
#include "GUICommon.h"
#include "FunctionManagerPage.h"


struct FunctionDetailsPage {
	sf::Vector2i pos;
	sf::Vector2i size;
	sf::Text title;
	std::vector<FunctionBox*>* funcList;
	Button goBackButton;
	Button nextButton;
};

void initFunctionDetailsPage(FunctionDetailsPage* page, sf::Vector2i pos, sf::Vector2i size);
void runFunctionDetailsPage(FunctionDetailsPage* page, const Mouse& mouse, const Keyboard& kb);
void drawFunctionDetailsPage(sf::RenderWindow& window, FunctionDetailsPage* page);
