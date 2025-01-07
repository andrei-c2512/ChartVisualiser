#include "FunctionDetailsPage.h"
#include "SFHelper.h"
#include "../Tools.h"
#include "../FunctionProcessor.h"
#include "SharedData.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

void initFunctionDetailsPage(FunctionDetailsPage* page, sf::Rect<int> rect) {
	page->rect = rect;

	//initializing the top bar
	sf::Vector2i btnSize(FunctionDetailsPage::navigationBtnSize, FunctionDetailsPage::navigationBtnSize);
	initButton(&page->goBackButton, 
		sf::Rect<int>(rect.getPosition() + sf::Vector2i(0, FunctionDetailsPage::topBarPadding), btnSize), 
		Palette::navigationButtonPalette());

	initButton(&page->nextButton, 
		sf::Rect(sf::Vector2i(rect.left + rect.width - btnSize.x, rect.top + FunctionDetailsPage::topBarPadding), btnSize), 
		Palette::navigationButtonPalette());

	setButtonIcon(&page->goBackButton, "GUI/Resources/goLeftIcon48x48.png");
	setButtonIcon(&page->nextButton, "GUI/Resources/goRightIcon48x48.png");

	page->goBackButton.onClick = [page]() {
		if (page->index != -1) {
			page->index--;
			if (page->index == -1) {
				page->index = SharedData::funcList.size() - 1;
			}
			page->indexChanged = true;
		}
	};

	page->nextButton.onClick = [page]() {
		if (page->index != -1) {
			page->index++;
			if (page->index == SharedData::funcList.size()) {
				page->index = 0;
			}
			page->indexChanged = true;
		}
	};
	
	const int listElemHeight = 30;
	const int listContentPadding = 10;

	int startX = rect.left + listContentPadding;
	int startY = rect.top + FunctionDetailsPage::navigationBtnSize + 3 * FunctionDetailsPage::topBarPadding;

	sf::Text& headerDomain = page->domainView.header;
	headerDomain.setString("Domain: ");
	headerDomain.setFillColor(Palette::mainTextColor());
	headerDomain.setCharacterSize(30);
	headerDomain.setFont(Palette::font());
	headerDomain.setPosition(sf::Vector2f(startX, startY));

	const int domainEditHorizontalPadding = 10;
	const int domainEditHeight = 30;

	auto& domainEdit = page->domainView.domainEdit;
	initTextEdit(&domainEdit,
		sf::Vector2i(startX + headerDomain.getLocalBounds().width + domainEditHorizontalPadding, startY + 6) ,
		sf::Vector2i(rect.width - listContentPadding - headerDomain.getLocalBounds().width - 3 * domainEditHorizontalPadding, domainEditHeight));

	domainEdit.charFilter = [page](char ch) {
		//the first character should always be a type of parantheses
		auto& domainEdit = page->domainView.domainEdit;
		std::string_view content = domainEdit.text;

		//this algorhitm is so shit fr fr i dont like this yandere dev type shit
		auto nonNullDigit = [](char ch) {
			return ch >= '1' && ch <= '9';
			};

		auto nullableDigit = [](char ch) {
			return ch >= '0' && ch <= '9';
			};
		auto validLetter = [](char ch) {
			return ch == 'i' || ch == 'n' || ch == 'f';
			};

		if (content.empty()) {
			return ch == '(' || ch == '[';
		}

		//the delete character
		if (ch == ',' && content.find(',') != std::string::npos) {
			return false;
		}
		if (ch == '`') {
			if (content.back() == 'f')
			{
				page->domainView.domainEdit.text.resize(content.size() - 3);
				return false;
			}
			return true;
		}
		if (ch == '\n' && content.back() == ')' || content.back() == ']')
			return true;

		if (content.size() == 1) {
			if (ch == 'i')
			{
				page->domainView.domainEdit.text.append("inf");
				return false;
			}
			else
				return nullableDigit(ch) || ch == '-' || ch == 'i';
		}
		else if (content.back() == '-') {
			if (ch == 'i') {
				page->domainView.domainEdit.text.append("inf");
				return false;
			}
			else
				return nonNullDigit(ch);
		}
		else if (content.back() == ',') {
			if (ch == 'i') {
				page->domainView.domainEdit.text.append("inf");
				return false;
			}
			else
				return nullableDigit(ch) || ch == '-';
		}
		else if (content.find(',') != std::string::npos && nullableDigit(content.back())) {
			return ch == ')' || ch == ']' || nullableDigit(ch);
		}
		else if (nullableDigit(content.back())) {
			return ch == ',' || nullableDigit(ch);
		}
		else if (validLetter(content.back()) && content.find(',') != std::string::npos) {
			return ch == ')' || ch == ']';
		}
		else if (validLetter(content.back()))
			return ch == ',';
		return false;
	};

	startY += float(listElemHeight) * 1.25f;
	sf::Text& asympHeader = page->asympSection.header;
	asympHeader.setCharacterSize(30);
	asympHeader.setFont(Palette::font());
	asympHeader.setFillColor(Palette::mainTextColor());
	asympHeader.setPosition(sf::Vector2f(startX, startY));
	asympHeader.setString("Asymptotes:");
	startY += float(listElemHeight) * 1.25f;

	auto applySettings = [](sf::Text& text , const sf::Vector2f& pos ) {
		text.setFont(Palette::font());
		text.setCharacterSize(20);
		text.setPosition(pos);
		text.setString("Na");
		text.setFillColor(Palette::mainTextColor());
	};

	for (int32_t i = 0; i < int32_t(AsymptoteType::COUNT); i++) {
		applySettings(page->asympSection.asympList[i] , sf::Vector2f(startX , startY));
		startY += listElemHeight;
	}
	const int barSpacing = 10;
	startY += barSpacing;

	page->subSettingsBar.setPosition(sf::Vector2f(rect.left - 8, startY));
	page->subSettingsBar.setSize(sf::Vector2f(rect.width - FunctionDetailsPage::endSettingsRadius, FunctionDetailsPage::subSettingsHeight));
	page->subSettingsBar.setFillColor(Palette::optionTabBackground());
	page->subSettingsBar.setOutlineColor(Palette::optionTabMarginColor());
	page->subSettingsBar.setOutlineThickness(5.0f);

	page->subSettingsBarEnd.setPosition(page->subSettingsBar.getPosition() +
		sf::Vector2f(page->subSettingsBar.getSize().x - FunctionDetailsPage::endSettingsRadius, 0));
	page->subSettingsBarEnd.setRadius(FunctionDetailsPage::endSettingsRadius);
	page->subSettingsBarEnd.setFillColor(Palette::optionTabBackground());
	page->subSettingsBarEnd.setOutlineColor(Palette::optionTabMarginColor());
	page->subSettingsBarEnd.setOutlineThickness(5.0f);

	sf::Vector2i minMaxBtnSize(FunctionDetailsPage::subSettingsBtnSize, FunctionDetailsPage::subSettingsBtnSize);
	auto positionList = getAlignedPositions(
		sf::Rect(startX, startY, rect.width - FunctionDetailsPage::endSettingsRadius, FunctionDetailsPage::subSettingsHeight), 2, minMaxBtnSize);


	initButton(&page->minPointsButton, sf::Rect(positionList[0], minMaxBtnSize), Palette::navigationButtonPalette());
	setButtonIcon(&page->minPointsButton, "GUI/Resources/minPointIcon48x48.png");

	initButton(&page->maxPointsButton, sf::Rect(positionList[1], minMaxBtnSize), Palette::navigationButtonPalette());
	setButtonIcon(&page->maxPointsButton, "GUI/Resources/maxPointIcon48x42.png");

	page->barLogic.list.emplace_back(&page->minPointsButton);
	page->barLogic.list.emplace_back(&page->maxPointsButton);

	selectButton(page->barLogic, 1);
	startY += barSpacing + FunctionDetailsPage::subSettingsHeight;

	const int navigatorOffsetX = 200;
	initPointNavigator(&page->pointNavigator, sf::Rect(sf::Vector2i(rect.left, startY),
		rect.getSize()));

	startY += barSpacing;
}

