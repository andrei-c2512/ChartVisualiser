#include <iostream>
#include "GUI/MainLayout.h"
#include "SFML/Graphics.hpp"
#include <conio.h>
#include "GUI/Mouse.h"
#include "GUI/Palette.h"
#include "GUI/Keyboard.h"
#include "RandomFunction.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1000


using namespace std;
//x*(cos(x) + log(sin(x)))
int main()
{
    Palette::init();
    initRandomFunc();
    sf::Image icon;
    if (!icon.loadFromFile("GUI/Resources/windowIcon.png")) {
        std::cout << "Failed to load icon";
    }
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ChartVisualiser");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    Mouse mouse;
    Keyboard keyboard;
    MainLayout* mainLayout = initMainLayout(&window, sf::Rect<int>(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    std::cout << sizeof(long double) << ' ' << sizeof(double) << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        keyboard.samePoll = false;
        keyboard.usedKey = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            bool shift = event.key.shift;
            bool control = event.key.control;
            updateMouseByEvent(mouse, event);
            updateKeyboard(keyboard, event , shift , control);
        }
        updateMouse(mouse , window);
        runMainLayout(mainLayout , mouse , keyboard);

        window.clear(sf::Color::Black);
        
        drawMainLayout(window , mainLayout);
        // Display the frame

        if (keyboard.clock.getElapsedTime().asSeconds() > 0.6f)
            keyboard.clock.restart();
        window.display();
    }

    destroyMainLayout(mainLayout);
    delete mainLayout;

    return 0;
}
