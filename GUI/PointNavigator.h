#pragma once
#include "Button.h"
#include "Chart.h"


struct PointNavigator {
	sf::Rect<int> rect;
	Button btnUp;
	Button btnDown;
	Button goThereBtn;
	sf::Text text;

	std::vector<sf::Vector2f>* pointList;
	int32_t index = 0;

	static constexpr int32_t btnSize = 48;
};

void initPointNavigator(PointNavigator* navigator, sf::Rect<int> rect);
void runPointNavigator(PointNavigator* navigator, const Mouse& mouse , Chart& chart);
void drawPointNavigator(sf::RenderWindow& window , PointNavigator* navigator);
void onNavigate(PointNavigator& navigator, Chart& chart);
void setList(PointNavigator& navigator , std::vector<sf::Vector2f>* vec);
void updateText(PointNavigator& navigator);