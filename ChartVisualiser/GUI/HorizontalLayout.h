#pragma once
#include "GUICommon.h"
#include "LayoutBase.h"

namespace Widgets::Layout {
	struct HorizontalLayout {
		sf::Rect<int> rect;
		std::vector<sf::Rect<int>*> list;
		Alignment alignment;
		SpacingType spacingType;
		Margins margin;
		int32_t spacing;
	};

	HorizontalLayout* createHorizontalLayout(sf::Rect<int> rect , Alignment al , SpacingType sp , const Margins& margins , int32_t spacing);
	void applyLayout(HorizontalLayout& layout);
	void updateRect(HorizontalLayout& layout, sf::Rect<int> rect);
}