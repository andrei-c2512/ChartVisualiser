#pragma once
#include "SFML/Graphics.hpp"

namespace SFHelper {
	void line(sf::RenderWindow& window , int x, int y, int x1, int y1, sf::Color color);
	sf::Vector2f toVec2f(const sf::Vector2i& pos);
}