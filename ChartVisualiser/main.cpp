#include <iostream>
#include "GUI/MainLayout.h"
#include "SFML/Graphics.hpp"
#include <conio.h>
#include "GUI/Mouse.h"
#include "GUI/Palette.h"
#include "GUI/Keyboard.h"


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


using namespace std;

int main()
{
    Palette::init();
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ChartVisualiser");

    Mouse mouse;
    Keyboard keyboard;
    MainLayout* mainLayout = new MainLayout;
    initMainLayout(mainLayout , {WINDOW_WIDTH , WINDOW_HEIGHT} , &mouse);


    while (window.isOpen()) {
        sf::Event event;
        keyboard.samePoll = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            bool shift = event.key.shift;
            updateMouseByEvent(mouse, event);
            updateKeyboard(keyboard, event , shift);
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
