#include "Checkbox.h"

Checkbox* createCheckbox(sf::Rect<int> rect) {
	Checkbox* box = new Checkbox;
	using namespace Widgets::Layout;
	box->layout = createHorizontalLayout(rect , Widgets::Layout::Alignment::Left ,Widgets::Layout::SpacingType::Balanced , { 3 , 3 , 3 , 3} , 5);
	box->layout->alignment = Alignment::Left;
	box->layout->spacingType = SpacingType::Balanced;
	box->layout->spacing = 10;

	initButton(&box->button, sf::Rect<int>(0, 0, Checkbox::checkboxSize, Checkbox::checkboxSize) , Palette::checkboxPalette());

	box->text.setCharacterSize(16);
	box->text.setFont(Palette::font());
	box->text.setFillColor(Palette::mainTextColor());

	auto rectf = box->text.getLocalBounds();
	box->textRect = sf::Rect<int>(rectf.left , rectf.top , rectf.width , rectf.height);
	std::vector<sf::Rect<int>*> list = { &box->textRect , &box->button.rect };

	applyLayout(*box->layout);

	return box;
}
void runCheckbox(Checkbox& checkbox, const Mouse& mouse) {
	runButton(&checkbox.button, mouse);
}
void drawCheckbox(sf::RenderWindow& window, Checkbox& checkbox) {
	window.draw(checkbox.text);
	drawButton(window, &checkbox.button);
}
void freeMem(Checkbox* checkbox) {
	delete checkbox->layout;
}