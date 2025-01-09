#pragma once
#include "GUICommon.h"
#include "FunctionManagerPage.h"
#include "../Tools.h"
#include "PointNavigator.h"
#include "OptionBarLogic.h"
#include "IntegralCalculator.h"


struct AsymptoteSection {
	sf::Text header;
	std::array<sf::Text, size_t(AsymptoteType::COUNT)> asympList;
	std::pair<Equation, Equation> horizontalEq;
};

struct DomainView {
	sf::Text header;
	TextEdit domainEdit;
};


struct FunctionDetailsPage {
	sf::Rect<int> rect;

	sf::Text title;
	int32_t index = -1;
	bool indexChanged = false;
	Button goBackButton;
	Button nextButton;

	std::string currentFunction = "None";
	static constexpr int32_t navigationBtnSize = 48;
	static constexpr int32_t topBarPadding = 10;

	DomainView domainView;
	AsymptoteSection asympSection;

	sf::RectangleShape subSettingsBar;
	sf::CircleShape subSettingsBarEnd;
	PointNavigator pointNavigator;


	OptionBarLogic barLogic;
	Button minPointsButton;
	Button maxPointsButton;

	IntegralCalculator* integralCalculator;
	
	static constexpr int32_t subSettingsBtnSize = 48;
	static constexpr int32_t subSettingsHeight = 64;
	static constexpr int32_t endSettingsRadius = 32;
};


void initFunctionDetailsPage(FunctionDetailsPage* page, sf::Rect<int> rect);
void runFunctionDetailsPage(FunctionDetailsPage* page, const Mouse& mouse, const Keyboard& kb , Chart& chart);
void updateDomain(FunctionDetailsPage* page);
void updateInformation(FunctionDetailsPage* page);
Domain getDomain(FunctionDetailsPage* page);
void drawFunctionDetailsPage(sf::RenderWindow& window, FunctionDetailsPage* page);
void freeMem(FunctionDetailsPage* page);
