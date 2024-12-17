#include "FunctionManagerPage.h"
#include "SFHelper.h"
#include "../RandomFunction.h"



void initFunctionBox(FunctionBox* box, sf::Vector2i pos, sf::Vector2i size) {
	box->pos = pos;
	box->size = size;
	const int marg = 5;
	box->margin = { marg , marg , marg , marg };

	/*Layout
	
		________________________________________________             <- text edit

		space for messages(like invalid input)

		Add from file btn						Delete btn
	*/

	sf::Vector2i btnSize(FunctionBox::buttonSize, FunctionBox::buttonSize);
	const int textEditHeight = 30;

	initTextEdit(&box->textEdit, sf::Vector2i(box->pos.x + box->margin.left, box->pos.y + box->margin.top),
		sf::Vector2i(size.x - box->margin.left - box->margin.right, textEditHeight));


	initButton(&box->deleteBtn, sf::Vector2i(box->pos.x + box->size.x - box->margin.right - FunctionBox::buttonSize,
		box->pos.y + textEditHeight + FunctionBox::buttonVerticalSpacing),
		btnSize, Palette::deleteButtonPalette());

	setButtonIcon(&box->deleteBtn, "GUI/Resources/deleteIcon32x32.png");
	box->deleteBtn.drawCircle = true;

	initButton(&box->randomFunctionBtn, 
		sf::Vector2i(box->pos.x + box->margin.left, box->pos.y + textEditHeight + FunctionBox::buttonVerticalSpacing),
		btnSize, Palette::randomButtonPalette());
	setButtonIcon(&box->randomFunctionBtn, "GUI/Resources/diceIcon48x48.png");

	box->randomFunctionBtn.onClick = [box]() {
		box->textEdit.text = getRandomFunction();
		box->textEdit.done = true;
	};

}
void drawFunctionBox(sf::RenderWindow& window, FunctionBox* box) {
	box->textEdit.pos.y = box->pos.y + box->margin.top;
	drawTextEdit(window, &box->textEdit);

	const int verticalSpacing = 15;
	const int adjustedY = box->pos.y + box->textEdit.size.y + verticalSpacing;
	box->deleteBtn.pos.y = box->randomFunctionBtn.pos.y = adjustedY;

	drawButton(window, &box->deleteBtn);
	drawButton(window, &box->randomFunctionBtn);
}

int32_t getFunctionBoxHeight(FunctionBox* box) {
	return box->deleteBtn.size.y + box->textEdit.size.y + FunctionBox::buttonVerticalSpacing;
}

void runFunctionBox(FunctionBox* box, const Mouse& mouse, const Keyboard& kb) {
	runButton(&box->deleteBtn, mouse);
	runButton(&box->randomFunctionBtn, mouse);

	runTextEdit(&box->textEdit, mouse, kb);
}

void initFunctionManagerPage(FunctionManagerPage* page, sf::Vector2i pos, sf::Vector2i size) {
	page->pos = pos;
	page->size = size;
	const int m = 5;
	page->margin = { m , m , m , m };


	page->list.resize(1 , new FunctionBox);
	sf::Text& title = page->title;
	title.setFont(Palette::font());
	title.setCharacterSize(40);
	title.setFillColor(Palette::mainTextColor());
	title.setPosition(SFHelper::toVec2f(pos));
	title.setString("Function manager");

	const sf::Vector2i listPos = pos + sf::Vector2i(0, title.getLocalBounds().height + FunctionManagerPage::titleSpacing);
	initFunctionBox(page->list[0] ,listPos , size);
	FunctionBox* box = page->list[0];
	box->funcColor = Palette::chartColor(0);


	sf::Vector2i s(FunctionManagerPage::buttonSize, FunctionManagerPage::buttonSize);
	initButton(&page->addButton, pos, s , Palette::addButtonPalette());
	setButtonIcon(&page->addButton, "GUI/Resources/addIcon48x48.png");
	setOnClick(&page->addButton , [page]() {
		FunctionBox* box = new FunctionBox;
		box->id = page->list.size();
		box->funcColor = Palette::chartColor(box->id);
		//erasing the element
		initFunctionBox(box, page->pos, page->size);
		page->list.emplace_back(box);
	});

	initButton(&page->loadFromFileBtn, sf::Vector2i(page->pos.x + page->margin.left, page->pos.y ),
		s, Palette::loadFileButtonPalette());
	setButtonIcon(&page->loadFromFileBtn, "GUI/Resources/loadIcon32x32.png");
	page->loadFromFileBtn.drawCircle = true;
}
void destroyFunctionManagerPage(FunctionManagerPage* page) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		delete page->list[i];
	}
}
void runFunctionManagerPage(FunctionManagerPage* page, const Mouse& mouse , const Keyboard& kb) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		bool pressed = page->list[i]->deleteBtn.state == ViewState::PRESSED;
		if (pressed) {
			page->list.erase(page->list.begin() + page->list[i]->id);
			//updating the indexes cuz otherwise it might crash/delete the wrong buttons
			for (int32_t i = 0; i < page->list.size(); i++) {
				page->list[i]->id = i;
			}
		}
	}
	for (int32_t i = 0; i < page->list.size(); i++) {
		runFunctionBox(page->list[i], mouse, kb);
	}
	runButton(&page->addButton , mouse);
	runButton(&page->loadFromFileBtn, mouse);
}
void drawFunctionManagerPage(sf::RenderWindow& window, FunctionManagerPage* page) {
	window.draw(page->title);

	int32_t newHeight = page->pos.y + page->title.getLocalBounds().height + 
		FunctionManagerPage::titleSpacing;
	for (int32_t i = 0; i < page->list.size(); i++) {
		page->list[i]->pos.y = newHeight;
		drawFunctionBox(window , page->list[i]);
		newHeight += getFunctionBoxHeight(page->list[i]);
	}
	page->addButton.pos.y = newHeight + page->pos.y + FunctionManagerPage::functionalitySpacing;
	drawButton(window, &page->addButton);

	page->loadFromFileBtn.pos.y = page->addButton.pos.y;
	const int btnSpacing = 5;
	page->loadFromFileBtn.pos.x = page->addButton.pos.x + FunctionManagerPage::buttonSize + btnSpacing;
	drawButton(window, &page->loadFromFileBtn);
}

bool chartNeedsUpdate(FunctionManagerPage* page) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		bool& result = page->list[i]->textEdit.done;
		//reset and return true
		if (result) {
			return true;
		}
	}
	return false;
}

std::vector<FunctionString> getFunctionList(FunctionManagerPage* page) {
	std::vector<FunctionString> vec;
	vec.reserve(page->list.size());

	for (int32_t i = 0; i < page->list.size(); i++) {
		FunctionString funcStr;
		funcStr.funcStr = page->list[i]->textEdit.text;
		initFunc(funcStr.funcStr);
		if (page->list[i]->textEdit.done) {
			funcStr.needsUpdate = true;
			funcStr.color = page->list[i]->funcColor;
			page->list[i]->textEdit.done = false;
		}

		vec.emplace_back(funcStr);
	}

	return vec;
}

