#include "Keyboard.h"
#include <iostream>

char keyToChar(sf::Keyboard::Key key, bool shift , bool control) {
    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        if (key == sf::Keyboard::V && control) {
            return '$';
        }
        char baseChar = char(key - sf::Keyboard::A + 'a'); 
        return shift ? toupper(baseChar) : baseChar; 
    }

    if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        if (shift) {
            switch (key) {
            case sf::Keyboard::Num1: return '!';
            case sf::Keyboard::Num2: return '@';
            case sf::Keyboard::Num3: return '#';
            case sf::Keyboard::Num4: return '$';
            case sf::Keyboard::Num5: return '%';
            case sf::Keyboard::Num6: return '^';
            case sf::Keyboard::Num7: return '&';
            case sf::Keyboard::Num8: return '*';
            case sf::Keyboard::Num9: return '(';
            case sf::Keyboard::Num0: return ')';
            }
        }
        else
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
    case sf::Keyboard::LShift: return '\0';
    case sf::Keyboard::RShift: return '\0';
    case sf::Keyboard::Enter: return '\n';
    default: return NULL;
    }
}

void updateKeyboard(Keyboard& kb, sf::Event ev , bool shift , bool control) {
    if (ev.type == sf::Event::KeyPressed) {
        kb.keyPressed = true;
        kb.lastKey = keyToChar(ev.key.code, shift , control );
        kb.samePoll = true;
    }
    else if(!kb.samePoll)
        kb.keyPressed = false;
}