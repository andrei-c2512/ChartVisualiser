#pragma once
#include "GUICommon.h"


namespace Widgets::Layout {
	enum class Alignment {
		Left, Center, Right
	};

	enum class SpacingType {
		Balanced, Dispersed
	};

	std::vector<sf::Vector2i> alignLeft(const Margins& margin , const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items , int32_t spacing);
	std::vector<sf::Vector2i> alignRight(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items , int32_t spacing);
	std::vector<sf::Vector2i> alignCenterBalancedX(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items, int32_t spacing);
	std::vector<sf::Vector2i> alignCenterDispersedX(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items);

	std::vector<sf::Vector2i> alignTop(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items , int32_t spacing);
	std::vector<sf::Vector2i> alignBottom(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items , int32_t spacing);
	std::vector<sf::Vector2i> alignCenterBalancedY(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items, int32_t spacing);
	std::vector<sf::Vector2i> alignCenterDispersedY(const Margins& margin, const sf::Rect<int>& rect, const std::vector<sf::Rect<int>*> items);
}