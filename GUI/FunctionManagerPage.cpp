#include "FunctionManagerPage.h"
#include "SFHelper.h"
#include "../RandomFunction.h"
#include "../Validation.h"



void initFunctionBox(FunctionBox* box, sf::Rect<int> rect) {
	box->rect = rect;
	const int marg = 5;
	box->margin = { marg , marg , marg , marg };

	/*Layout
	
		________________________________________________             <- text edit

		space for messages(like invalid input)

		Add from file btn						Delete btn
	*/

	sf::Vector2i btnSize(FunctionBox::buttonSize, FunctionBox::buttonSize);
	const int textEditHeight = 30;

	initTextEdit(&box->textEdit, sf::Vector2i(box->rect.left + box->margin.left, box->rect.top + box->margin.top),
		sf::Vector2i(rect.width - box->margin.left - box->margin.right, textEditHeight));


	initButton(&box->deleteBtn, 
		sf::Rect(sf::Vector2i(box->rect.left + box->rect.width - box->margin.right - FunctionBox::buttonSize,
		box->rect.height + textEditHeight + FunctionBox::buttonVerticalSpacing),btnSize)
		, Palette::deleteButtonPalette());

	setButtonIcon(&box->deleteBtn, "GUI/Resources/deleteIcon32x32.png");
	box->deleteBtn.drawCircle = true;

	initButton(&box->randomFunctionBtn, 
		sf::Rect(sf::Vector2i(box->rect.left + box->margin.left, box->rect.top + textEditHeight + FunctionBox::buttonVerticalSpacing),btnSize),
		Palette::randomButtonPalette());
	setButtonIcon(&box->randomFunctionBtn, "GUI/Resources/diceIcon32x32.png");

	box->randomFunctionBtn.onClick = [box]() {
		box->textEdit.text = getRandomFunction();
		box->textEdit.done = true;
	};

	initButton(&box->detailsBtn, 
		sf::Rect(sf::Vector2i(box->rect.left + box->margin.left * 2 + FunctionBox::buttonSize,
			box->rect.top + textEditHeight + FunctionBox::buttonVerticalSpacing), btnSize), Palette::addButtonPalette());
	setButtonIcon(&box->detailsBtn, "GUI/Resources/detailsIcon48x48.png");

	box->errorMessage.setCharacterSize(16);
	box->errorMessage.setFillColor(Palette::highlightColor());
	box->errorMessage.setFont(Palette::font());
	box->errorMessage.setPosition(SFHelper::toVec2f(topRight(box->detailsBtn.rect)) - sf::Vector2f(0 , 15));
}
void drawFunctionBox(sf::RenderWindow& window, FunctionBox* box) {
	box->textEdit.pos.y = box->rect.top + box->margin.top;
	drawTextEdit(window, &box->textEdit);

	const int verticalSpacing = 15;
	const int adjustedY = box->rect.top + box->textEdit.size.y + verticalSpacing;
	box->deleteBtn.rect.top = box->randomFunctionBtn.rect.top = box->detailsBtn.rect.top = adjustedY;
	
	drawButton(window, &box->deleteBtn);
	drawButton(window, &box->randomFunctionBtn);
	drawButton(window, &box->detailsBtn);
	window.draw(box->errorMessage);
}

int32_t getFunctionBoxHeight(FunctionBox* box) {
	return box->deleteBtn.rect.height + box->textEdit.size.y + FunctionBox::buttonVerticalSpacing;
}

void validateString(FunctionBox& box) {
	std::string str = box.textEdit.text;
	StatusCode result = validate(str);

	std::string message;
	switch (result) {
	case StatusCode::OK:
		break;
	case StatusCode::EMPTY_PARENTHESES:
		message = "Please provide parantheses";
		break;
	case StatusCode::INCORRECT_PARENTHESES:
		message = "Please format the parantheses correctly";
		break;
	case StatusCode::INVALID_BINARY_OPERATION:
		message = "Please use a valid operation";
		break;
	case StatusCode::INVALID_NUMBER:
		message = "Invalid number";
		break;
	case StatusCode::SYNTAX_ERROR:
		message = "Equation not formated correctly";
		break;
	case StatusCode::MISSING_UNARY_PARENTHESIS:
		message = "Missing parantheses";
		break;
	case StatusCode::INVALID_CHARACTER:
		message = "Found out of place character";
		break;
	}
	box.errorMessage.setString(message);

	if (result != StatusCode::OK) {
		box.textEdit.done = false;
	}
}
void runFunctionBox(FunctionBox* box, const Mouse& mouse, const Keyboard& kb) {
	runButton(&box->deleteBtn, mouse);
	runButton(&box->randomFunctionBtn, mouse);
	runButton(&box->detailsBtn, mouse);

	runTextEdit(&box->textEdit, mouse, kb);
	//this function cancels the effect of enter
	validateString(*box);
}

