#include "TextEdit.h"
#include "Palette.h"
#include <conio.h>
#include <iostream>
#include <assert.h>
#include "SFHelper.h"



void initTextEdit(TextEdit* edit, sf::Vector2i pos, sf::Vector2i size) {
	edit->pos = pos;
	edit->size = size;
	edit->selected = false;
	edit->clock = nullptr;
	edit->text = "Example";
}
void runTextEdit(TextEdit* edit, const Mouse& mouse ,const Keyboard& kb) {

	float f = kb.clock.getElapsedTime().asSeconds();
	if (edit->selected && kb.keyPressed && kb.samePoll && !kb.usedKey && edit->charFilter(*edit , kb.lastKey)) {
		switch (kb.lastKey) {
		case '`':
				if (edit->text.empty() == false)
					edit->text.pop_back();
				break;
		case '\n':
				edit->done = true;
				edit->selected = false;
				if (edit->clock) {
					delete edit->clock;
					edit->clock = nullptr;
				}
				break;
		case '\0':
				break;
		case '$':
				edit->text += sf::Clipboard::getString();
				break;
		default:
				edit->text += kb.lastKey;
				kb.usedKey = true;
				break;
		}
	}

	sf::Vector2i mousePos = mouse.windowPos;
	if (mouse.current != sf::Event::MouseButtonPressed) 
		return;

	sf::Rect<int> rect(edit->pos, edit->size);
	if (rect.contains(mousePos)) {
		edit->selected = true;
		edit->clock = new sf::Clock;
		edit->drawCursor = true;
	}
	else {
		edit->selected = false;
		if (edit->clock) {
			delete edit->clock;
			edit->clock = nullptr;
		}
	}
}
void drawTextEdit(sf::RenderWindow& window, TextEdit* edit){
	edit->lines.clear();

	sf::Text text;
	text.setFont(Palette::font());
	text.setCharacterSize(20);
	text.setFillColor(Palette::mainTextColor());
	int lastIt = 0;
	int height = 0;

	const int maxWidth = edit->size.x - edit->bugGuard;
	if(edit->text.size())
	while (lastIt < edit->text.size()) {
		int left = lastIt, right = edit->text.size() - 1;
		int mid = right / 2;

		int lastOption = 0;
		while (left < right) {
			mid = (left + right) / 2;
			text.setString(edit->text.substr(lastIt, mid - lastIt));
			sf::FloatRect rect = text.getGlobalBounds();
			if (rect.width < maxWidth) {
				left = mid + 1;
				mid++;
			}
			else if (rect.width > maxWidth) {
				right = mid - 1;
				mid++;
			}
			else {
				lastOption = mid;
				break;
			}
		}

		//with lastOption we find a good aproximation
		//now we check if it's mid word
		int i = edit->text.length();
		if (edit->text.length() - 1 == mid) {

		}
		else if (edit->text[mid + 1] == ' ') {

		}
		else {
			int before = mid;
			while (mid >= 0 && edit->text[mid] != ' ') {
				mid--;
			}
			if (mid == 0)
				break;
			if (mid <= lastIt)
				mid = before;
		}
		std::string line = edit->text.substr(lastIt, mid - lastIt + 1);
		edit->lines.emplace_back(line);
		text.setString(line);
		text.setPosition(edit->pos.x, edit->pos.y + height);
		window.draw(text);

		height += TextEdit::lineHeight;

		lastIt = mid + 1;
		assert(height < 200);
	}
	edit->size.y = std::max(20, height); 
	const int sublineSpacing = 3;
	SFHelper::line(window , edit->pos.x, 
		edit->pos.y + edit->size.y + sublineSpacing, 
		edit->pos.x + edit->size.x, 
		edit->pos.y + edit->size.y + sublineSpacing, sf::Color::Black);

	height -= 20;
	if (edit->clock && edit->clock->getElapsedTime().asSeconds() > 0.5f) {
		edit->drawCursor = !edit->drawCursor;
		edit->clock->restart();
	}

	if (edit->drawCursor) {
		sf::FloatRect rect = text.getGlobalBounds();
		sf::RectangleShape drawable;
		drawable.setPosition(rect.getPosition() + sf::Vector2f(1+ rect.width, 0));
		drawable.setSize(sf::Vector2f(1, rect.height));
		drawable.setFillColor(sf::Color(0, 0, 0));
		window.draw(drawable);
	}
}
void destroyTextEdit(TextEdit* edit) {
	if (edit->clock)
		delete edit->clock;
}