void updateDomain(FunctionDetailsPage* page) {
	std::string_view str = page->domainView.domainEdit.text;
	if (str.empty() == false && (str.back() == ')' || str.back() == ']')) {
		SharedData::funcList[page->index].domain = getDomain(page);
	}
}

Domain getDomain(FunctionDetailsPage* page) {
	string_view str = page->domainView.domainEdit.text;
	bool openLeft = str.front() == '(';
	bool openRight = str.back() == ')';

	page->domainView.domainEdit.done = false;
	int32_t collin = str.find(',');
	string_view firstStr = str.substr(1, collin - 1);
	string_view secondStr = str.substr(collin + 1, str.size() - firstStr.size() - 3);

	float leftVal;
	float rightVal;

	if (firstStr.size() >= 3 && firstStr.back() == 'f')
		leftVal = std::numeric_limits<float>::min() * pow(-1, firstStr.size() == 4);
	else
		leftVal = stof(firstStr.data());

	if (secondStr.size() >= 3 && firstStr.back() == 'f')
		rightVal = std::numeric_limits<float>::max() * pow(-1, secondStr.size() == 4);
	else
		rightVal = stof(secondStr.data());

	if (leftVal > rightVal) {
		return {};
	}
	else {
		return { leftVal , rightVal , openLeft , openRight , true };
	}
}

