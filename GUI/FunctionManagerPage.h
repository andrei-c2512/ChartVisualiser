#pragma once
#include "TextEdit.h"
#include "Button.h"
#include "GUICommon.h"

struct FunctionBox {
	sf::Vector2i pos;
	sf::Vector2i size;
	Margins margin;
	TextEdit textEdit;
	Button loadFromFileBtn;
	Button deleteBtn;
	sf::Text formatMessage;
};

void initFunctionBox(FunctionBox* box, sf::Vector2i pos, sf::Vector2i size);
void drawFunctionBox(sf::RenderWindow& window, FunctionBox* box);
void runFunctionBox(FunctionBox* box, const Mouse& mouse, const Keyboard& kb);

struct FunctionManagerPage {
	sf::Vector2i pos;
	sf::Vector2i size;

	std::vector<FunctionBox> list;
};

void initFunctionManagerPage(FunctionManagerPage* page, sf::Vector2i pos, sf::Vector2i size);
void destroyFunctionManagerPage(FunctionManagerPage* page);
void runFunctionManagerPage(FunctionManagerPage* page, const Mouse& mouse, const Keyboard& kb);
void drawFunctionManagerPage(sf::RenderWindow& window , FunctionManagerPage* page);