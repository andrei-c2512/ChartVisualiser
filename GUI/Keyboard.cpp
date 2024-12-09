#include "Keyboard.h"
#include <iostream>

char keyToChar(sf::Keyboard::Key key, bool shift) {
    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        char baseChar = char(key - sf::Keyboard::A + 'a'); 
        return shift ? toupper(baseChar) : baseChar; 
    }

    if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        return char(key - sf::Keyboard::Num0 + '0'); 
    }

    if (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9) {
        return char(key - sf::Keyboard::Numpad0 + '0'); 
    }

    switch (key) {
    case sf::Keyboard::Space: return ' ';
    case sf::Keyboard::Period: return shift ? '>' : '.';
    case sf::Keyboard::Comma: return shift ? '<' : ',';
    case sf::Keyboard::Semicolon: return shift ? ':' : ';';
    case sf::Keyboard::Slash: return shift ? '?' : '/';
    case sf::Keyboard::BackSlash: return shift ? '|' : '\\';
    case sf::Keyboard::Quote: return shift ? '"' : '\'';
    case sf::Keyboard::Equal: return shift ? '+' : '=';
    case sf::Keyboard::Dash: return shift ? '_' : '-';
    case sf::Keyboard::LBracket: return shift ? '{' : '[';
    case sf::Keyboard::RBracket: return shift ? '}' : ']';
    case sf::Keyboard::Backspace: return '`';
    default: return NULL;
    }
}

void updateKeyboard(Keyboard& kb, sf::Event ev , bool shift) {
    if (ev.type == sf::Event::KeyPressed) {
        kb.keyPressed = true;
        kb.lastKey = keyToChar(ev.key.code, shift);
        kb.samePoll = true;

        std::cout << "CACA" << std::endl;
    }
    else if(!kb.samePoll)
        kb.keyPressed = false;
}