#include "FunctionManagerPage.h"



void initFunctionBox(FunctionBox* box, sf::Vector2i pos, sf::Vector2i size) {
	box->pos = pos;
	box->size = size;
	const int marg = 5;
	box->margin = { marg , marg , marg , marg };

	const int textEditHeight = 30;
	/*Layout
	
		________________________________________________             <- text edit

		space for messages(like invalid input)

		Add from file btn						Delete btn
	*/

	initTextEdit(&box->textEdit, sf::Vector2i(box->pos.x + box->margin.left, box->pos.y + box->margin.top),
		sf::Vector2i(size.x - box->margin.left - box->margin.right, textEditHeight));

	const int verticalSpacing = 15;
	const int buttonSize = 48;
	initButton(&box->loadFromFileBtn, sf::Vector2i(box->pos.x + box->margin.left, box->pos.y + textEditHeight + verticalSpacing),
		sf::Vector2i(buttonSize, buttonSize) , Palette::loadFileButtonPalette() );
	setButtonIcon(&box->loadFromFileBtn, "");

	initButton(&box->deleteBtn, sf::Vector2i(box->pos.x + box->size.x - box->margin.right - buttonSize,
		box->pos.y + textEditHeight + verticalSpacing), 
		sf::Vector2i(buttonSize , buttonSize) , Palette::deleteButtonPalette());

	setButtonIcon(&box->deleteBtn, "");
}
void drawFunctionBox(sf::RenderWindow& window, FunctionBox* box) {
	drawTextEdit(window, &box->textEdit);

	const int verticalSpacing = 15;
	const int adjustedY = box->pos.y + TextEdit::lineHeight * box->textEdit.lines.size() + verticalSpacing;
	box->deleteBtn.pos.y = adjustedY;
	box->loadFromFileBtn.pos.y = adjustedY;

	drawButton(window, &box->deleteBtn);
	drawButton(window, &box->loadFromFileBtn);
}
void runFunctionBox(FunctionBox* box, const Mouse& mouse, const Keyboard& kb) {
	runButton(&box->loadFromFileBtn, mouse);
	runButton(&box->deleteBtn, mouse);
	runTextEdit(&box->textEdit, mouse, kb);
}

void initFunctionManagerPage(FunctionManagerPage* page, sf::Vector2i pos, sf::Vector2i size) {
	page->pos = pos;
	page->size = size;
	page->list.resize(1);
	initFunctionBox(&page->list[0] , pos , size);
}
void destroyFunctionManagerPage(FunctionManagerPage* page) {

}
void runFunctionManagerPage(FunctionManagerPage* page, const Mouse& mouse , const Keyboard& kb) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		runFunctionBox(&page->list[i], mouse, kb);
	}
}
void drawFunctionManagerPage(sf::RenderWindow& window, FunctionManagerPage* page) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		drawFunctionBox(window , &page->list[i]);
	}
}