void initFunctionManagerPage(FunctionManagerPage* page, sf::Rect<int> rect) {
	page->rect = rect;
	const int m = 5;
	page->margin = { m , m , m , m };


	page->list.resize(1 , new FunctionBox);
	sf::Text& title = page->title;
	title.setFont(Palette::font());
	title.setCharacterSize(40);
	title.setFillColor(Palette::mainTextColor());
	title.setPosition(SFHelper::toVec2f(rect.getPosition()));
	title.setString("Function manager");

	const sf::Vector2i listPos = rect.getPosition() + sf::Vector2i(0, title.getLocalBounds().height + FunctionManagerPage::titleSpacing);
	initFunctionBox(page->list[0] , sf::Rect(listPos , rect.getSize()));
	FunctionBox* box = page->list[0];
	box->id = 0;
	box->funcColor = Palette::chartColor(0);
	box->textEdit.text = getRandomFunction();
	box->textEdit.text = "(x#(-11))*(sqr(x)*cos(23/x))+(x=(-11))*0";
	box->textEdit.done = true;


	sf::Vector2i s(FunctionManagerPage::buttonSize, FunctionManagerPage::buttonSize);
	initButton(&page->addButton, sf::Rect(rect.getPosition(), s), Palette::addButtonPalette());
	setButtonIcon(&page->addButton, "GUI/Resources/addIcon48x48.png");
	setOnClick(&page->addButton , [page]() {
		FunctionBox* box = new FunctionBox;
		//erasing the element
		initFunctionBox(box, page->rect);
		box->id = page->list.size();
		box->funcColor = Palette::chartColor(box->id);
		box->textEdit.text = getRandomFunction();
		box->textEdit.done = true;
		page->list.emplace_back(box);
	});

	initButton(&page->saveToFileButton,
		sf::Rect(sf::Vector2i(page->rect.left + page->margin.left, page->rect.top ),s),
		Palette::loadFileButtonPalette());
	setButtonIcon(&page->saveToFileButton, "GUI/Resources/pictureIcon32x32.png");
	page->saveToFileButton.drawCircle = true;

}
void destroyFunctionManagerPage(FunctionManagerPage* page) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		delete page->list[i];
	}
}
void runFunctionManagerPage(FunctionManagerPage* page, const Mouse& mouse , const Keyboard& kb) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		bool deletePressed = page->list[i]->deleteBtn.state == ViewState::PRESSED;
		if (deletePressed) {
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
	runButton(&page->saveToFileButton, mouse);
}
void drawFunctionManagerPage(sf::RenderWindow& window, FunctionManagerPage* page) {
	window.draw(page->title);

	int32_t newHeight = page->rect.top+ page->title.getLocalBounds().height + 
		FunctionManagerPage::titleSpacing;
	for (int32_t i = 0; i < page->list.size(); i++) {
		page->list[i]->rect.top = newHeight;
		drawFunctionBox(window , page->list[i]);
		newHeight += getFunctionBoxHeight(page->list[i]);
	}
	page->addButton.rect.top = newHeight + page->rect.top + FunctionManagerPage::functionalitySpacing;
	drawButton(window, &page->addButton);

	page->saveToFileButton.rect.top = page->addButton.rect.top;
	const int btnSpacing = 5;
	page->saveToFileButton.rect.left = page->addButton.rect.left + FunctionManagerPage::buttonSize + btnSpacing;
	drawButton(window, &page->saveToFileButton);
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
		funcStr.funcStr = funcStr.unprocessedFunc = page->list[i]->textEdit.text;
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


int detailsButtonPressed(FunctionManagerPage* page) {
	for (int32_t i = 0; i < page->list.size(); i++) {
		bool detailsPressed = page->list[i]->detailsBtn.state == ViewState::PRESSED;
		if (detailsPressed) {
			page->list[i]->detailsBtn.state = ViewState::NONE;
			return i;
		}
	}
	return -1;
}

bool saveToFilePressed(FunctionManagerPage* page) {
	return page->saveToFileButton.state == ViewState::PRESSED;
}