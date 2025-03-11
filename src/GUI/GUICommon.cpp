#include "GUICommon.h"



sf::Rect<int> adjustRectToMargins(const sf::Rect<int>& rect, const Margins& margin) {
	return sf::Rect<int>(rect.left + margin.left, rect.top + margin.top,
		rect.width - margin.right - margin.left ,
		rect.height - margin.top - margin.bottom);
}

int horizontalSizeByStretchFactor(int totalSize , int segments , int stretch){
    const float segmentW = float(totalSize) / segments;

    return int(segmentW * float(stretch));
}

std::vector<sf::Vector2i> getAlignedPositionsX(const sf::Rect<int>& rect, int items , const sf::Vector2i& itemSize) {
	std::vector<sf::Vector2i> list(items);
	int spacingY = (rect.height - itemSize.y) / 2;
	int spacingX = (rect.width - items * itemSize.x) / (items + 1);

	int startX = spacingX;
	int startY = spacingY;
	for (sf::Vector2i& point : list) {
		point.x = startX + rect.left;
		point.y = startY + rect.top;

		startX += spacingX + itemSize.x;
	}
	return list;
}

std::vector<sf::Vector2i> getAlignedPositionsY(const sf::Rect<int>& rect, int items, const sf::Vector2i& itemSize) {
    std::vector<sf::Vector2i> list(items);
    int spacingX = (rect.width - itemSize.x) / 2;
    int spacingY = (rect.height - items * itemSize.y) / (items + 1);

    int startX = spacingX;
    int startY = spacingY;
    for (sf::Vector2i& point : list) {
        point.x = startX + rect.left;
        point.y = startY + rect.top;

        startY += spacingY + itemSize.y;
    }
    return list;
}

int32_t getCentered(int32_t x, int32_t width, int32_t itemWidth) noexcept {
    return x + (width - itemWidth) / 2;
}

std::vector<sf::Vector2i> getDispersedPositionY(const sf::Rect<int>& rect, int items, const sf::Vector2i& itemSize) {
    std::vector<sf::Vector2i> list(items);
    int spacingX = (rect.width - itemSize.x) / 2;
    int spacingY = (rect.height - items * itemSize.y) / (items - 1);

    int startX = spacingX;
    int startY = 0;

    for (sf::Vector2i& point : list) {
        point.x = startX + rect.left;
        point.y = startY + rect.top;

        startY += spacingY + itemSize.y;
    }

    return list;
}

sf::Vector2f topRight(const sf::Text& text) {
    return sf::Vector2f(text.getPosition() + sf::Vector2f(text.getLocalBounds().width, 0));
}



double multiplierByZoom(double zoom) {
    if (zoom < 0.005f) {
        return 2500.0;
    }
    else if (zoom < 0.01f) {
        return 1000.0;
    }
    else if (zoom < 0.05f) {
        return 250.0;
    }
    else if (zoom < 0.1f) {
        return 50.0;
    }
    else if (zoom < 0.25f) {
        return 10.0;
    }
    else if (zoom < 0.5f)
    {
        return 5.0;
    }
    else if (zoom < 0.75) {
        return 2.0;
    }
    else if (zoom < 1.0)
    {
        return 2.0;
    }
    else if (zoom < 2.0)
    {
        return 1.0;
    }
    else if (zoom < 4.0) {
        return 0.5;
    }
    else if (zoom < 5.0) {
        return 0.5;
    }
    else if (zoom < 7.0) {
        return 0.2;
    }
    else if (zoom < 10.0) {
        return 0.1;
    }
    else if (zoom < 20.0)
        return 0.1;

    return 0.05;
}

