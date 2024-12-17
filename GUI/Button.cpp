#include "Button.h"
#include "SFHelper.h"


void initIconDrawer(IconDrawer* drawer, std::string imgPath) {
	if (drawer->img.loadFromFile(imgPath) == false)
		std::cout << "Failed to load icon";

	sf::Vector2u imgSize = drawer->img.getSize();

	for (int32_t y = 0; y < imgSize.y; y++) {
		for (int32_t x = 0; x < imgSize.x; x++) {
			sf::Color color = drawer->img.getPixel(x, y);
			if (color.a != 0) {
				drawer->pixels.emplace_back(sf::Vector2u(x, y));
			}
		}
	}


}

void drawIcon(IconDrawer* drawer, sf::RenderWindow& window  , sf::Vector2i pos , sf::Vector2i size, sf::Color color) {
	if (color != drawer->lastColor) {
		for (const sf::Vector2u& point : drawer->pixels) {
			drawer->img.setPixel(point.x, point.y, color);
		}
		drawer->texture.loadFromImage(drawer->img);
		drawer->texture.setSmooth(true);
		drawer->sprite.setTexture(drawer->texture);


		sf::Vector2i newPos = pos + sf::Vector2i((size.x - drawer->texture.getSize().x) / 2, (size.y - drawer->texture.getSize().y) / 2);
		drawer->sprite.setPosition(SFHelper::toVec2f(newPos));
		window.draw(drawer->sprite);

		drawer->lastColor = color;
	}
	else {
		sf::Vector2i newPos = pos + sf::Vector2i((size.x - drawer->texture.getSize().x) / 2, (size.y - drawer->texture.getSize().y) / 2);
		drawer->sprite.setPosition(SFHelper::toVec2f(newPos));
		window.draw(drawer->sprite);
	}
}




void initButton(Button* button , sf::Vector2i pos0 , sf::Vector2i size0 , const std::array<ViewPalette , 4>& palette){
	button->pos = pos0;
	button->size = size0;
	button->paletteList = palette;
	button->onClick = []() {};
}
bool runButton(Button* button , const Mouse& mouse){
	const sf::Vector2i& mousePos = mouse.windowPos;
	sf::Rect<int> rect( button->pos , button->size );
	bool in = rect.contains(mousePos);

	if (in) {
		if (mouse.current == sf::Event::MouseButtonPressed && mouse.samePoll == false)
		{
			button->state = ViewState::PRESSED;
			button->onClick();
			mouse.samePoll = true;
			return true;
		}
		else
		{
			button->state = ViewState::HOVERED;
		}
	}
	else if (button->selected) {
		button->state = ViewState::SELECTED;
	}
	else
		button->state = ViewState::NONE;

	return false;
}
void drawButton(sf::RenderWindow& window , Button* button){
	assert(button->paletteList.size() == ViewState::COUNT);

	if (button->state == ViewState::SELECTED)
		int i = 0;
	const ViewPalette& p = button->paletteList[int(button->state)];


	if (button->text.empty() == false) {
		sf::Text text;
		text.setString(button->text);
		text.setFont(Palette::font());
		text.setFillColor(Palette::mainTextColor());
		text.setPosition(SFHelper::toVec2f(button->pos));
	}
	
	if (button->drawCircle) {
		sf::CircleShape shape;
		shape.setPosition(SFHelper::toVec2f(button->pos));
		shape.setOutlineColor(p.borderColor);
		shape.setFillColor(p.backgroundColor);
		shape.setRadius(button->size.x / 2);
		shape.setOutlineThickness(3);

		window.draw(shape);
	}
	else
	{
		sf::RectangleShape rect;
		rect.setFillColor(p.backgroundColor);
		rect.setOutlineColor(p.borderColor);
		rect.setSize(SFHelper::toVec2f(button->size));
		rect.setPosition(SFHelper::toVec2f(button->pos));
		rect.setOutlineThickness(3);
		window.draw(rect);
	}

	if (button->iconDrawer) {
		drawIcon(button->iconDrawer, window, button->pos , button->size , p.textColor);
	}
}


void setButtonIcon(Button* button, std::string imagePath) {
	button->iconDrawer = new IconDrawer;
	initIconDrawer(button->iconDrawer, imagePath);
}

void destroyButton(Button* button) {
	if (button->iconDrawer) {
		delete button->iconDrawer;
	}
}

void setOnClick(Button* btn , std::function<void()> func) {
	btn->onClick = func;
}