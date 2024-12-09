#pragma once
#include "SFML/Graphics.hpp"

struct Keyboard {
	char lastKey;
	bool keyPressed = false;

	bool samePoll = false;
	sf::Clock clock;
};

void updateKeyboard(Keyboard& kb, sf::Event ev , bool shift);