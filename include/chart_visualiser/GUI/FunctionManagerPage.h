#pragma once
#include "TextEdit.h"
#include "Button.h"
#include "GUICommon.h"
#include "../FunctionProcessor.h"

struct FunctionBox {
	sf::Rect<int> rect;
	Margins margin;
	TextEdit textEdit;
	Button deleteBtn;
	Button randomFunctionBtn;
	Button detailsBtn;

	sf::Text formatMessage;
	sf::Color funcColor;
	sf::Text errorMessage;

	int32_t id = 0;
	static constexpr int32_t buttonVerticalSpacing = 30;
	static constexpr int32_t buttonSize = 48;
};

void initFunctionBox(FunctionBox* box, sf::Rect<int> rect);
void drawFunctionBox(sf::RenderWindow& window, FunctionBox* box);
void runFunctionBox(FunctionBox* box, const Mouse& mouse, const Keyboard& kb);
void validateString(FunctionBox& box);
int32_t getFunctionBoxHeight(FunctionBox* box);

struct FunctionList {
	std::vector<FunctionBox> list;
};

struct FunctionManagerPage {
	sf::Text title;

	sf::Rect<int> rect;
	Margins margin;

	std::vector<FunctionBox*> list;

	Button addButton;
	Button saveToFileButton;

	static constexpr int32_t titleSpacing = 30;
	static constexpr int32_t buttonSize = 48;
	static constexpr int32_t functionalitySpacing = 30;
};

void initFunctionManagerPage(FunctionManagerPage* page, sf::Rect<int> rect);
void destroyFunctionManagerPage(FunctionManagerPage* page);
void runFunctionManagerPage(FunctionManagerPage* page, const Mouse& mouse, const Keyboard& kb);
void drawFunctionManagerPage(sf::RenderWindow& window , FunctionManagerPage* page);
bool chartNeedsUpdate(FunctionManagerPage* page);

//returns the index of the specified function
int detailsButtonPressed(FunctionManagerPage* page);
bool saveToFilePressed(FunctionManagerPage* page);
std::vector<FunctionString> getFunctionList(FunctionManagerPage* list);
