#include "HorizontalLayout.h"


Widgets::Layout::HorizontalLayout* Widgets::Layout::createHorizontalLayout(sf::Rect<int>& rect) {
	HorizontalLayout* layout = new HorizontalLayout;
	layout->rect = rect;
	return layout;
}
void Widgets::Layout::applyLayout(HorizontalLayout& layout) {
	std::vector<sf::Vector2i> newPosList;
	switch (layout.alignment) {
	case Alignment::Left:
		newPosList = alignLeft(layout.margin, layout.rect, layout.list, layout.spacing);
		break;
	case Alignment::Center:
		if (layout.spacingType == SpacingType::Balanced)
			newPosList = alignCenterBalancedX(layout.margin, layout.rect, layout.list, layout.spacing);
		else
			newPosList = alignCenterDispersedX(layout.margin, layout.rect, layout.list);
		break;
	case Alignment::Right:
		newPosList = alignRight(layout.margin, layout.rect, layout.list, layout.spacing);
		break;
	}
}

void Widgets::Layout::updateRect(HorizontalLayout& layout, sf::Rect<int> rect) {
	layout.rect = rect;
	applyLayout(layout);
}