#pragma once
#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED
#include "SFML/Graphics.hpp"


struct DragHelper{
    sf::Vector2<int> lastPos;
    sf::Vector2<int> currentPos;


    bool on = false;
};

struct Mouse{
    DragHelper helper;
    sf::Event::EventType last;
    sf::Event::EventType current;

    sf::Vector2i windowPos;
};

void updateMouseByEvent(Mouse& mouse , sf::Event ev);
void updateMouse(Mouse& mouse , const sf::RenderWindow& window );
void updateHelperByEvent(DragHelper& helper, sf::Event ev);
void updateDragHelper(DragHelper& helper);

#endif // MOUSE_H_INCLUDED
