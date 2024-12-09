#include "SFHelper.h"

void SFHelper::line(int x, int y, int x1, int y1, sf::Color color) {

}

sf::Vector2f SFHelper::toVec2f(const sf::Vector2i& pos) {
	return sf::Vector2f(pos.x, pos.y);
}
