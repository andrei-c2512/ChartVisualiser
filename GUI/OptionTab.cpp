#include "OptionTab.h"
#include "SFHelper.h"



void initOptionTab(OptionTab* tab, sf::Rect<int> rect) {
	tab->rect = rect;

	tab->optionList.resize(int32_t(Options::Count));

	int32_t baseHeight = rect.width;

	std::vector<Button*>& list = tab->optionList;
	for (int32_t i = 0; i < list.size(); i++) {
		list[i] = new Button;
		initButton(list[i], 
			sf::Rect(rect.getPosition() + sf::Vector2i(-3, baseHeight * i),sf::Vector2i(rect.width, baseHeight)) , 
			Palette::optionButtonPalette());
	}

	tab->backgroundColor = Palette::optionTabBackground();

	setButtonIcon(list[Options::FunctionList], "GUI/Resources/functionIcon64x60.png");
	setButtonIcon(list[Options::Analysis]    , "GUI/Resources/analysisIcon64x64.png");
	setButtonIcon(list[Options::Integral]    , "GUI/Resources/settingsIcon64x64.png");

	list[Options::Help]->rect.top = rect.top + rect.height - baseHeight;
	list[Options::Help]->rect.left = tab->rect.left - 3;
	setButtonIcon(list[Options::Help]        , "GUI/Resources/questionMarkIcon64x64.png");


	list[Options::FunctionList]->selected = true;
}


void runOptionTab(OptionTab* tab, const Mouse& mouse) {
	for (int32_t i = 0; i < tab->optionList.size(); i++) {
		bool selected = runButton(tab->optionList[i] , mouse);
		if (selected) {
			tab->optionList[i]->state = ViewState::SELECTED;
			tab->optionList[i]->selected = true;
			if (i != tab->lastSelected) {
				tab->optionList[tab->lastSelected]->state = ViewState::NONE;
				tab->optionList[tab->lastSelected]->selected = false;
				tab->lastSelected = i;
			}
			tab->currentOption = Options(i);
		}
	}
}
void drawOptionTab(sf::RenderWindow& window, OptionTab* tab) {
	sf::RectangleShape rect;
	rect.setPosition(SFHelper::toVec2f(tab->rect.getPosition()));
	rect.setSize(SFHelper::toVec2f(tab->rect.getSize()));
	rect.setFillColor(tab->backgroundColor);

	window.draw(rect);

	for (int32_t i = 0; i < tab->optionList.size(); i++) {
		drawButton(window, tab->optionList[i]);
	}
}
void destroyOptionTab(OptionTab* tab) {
	for (int32_t i = 0; i < tab->optionList.size(); i++) {
		destroyButton(tab->optionList[i]);
		delete tab->optionList[i];
	}
}

