#include "HorizontalLayout.h"


Widgets::Layout::HorizontalLayout* Widgets::Layout::createHorizontalLayout(sf::Rect<int> rect, 
	Alignment al, SpacingType sp, const Margins& margins, int32_t spacing) 
{
	HorizontalLayout* layout = new HorizontalLayout;

	layout->margin = margins;
	layout->spacing = spacing;
	layout->spacingType = sp;
	layout->alignment = al;
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

	for (int32_t i = 0; i < newPosList.size(); i++) {
		layout.list[i]->left = newPosList[i].x;
		layout.list[i]->top = newPosList[i].y;
	}
}

void Widgets::Layout::updateRect(HorizontalLayout& layout, sf::Rect<int> rect) {
	layout.rect = rect;
	applyLayout(layout);
}