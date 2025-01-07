#pragma once
#include "SFML/Graphics.hpp"

struct HighlightAnimation {
	float totalTime;
	int32_t rings;
	sf::Color ringColor;
	sf::Vector2f pos;
	float startRadius;


	sf::Clock* clock;

	float timeBetweenRings;

	int32_t cnt;
	int32_t width;
	float space;
};

[[nodiscard]] HighlightAnimation* createAnimation(sf::Vector2f pos, float time, int32_t rings, sf::Color color , int32_t radius);
void runAnimation(sf::RenderWindow& window , HighlightAnimation& animation);
