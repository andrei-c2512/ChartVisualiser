#include "GUI/Palette.h"
#include <iostream>
static sf::Font _font;

void Palette::init() {
	std::string path = "GUI/Resources/Quicksand_Book.otf";

	if (!_font.loadFromFile(path)) {
		std::cout << "ERROR" << std::endl;
	}
	else
		std::cout << path << std::endl;

}
sf::Color Palette::mainBackgroundColor() {
	return sf::Color(252, 252, 252);
}
sf::Color Palette::mainTextColor() {
	return sf::Color::Black;
}
sf::Color Palette::mainContourColor() {
	return sf::Color(44, 54, 63);
}
sf::Color Palette::chartBackgroundColor() {
	return sf::Color(252, 252, 252);
}

sf::Color Palette::axisColor() {
	return sf::Color::Black;
}
sf::Color Palette::highlightColor() {
	return sf::Color(229, 75, 75);
}

sf::Color Palette::backgroundLineColor() {
	return sf::Color(200, 200, 200);
}

sf::Color Palette::chartTextColor() {
	return sf::Color(0 , 0 , 0);
}

const sf::Font& Palette::font() {
	return _font;
}

std::array<ViewPalette, 4> Palette::optionButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63), optionTabBackground() , sf::Color(100 , 100 , 100)};
	pal[1] = { sf::Color(255, 187, 92) , sf::Color(112, 136, 255) , sf::Color(100 , 100 , 100)};
	pal[2] = { sf::Color(255, 159, 28) , sf::Color(112, 136, 255) , sf::Color(100 , 100 , 100) };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color(112, 136, 255) , sf::Color(100 , 100 , 100) };

	return pal;
}


sf::Color Palette::optionTabBackground() {
	return sf::Color(113, 137, 255);
}
sf::Color Palette::functionViewContentBackground() {
	return sf::Color(245, 245, 245);
}
sf::Color Palette::optionTabMarginColor() {
	return sf::Color(133, 153, 255);
}

std::array<ViewPalette, 4> Palette::loadFileButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63), optionTabBackground() , sf::Color(100 , 100 , 100) };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color(112, 136, 255) , sf::Color(100 , 100 , 100) };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color(112, 136, 255) , sf::Color(100 , 100 , 100) };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color(112, 136, 255) , sf::Color(100 , 100 , 100) };

	return pal;
}
std::array<ViewPalette, 4> Palette::deleteButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63), sf::Color(254, 74, 73) , sf::Color(100 , 100 , 100)};
	pal[1] = { sf::Color(255, 187, 92) , sf::Color(254, 74, 73) , sf::Color(100 , 100 , 100) };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color(254, 74, 73) , sf::Color(100 , 100 , 100) };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color(254, 74, 73) , sf::Color(100 , 100 , 100) };

	return pal;
}