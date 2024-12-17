#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "GUICommon.h"
#include "Mouse.h"
#include "Palette.h"
#include <array>
#include <functional>


struct IconDrawer {
    sf::Image img;
    std::vector<sf::Vector2u> pixels;
    sf::Color lastColor;
    sf::Sprite sprite;
    sf::Texture texture;
};

void initIconDrawer(IconDrawer* drawer, std::string imgPath);
void drawIcon(IconDrawer* drawer , sf::RenderWindow& window ,  sf::Vector2i pos , sf::Vector2i size, sf::Color color);

struct Button{
    sf::Vector2i pos;
    sf::Vector2i size;

    ViewState state = ViewState::NONE;
    //default , but defaults is a reserved word for some reason in codeblocks
    std::array<ViewPalette , 4> paletteList;

    std::string text;

    bool selected = false;

    IconDrawer* iconDrawer = nullptr;

    bool drawCircle = false;

    std::function<void()> onClick;
};


void setButtonIcon(Button* button, std::string imagePath);
void initButton(Button* button , sf::Vector2i pos, sf::Vector2i size,  const std::array<ViewPalette , 4>& palette);
bool runButton(Button* button , const Mouse& mouse);
void drawButton(sf::RenderWindow& window, Button* button);
void setOnClick(Button* btn , std::function<void()> func);
void destroyButton(Button* button);

#endif // BUTTON_H_INCLUDED
