#include "Palette.h"
#include <iostream>

static sf::Font _font;
static Palette::Theme theme = Palette::Theme::LIGHT;

std::vector<sf::Color> chartColorList;

static sf::Color mainBgColors[] = { sf::Color(252, 252, 252) , sf::Color(44, 54, 63)};
static sf::Color mainTextColors[] = { sf::Color::Black , sf::Color::White};
static sf::Color mainContourColors[] = { sf::Color(44, 54, 63)  , sf::Color(84, 104, 120)};
static sf::Color chartBgColors[] = { sf::Color(252, 252, 252) , sf::Color(44, 54, 63) };
static sf::Color axisColors[] = { sf::Color::Black , sf::Color::White};
static sf::Color highlightColors[] = { sf::Color(255, 73, 92) , sf::Color(215, 78, 9)};
static sf::Color bgLineColors[] = { sf::Color(200, 200, 200) , sf::Color(75, 93, 108)};
static sf::Color chartTextColors[] = { sf::Color::Black , sf::Color::White};
static sf::Color optionTabBgColors[] = { sf::Color(113, 137, 255) , sf::Color(215, 78, 9) };
static sf::Color funcViewContentBgColors[] = {sf::Color(245, 245, 245) , sf::Color(44, 54, 63) };
static sf::Color optionTabMarginColors[] = {sf::Color(133, 153, 255) , sf::Color(245, 95, 20)};

static sf::Color buttonIconColors[] = { sf::Color::Black , sf::Color::White };

void Palette::setTheme(Theme theme0) {
	theme = theme0;
}
void Palette::init() {
	std::string path = "Resources/Quicksand_Book.otf";

	if (!_font.loadFromFile(path)) {
		std::cout << "ERROR" << std::endl;
	}
	else
		std::cout << path << std::endl;


	chartColorList.emplace_back(sf::Color(71, 168, 189));
	chartColorList.emplace_back(sf::Color(167, 29, 49));
	chartColorList.emplace_back(sf::Color(147, 129, 255));
	chartColorList.emplace_back(sf::Color(53, 206, 141));
	chartColorList.emplace_back(sf::Color(30, 56, 136));
	chartColorList.emplace_back(sf::Color(193, 120, 23));
	chartColorList.emplace_back(sf::Color(35, 150, 127));
	chartColorList.emplace_back(sf::Color(137, 2, 62));
	chartColorList.emplace_back(sf::Color(52, 228, 234));
}

sf::Color Palette::chartColor(int16_t ind) {
	if(ind >= chartColorList.size())
		return sf::Color::Black;

	return chartColorList[ind];
}
sf::Color Palette::mainBackgroundColor() {
	return mainBgColors[theme];
}
sf::Color Palette::mainTextColor() {
	return mainTextColors[theme];
}
sf::Color Palette::mainContourColor() {
	return mainContourColors[theme];
}
sf::Color Palette::chartBackgroundColor() {
	return chartBgColors[theme];
}

sf::Color Palette::axisColor() {
	return axisColors[theme];
}
sf::Color Palette::highlightColor() {
	return highlightColors[theme];
}

sf::Color Palette::backgroundLineColor() {
	return bgLineColors[theme];
}

sf::Color Palette::chartTextColor() {
	return chartTextColors[theme];
}

const sf::Font& Palette::font() {
	return _font;
}

sf::Color Palette::optionTabBackground() {
	return optionTabBgColors[theme];
}
sf::Color Palette::functionViewContentBackground() {
	return funcViewContentBgColors[theme];
}
sf::Color Palette::optionTabMarginColor() {
	return optionTabMarginColors[theme];

}
std::array<ViewPalette, 4> Palette::optionButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63)   ,  sf::Color::Transparent,  sf::Color::Transparent };
	pal[1] = { sf::Color(255, 187, 92) ,  sf::Color::Transparent,  sf::Color::Transparent};
	pal[2] = { sf::Color(255, 159, 28) ,  sf::Color::Transparent,  sf::Color::Transparent };
	pal[3] = { sf::Color(255, 159, 28) ,  sf::Color::Transparent,  sf::Color::Transparent };

	return pal;
}


std::array<ViewPalette, 4> Palette::loadFileButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { optionTabBackground()   , sf::Color::Transparent , optionTabBackground() };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color::Transparent , sf::Color(255, 187, 92) };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color(255, 159, 28) };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color(255, 159, 28) };

	return pal;
}
std::array<ViewPalette, 4> Palette::deleteButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(254, 74, 73)  , sf::Color::Transparent , sf::Color(254, 74, 73)  };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color::Transparent , sf::Color(255, 187, 92) };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color(255, 159, 28) };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color(255, 159, 28) };

	return pal;
}

std::array<ViewPalette, 4> Palette::addButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63), sf::Color::Transparent , sf::Color::Transparent };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color::Transparent , sf::Color::Transparent };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color::Transparent };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color::Transparent };

	return pal;
}

std::array<ViewPalette, 4> Palette::randomButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63), sf::Color::Transparent , sf::Color::Transparent };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color::Transparent , sf::Color::Transparent };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color::Transparent };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color::Transparent };

	return pal;
}

std::array<ViewPalette, 4> Palette::navigationButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63), sf::Color::Transparent , sf::Color::Transparent };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color::Transparent , sf::Color::Transparent };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color::Transparent };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color::Transparent , sf::Color::Transparent };

	return pal;
}

std::array<ViewPalette, 4> Palette::checkboxPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63)   , sf::Color(245, 245, 245), sf::Color(44, 54, 63) };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color(245, 245, 245), sf::Color(44, 54, 63) };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color(245, 245, 245), sf::Color(44, 54, 63) };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color(245, 245, 245), sf::Color(44, 54, 63) };

	return pal;
}

std::array<ViewPalette, 4> Palette::themeButtonPalette() {
	std::array<ViewPalette, 4> pal;
	pal[0] = { sf::Color(44, 54, 63)   , sf::Color(245, 245, 245), sf::Color::Transparent };
	pal[1] = { sf::Color(255, 187, 92) , sf::Color(245, 245, 245), sf::Color::Transparent };
	pal[2] = { sf::Color(255, 159, 28) , sf::Color(245, 245, 245), sf::Color::Transparent };
	pal[3] = { sf::Color(255, 159, 28) , sf::Color(245, 245, 245), sf::Color::Transparent };

	return pal;
}
