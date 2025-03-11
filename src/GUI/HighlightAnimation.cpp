#include "HighlightAnimation.h"
#include <iostream>

[[nodiscard]] HighlightAnimation* createAnimation(sf::Vector2f pos, float time, int32_t rings, sf::Color color , int32_t radius) {
	HighlightAnimation* anim = new HighlightAnimation;
	anim->pos = pos;
	anim->totalTime = time;
	anim->rings = rings;
	anim->ringColor = color;

	anim->clock = nullptr;

	anim->timeBetweenRings = time / float(rings * 2 - 1);
	anim->cnt = 0;
	anim->startRadius = radius;
	anim->width = 3;
	anim->space = 1.0f;
	return anim;
}
void runAnimation(sf::RenderWindow& window, HighlightAnimation& anim) {
	if (anim.cnt == anim.rings * 2) return;
	if (anim.clock == nullptr) {
		anim.clock = new sf::Clock;
		return;
	}

	if (anim.clock->getElapsedTime().asSeconds() >= anim.timeBetweenRings) {
		anim.clock->restart();
		anim.cnt++;

		if (anim.cnt == anim.rings * 2) {
			delete anim.clock;
		}
		if (anim.cnt < anim.rings) {
			anim.startRadius += anim.space;
		}
		else
			anim.startRadius -= anim.space;
	}
	sf::CircleShape circle;
	circle.setOrigin(sf::Vector2f(anim.startRadius, anim.startRadius));
	circle.setPosition(anim.pos);
	circle.setRadius(anim.startRadius);
	circle.setOutlineThickness(anim.width);
	circle.setOutlineColor(anim.ringColor);
	circle.setFillColor(sf::Color::Transparent);

	window.draw(circle);
}
