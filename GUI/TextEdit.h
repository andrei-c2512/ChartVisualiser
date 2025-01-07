#pragma once
#include "SFML/Graphics.hpp"
#include "Mouse.h"
#include "Keyboard.h"
#include <functional>

struct TextEdit {
	sf::Vector2i pos;
	sf::Vector2i size;

	sf::Color underlineColor;

	int32_t characterLimit;
	//int32_t offset;

	std::string text;
	bool selected;

	sf::Clock* clock = nullptr;
	bool drawCursor = false;
	std::vector<std::string> lines;
	static constexpr int32_t lineHeight = 20;

	int32_t bugGuard = 30;
	bool done = false;

	std::function<bool(char)> charFilter = [](char ch) { return true; };
};

void initTextEdit(TextEdit* edit, sf::Vector2i pos, sf::Vector2i size);
void runTextEdit(TextEdit* edit, const Mouse& mouse , const Keyboard& kb);
void drawTextEdit(sf::RenderWindow& window, TextEdit* edit);
void destroyTextEdit(TextEdit* edit);
