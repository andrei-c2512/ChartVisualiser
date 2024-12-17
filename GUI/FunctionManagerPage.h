#pragma once
#include "TextEdit.h"
#include "Button.h"
#include "GUICommon.h"
#include "../FunctionProcessor.h"

struct FunctionBox {
	sf::Vector2i pos;
	sf::Vector2i size;
	Margins margin;
	TextEdit textEdit;
	Button deleteBtn;
	Button randomFunctionBtn;
	sf::Text formatMessage;
	sf::Color funcColor;

	int32_t id = 0;
	static constexpr int32_t buttonVerticalSpacing = 15;
	static constexpr int32_t buttonSize = 48;
};

void initFunctionBox(FunctionBox* box, sf::Vector2i pos, sf::Vector2i size);
void drawFunctionBox(sf::RenderWindow& window, FunctionBox* box);
void runFunctionBox(FunctionBox* box, const Mouse& mouse, const Keyboard& kb);
int32_t getFunctionBoxHeight(FunctionBox* box);

struct FunctionList {
	std::vector<FunctionBox> list;
};

struct FunctionManagerPage {
	sf::Text title;

	sf::Vector2i pos;
	sf::Vector2i size;
	Margins margin;

	std::vector<FunctionBox*> list;

	Button addButton;
	Button loadFromFileBtn;

	static constexpr int32_t titleSpacing = 30;
	static constexpr int32_t buttonSize = 48;
	static constexpr int32_t functionalitySpacing = 30;
};

void initFunctionManagerPage(FunctionManagerPage* page, sf::Vector2i pos, sf::Vector2i size);
void destroyFunctionManagerPage(FunctionManagerPage* page);
void runFunctionManagerPage(FunctionManagerPage* page, const Mouse& mouse, const Keyboard& kb);
void drawFunctionManagerPage(sf::RenderWindow& window , FunctionManagerPage* page);
bool chartNeedsUpdate(FunctionManagerPage* page);
std::vector<FunctionString> getFunctionList(FunctionManagerPage* list);