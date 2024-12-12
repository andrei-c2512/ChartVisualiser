#include "FunctionView.h"
#include "SFHelper.h"

void initFunctionView(FunctionView* view, sf::Vector2i pos, sf::Vector2i size) {
	view->pos = pos;
	view->size = size;
	view->rightMargin = 8;

	view->optionTab = new OptionTab;
	view->stackedView = new StackedView;

	const int tabStretch = 2;
	const int contentStretch = 7;

	const int segment = view->size.x / (tabStretch + contentStretch);
	const int tabWidth = segment * tabStretch;
	const int contentWidth = segment * contentStretch;

	initOptionTab(view->optionTab , view->pos , sf::Vector2i(tabWidth - 5, view->size.y));
	initStackedView(view->stackedView,
		sf::Vector2i(pos.x + tabWidth + view->rightMargin, pos.y), sf::Vector2i(contentWidth, size.y));
}
void runFunctionView(FunctionView* view, const Mouse& mouse ,const Keyboard& kb) {
	view->stackedView->option = view->optionTab->currentOption;

	runOptionTab(view->optionTab, mouse);
	runStackedView(view->stackedView, mouse, kb);
}
void drawFunctionView(sf::RenderWindow& window, FunctionView* view) {
	sf::RectangleShape rect;
	rect.setPosition(SFHelper::toVec2f(view->pos + sf::Vector2i(view->optionTab->size.x , 0)));
	rect.setSize(sf::Vector2f(view->rightMargin, view->size.y));
	rect.setFillColor(Palette::optionTabMarginColor());

	window.draw(rect);
	drawOptionTab(window , view->optionTab);
	drawStackedView(window, view->stackedView);
}
void destroyFunctionView(FunctionView* view) {
	destroyOptionTab(view->optionTab);
	destroyStackedView(view->stackedView);
}
