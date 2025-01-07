#pragma once
#ifndef PALETTE_H_INCLUDED
#define PALETTE_H_INCLUDED
#include "SFML/Graphics.hpp"
#include <vector>
#include <array>

struct ViewPalette {
    sf::Color textColor;
    sf::Color backgroundColor;
    sf::Color borderColor;
};

namespace Palette {
    void init();
    sf::Color mainBackgroundColor();
    sf::Color mainTextColor();
    sf::Color mainContourColor();
    sf::Color chartBackgroundColor();
    sf::Color axisColor();
    sf::Color highlightColor();
    sf::Color backgroundLineColor();
    sf::Color chartTextColor();

    sf::Color optionTabBackground();
    sf::Color functionViewContentBackground();
    sf::Color optionTabMarginColor();

    sf::Color chartColor(int16_t ind);
    const sf::Font& font();

    std::array<ViewPalette, 4> optionButtonPalette();
    std::array<ViewPalette, 4> loadFileButtonPalette();
    std::array<ViewPalette, 4> deleteButtonPalette();
    std::array<ViewPalette, 4> addButtonPalette();
    std::array<ViewPalette, 4> randomButtonPalette();
    std::array<ViewPalette, 4> navigationButtonPalette();
}


#endif // PALETTE_H_INCLUDED
