#include "OptionTab.h"
#include "SFHelper.h"



void initOptionTab(OptionTab* tab, sf::Vector2i pos, sf::Vector2i size) {
	tab->pos = pos;
	tab->size = size;

	tab->optionList.resize(int32_t(Options::Count));

	int32_t baseHeight = size.x;

	std::vector<Button*>& list = tab->optionList;
	for (int32_t i = 0; i < list.size(); i++) {
		list[i] = new Button;
		initButton(list[i], 
			tab->pos + sf::Vector2i(0 , baseHeight * i) , 
			sf::Vector2i(size.x, baseHeight) , Palette::optionButtonPalette());

		std::cout << list[i]->pos.x << ' ' << list[i]->pos.y << std::endl;
	}

	tab->backgroundColor = Palette::optionTabBackground();

	setButtonIcon(list[Options::FunctionList], "GUI/Resources/functionIcon64x60.png");
	setButtonIcon(list[Options::Analysis], "GUI/Resources/analysisIcon64x64.png");
	setButtonIcon(list[Options::Integral], "GUI/Resources/integralIcon64x64.png");

	list[Options::About]->pos.y = pos.y + size.y - baseHeight;
	setButtonIcon(list[Options::About], "GUI/Resources/questionMarkIcon64x64.png");
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
		}
	}
}
void drawOptionTab(sf::RenderWindow& window, OptionTab* tab) {
	sf::RectangleShape rect;
	rect.setPosition(SFHelper::toVec2f(tab->pos));
	rect.setSize(SFHelper::toVec2f(tab->size));
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

