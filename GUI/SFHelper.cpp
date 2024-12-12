#include "SFHelper.h"

void SFHelper::line(sf::RenderWindow& window, int x, int y, int x1, int y1, sf::Color color) {
    sf::Vertex line[2] = {
            sf::Vertex(sf::Vector2f(x , y) , color) ,
            sf::Vertex(sf::Vector2f(x1 , y1), color)
    };
    window.draw(line, 2, sf::Lines);
}

sf::Vector2f SFHelper::toVec2f(const sf::Vector2i& pos) {
	return sf::Vector2f(pos.x, pos.y);
}
