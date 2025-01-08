#pragma once
#include "SFML/Graphics.hpp"
#include "TextEdit.h"
#include "Button.h"


struct IntegralCalculator {
	sf::Texture integralTexture;
	sf::Sprite integralSprite;

	sf::Rect<int> rect;
	
	sf::Text startText;
	TextEdit startEdit;

	sf::Text endText;
	TextEdit endEdit;

	Button calculateBtn;

	sf::Text equationText;
	sf::Text resultText;
};

IntegralCalculator* createIntegralCalculator(sf::Rect<int> rect);
void runIntegralCalculator(IntegralCalculator& calculator, const Mouse& mouse, const Keyboard& kb  , FunctionString& funcStr);
void drawIntegralCalculator(sf::RenderWindow& window, IntegralCalculator& calculator);
void updateResult(IntegralCalculator& calculator, FunctionString& funcStr);