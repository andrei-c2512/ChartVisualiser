#include "PointNavigator.h"
#include "SFHelper.h"
#include "SharedData.hpp"

void initPointNavigator(PointNavigator* navigator,sf::Rect<int> rect) {
	navigator->pointList = nullptr;
	navigator->rect = rect;
	sf::Vector2i btnSize(PointNavigator::btnSize, PointNavigator::btnSize);

	const int spacing = 10; 
	initButton(&navigator->btnUp, 
		sf::Rect(sf::Vector2i(getCentered(rect.left, rect.width, btnSize.x), rect.getPosition().y), btnSize), Palette::navigationButtonPalette());
	setButtonIcon(&navigator->btnUp, "GUI/Resources/goUpIcon48x48.png");
	rect.top += PointNavigator::btnSize + spacing;

	navigator->text.setFillColor(Palette::mainTextColor());
	navigator->text.setFont(Palette::font());
	navigator->text.setString("x , y");
	navigator->text.setCharacterSize(30);
	navigator->text.setPosition(sf::Vector2f(rect.getPosition() + sf::Vector2i(-30 , 0)));

	rect.top += PointNavigator::btnSize + spacing;

	initButton(&navigator->btnDown, 
		sf::Rect(sf::Vector2i(getCentered(rect.left , rect.width , btnSize.x) , rect.getPosition().y) , btnSize), 
		Palette::navigationButtonPalette());
	setButtonIcon(&navigator->btnDown, "GUI/Resources/goDownIcon48x48.png");

	const int offsetX = 100;
	initButton(&navigator->goThereBtn,
		sf::Rect(sf::Vector2i(navigator->text.getPosition().x, navigator->text.getPosition().y) +sf::Vector2i(rect.width - 2 * btnSize.x, 0), btnSize) ,
		Palette::navigationButtonPalette());

	setButtonIcon(&navigator->goThereBtn, "GUI/Resources/goThereIcon48x48.png");

	updateText(*navigator);
	//navigator->pointList = &SharedData::funcList[0].maxPoints;
}
void runPointNavigator(PointNavigator* navigator, const Mouse& mouse, Chart& chart) {
	runButton(&navigator->btnDown, mouse);
	runButton(&navigator->btnUp, mouse);
	runButton(&navigator->goThereBtn, mouse);

	if (navigator->pointList && navigator->pointList->size()) {
		if (navigator->btnDown.state == ViewState::PRESSED) {
			navigator->index--;
			if (navigator->index < 0) {
				navigator->index = navigator->pointList->size() - 1;
			}
			onNavigate(*navigator, chart);
		}

		if (navigator->btnUp.state == ViewState::PRESSED) {
			navigator->index++;
			if (navigator->index >= navigator->pointList->size()) {
				navigator->index = 0;
			}
			onNavigate(*navigator, chart);
		}



		if (navigator->goThereBtn.state == ViewState::PRESSED) {
			setChartPos(chart, (*navigator->pointList)[navigator->index]);
		}
	}

}
void drawPointNavigator(sf::RenderWindow& window, PointNavigator* navigator) {
	drawButton(window, &navigator->btnDown);
	drawButton(window, &navigator->btnUp);
	drawButton(window, &navigator->goThereBtn);
	window.draw(navigator->text);
}

void onNavigate(PointNavigator& navigator , Chart& chart) {
	updateText(navigator);
	if(navigator.pointList->size())
		highlightPoint(chart, (*navigator.pointList)[navigator.index]);
}

void setList(PointNavigator& navigator, std::vector<sf::Vector2f>* vec) {
	navigator.pointList = vec;
	navigator.index = std::clamp(navigator.index , 0 , (int32_t)vec->size());
	updateText(navigator);
}

void updateText(PointNavigator& navigator) {
	if(navigator.pointList)
	if (navigator.pointList->size() == 0) {
		navigator.text.setString("none");
	}
	else
		navigator.text.setString(toString((*navigator.pointList)[navigator.index]));

	auto textRect = navigator.text.getLocalBounds();
	int newX = navigator.rect.left + (navigator.rect.width - textRect.width) / 2;
	navigator.text.setPosition(sf::Vector2f(newX, navigator.text.getPosition().y));
}