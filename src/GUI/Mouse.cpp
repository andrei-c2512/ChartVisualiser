#include "Mouse.h"
#include <iostream>


void updateMouse(Mouse& mouse, const sf::RenderWindow& window) {
    updateDragHelper(mouse.helper);
    mouse.windowPos = sf::Mouse::getPosition(window);
}
void updateMouseByEvent(Mouse& mouse, sf::Event ev) {
    updateHelperByEvent(mouse.helper, ev);
    mouse.last = mouse.current;
    mouse.current = ev.type;
    if (ev.type == sf::Event::EventType::MouseButtonReleased)
        mouse.samePoll = false;
}

void updateDragHelper(DragHelper& helper) {
    if (helper.on) {
        helper.lastPos = helper.currentPos;
        helper.currentPos = sf::Mouse::getPosition();
    }
}
void updateHelperByEvent(DragHelper& helper, sf::Event ev){
    switch (ev.type) {
    case sf::Event::EventType::MouseButtonPressed:
        helper.on = true;
        helper.currentPos = helper.lastPos = sf::Mouse::getPosition();
        //std::cout << "Mouse button pressed" << std::endl;
        break;
    case sf::Event::EventType::MouseMoved:
        //std::cout << "Mouse moved" << std::endl;
        break;
    case sf::Event::EventType::MouseButtonReleased:
        helper.on = false;
        helper.currentPos = helper.lastPos = sf::Mouse::getPosition();
        //std::cout << "Mouse released" << std::endl;
        break;
    case sf::Event::EventType::MouseLeft:
        helper.on = false;
        helper.currentPos = helper.lastPos = sf::Mouse::getPosition();
        break;
    default:
        break;
    }
}
