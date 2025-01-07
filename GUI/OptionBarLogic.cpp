#include "OptionBarLogic.h"

void runOptionBarLogic(OptionBarLogic* bar , const Mouse& mouse) {
	for (int32_t i = 0; i < bar->list.size(); i++) {
		bool selected = runButton(bar->list[i], mouse);
		if (selected) {
			bar->list[i]->state = ViewState::SELECTED;
			bar->list[i]->selected = true;
			if (i != bar->lastSelected) {
				bar->list[bar->lastSelected]->state = ViewState::NONE;
				bar->list[bar->lastSelected]->selected = false;
				bar->lastSelected = i;
			}
		}
	}
}

void selectButton(OptionBarLogic& bar, int32_t index) {
	if (bar.list.size() > index && index <= 0)
	{
		bar.list[index]->state = ViewState::SELECTED;
		bar.list[index]->selected = true;
		if (index != bar.lastSelected) {
			bar.list[bar.lastSelected]->state = ViewState::NONE;
			bar.list[bar.lastSelected]->selected = false;
			bar.lastSelected = index;
		}
	}
}