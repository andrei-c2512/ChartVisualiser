#include "LayoutBase.h"

std::vector<sf::Vector2i> Widgets::Layout::alignLeft(const Margins& margin, const sf::Rect<int>& rect,
	const std::vector<sf::Rect<int>*> items, int32_t spacing) {
	if (items.size() == 0) return {};

	std::vector<sf::Vector2i> list(items.size());

	int32_t startX = margin.left;
	int32_t startY = margin.top;

	for (int32_t i = 0; i < items.size() ; i++) {
		list[i].x = startX + rect.left;
		list[i].y = (rect.height - margin.top - margin.bottom - items[i]->height) / 2 + rect.top;
		startX += spacing + items[i]->width;
	}
	return list;
}
std::vector<sf::Vector2i> Widgets::Layout::alignRight(const Margins& margin, const sf::Rect<int>& rect,
	const std::vector<sf::Rect<int>*> items, int32_t spacing) 
{
	if (items.size() == 0) return {};

	std::vector<sf::Vector2i> list(items.size());

	int32_t startX = rect.width - margin.right;
	int32_t startY = margin.top;

	for (int32_t i = 0; i < items.size(); i++) {
		startX -= items[i]->width;
		list[i].x = startX + rect.left;
		list[i].y = (rect.height - margin.top - margin.bottom - items[i]->height) / 2 + rect.top;
		startX -= spacing;
	}
	return list;
}
std::vector<sf::Vector2i> Widgets::Layout::alignCenterBalancedX(const Margins& margin, const sf::Rect<int>& rect, 
	const std::vector<sf::Rect<int>*> items, int32_t spacing) 
{
	if (items.size() == 0) return {};

	std::vector<sf::Vector2i> list(items.size());

	int32_t totalWidth = 0;
	for (const sf::Rect<int>* item : items) {
		totalWidth += item->width;
	}
	totalWidth += spacing * (items.size() - 1);

	int32_t startX = (rect.width - totalWidth) / 2;

	for (int32_t i = 0; i < items.size(); i++) {
		list[i].x = startX + rect.left;
		list[i].y = (rect.height - margin.top - margin.bottom - items[i]->height) / 2 + rect.top;

		startX += items[i]->width + spacing;
	}

	return list;
}
std::vector<sf::Vector2i> Widgets::Layout::alignCenterDispersedX(const Margins& margin, const sf::Rect<int>& rect, 
	const std::vector<sf::Rect<int>*> items)
{
	if (items.size() == 0) return {};

	std::vector<sf::Vector2i> list(items.size());
	
	int32_t totalWidth = 0;
	for (const sf::Rect<int>* item : items) {
		totalWidth += item->width;
	}
	int32_t spacing = rect.width - totalWidth - margin.left - margin.top;
	int32_t startX = margin.left;
	
	for (int32_t i = 0; i < items.size(); i++) {
		list[i].x = startX + rect.left;
		list[i].y = (rect.height - margin.top - margin.bottom - items[i]->height) / 2 + rect.top;

		startX += spacing + items[i]->width;
	}

	return list;
}

std::vector<sf::Vector2i> Widgets::Layout::alignTop(const Margins& margin, const sf::Rect<int>& rect, 
	const std::vector<sf::Rect<int>*> items, int32_t spacing)
{
	if (items.size() == 0) return {};

	std::vector<sf::Vector2i> list(items.size());

	int32_t startX = margin.left;
	int32_t startY = margin.top;

	for (int32_t i = 0; i < items.size(); i++) {
		list[i].x = (rect.width - margin.left - margin.right - items[i]->width) / 2 + rect.left;
		list[i].y = startY + rect.top;
		startY += spacing + items[i]->height;
	}
	return list;
}
std::vector<sf::Vector2i> Widgets::Layout::alignBottom(const Margins& margin, const sf::Rect<int>& rect,
	const std::vector<sf::Rect<int>*> items, int32_t spacing)
{
	if (items.size() == 0) return {};

	std::vector<sf::Vector2i> list(items.size());

	int32_t startX = margin.left;
	int32_t startY = margin.bottom;

	for (int32_t i = 0; i < items.size(); i++) {

	}

	return list;
}
std::vector<sf::Vector2i> Widgets::Layout::alignCenterBalancedY(const Margins& margin, const sf::Rect<int>& rect,
	const std::vector<sf::Rect<int>*> items, int32_t spacing) 
{
	return {};
}
std::vector<sf::Vector2i> Widgets::Layout::alignCenterDispersedY(const Margins& margin, const sf::Rect<int>& rect,
	const std::vector<sf::Rect<int>*> items)
{


	return {};
}