void runFunctionDetailsPage(FunctionDetailsPage* page, const Mouse& mouse, const Keyboard& kb, Chart& chart) {
	if (SharedData::funcList.size() == 0)
		page->index = -1;
	//checking if the index becomes shit
	else if (SharedData::funcList.size() - 1 < page->index)
		page->index = 0;



	runButton(&page->goBackButton, mouse);
	runButton(&page->nextButton, mouse);

	runOptionBarLogic(&page->barLogic, mouse);

	runTextEdit(&page->domainView.domainEdit, mouse , kb);
	runPointNavigator(&page->pointNavigator, mouse , chart);

	updateInformation(page);
	updateDomain(page);

	if (page->maxPointsButton.state == ViewState::SELECTED) {
		setList(page->pointNavigator, &SharedData::funcList[page->index].maxPoints);
	}
	else if (page->minPointsButton.state == ViewState::SELECTED) {
		setList(page->pointNavigator, &SharedData::funcList[page->index].minPoints);
	}
}
void drawFunctionDetailsPage(sf::RenderWindow& window, FunctionDetailsPage* page) {
	const auto& funcList = SharedData::funcList;
	sf::RectangleShape shape;
	if (page->index == -1) {
		shape.setFillColor(Palette::optionTabBackground());
	}
	else
		shape.setFillColor(funcList[page->index].color);

	shape.setSize(sf::Vector2f(page->rect.width, 4));
	shape.setPosition(SFHelper::toVec2f(page->rect.getPosition() +
		sf::Vector2i(0 , FunctionDetailsPage::navigationBtnSize + 2 * FunctionDetailsPage::topBarPadding)));

	window.draw(shape);
	drawButton(window, &page->goBackButton);
	drawButton(window, &page->nextButton);

	sf::Text title;

	if (page->index != -1) {
		title.setString(funcList[page->index].unprocessedFunc);
	}
	else {
		title.setString("No function available");
	}
	title.setFillColor(sf::Color::Black);
	title.setFont(Palette::font());
	title.setCharacterSize(20);
	title.setPosition(SFHelper::toVec2f(page->rect.getPosition() + sf::Vector2i(FunctionDetailsPage::topBarPadding * 2 + FunctionDetailsPage::navigationBtnSize,
		FunctionDetailsPage::topBarPadding + 10)));

	//drawing the title
	window.draw(title);
	//drwaing the domain stuff
	window.draw(page->domainView.header);
	drawTextEdit(window , &page->domainView.domainEdit);
	//drawing the asymptote stuff
	

	window.draw(page->asympSection.header);
	for (int32_t i = 0; i < int32_t(AsymptoteType::COUNT); i++) {
		window.draw(page->asympSection.asympList[i]);
	}

	drawPointNavigator(window , &page->pointNavigator);
	window.draw(page->subSettingsBar);
	window.draw(page->subSettingsBarEnd);

	drawButton(window, &page->minPointsButton);
	drawButton(window, &page->maxPointsButton);
}

void updateInformation(FunctionDetailsPage* page) {
	if (page->indexChanged && SharedData::funcList.size()) {
		std::stack<char> operators;
		std::stack<float> operands;
		std::string str = SharedData::funcList[page->index].funcStr;
		initFunc(str);

		int type = (int)AsymptoteType::MINUS_X;
		std::string eqStr = toString(SharedData::funcList[page->index].asymptotes[type]);
		if (eqStr.empty() == false) {
			eqStr = eqStr + " is asymptote towards -inf";
		}
		else
			eqStr = "No asymptote towards -inf";
		page->asympSection.asympList[type].setString(eqStr);


		type = (int)AsymptoteType::PLUS_X;
		eqStr = toString(SharedData::funcList[page->index].asymptotes[type]);
		if (eqStr.empty() == false) {
			eqStr = eqStr + " is equation towards inf";
		}
		else
			eqStr = "No asymptote towards inf";

		page->asympSection.asympList[type].setString(eqStr);


		page->domainView.domainEdit.text = toString(SharedData::funcList[page->index].domain);

		page->indexChanged = false;
	}
}