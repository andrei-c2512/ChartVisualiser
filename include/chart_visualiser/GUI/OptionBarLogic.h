#pragma once
#include "Button.h"

//the class doesn't actually own the buttons
struct OptionBarLogic {
	std::vector<Button*> list;
	int32_t lastSelected = 0;
};


void runOptionBarLogic(OptionBarLogic* bar , const Mouse& mouse);
void selectButton(OptionBarLogic& bar, int32_t index);