#include "StackedView.h"


void initStackedView(StackedView* stackedView, sf::Vector2i pos, sf::Vector2i size) {
	stackedView->pos = pos;
	stackedView->size = size;
	stackedView->option = Options::FunctionList;

	initFunctionManagerPage(&stackedView->functionPage, pos, size);
	initHelpPage(&stackedView->helpPage, pos, size);
}
void runStackedView(StackedView* stackedView , const Mouse& mouse, const Keyboard& kb) {

	switch (stackedView->option) {
	case Options::FunctionList:
		runFunctionManagerPage(&stackedView->functionPage , mouse , kb);
		break;
	case Options::Analysis:
		break;
	case Options::Integral:
		break;
	case Options::Help:
		break;
	default:
		break;
	}
}
void drawStackedView(sf::RenderWindow& window, StackedView* stackedView) {
	switch (stackedView->option) {
	case Options::FunctionList:
		drawFunctionManagerPage(window , &stackedView->functionPage);
		break;
	case Options::Analysis:
		break;
	case Options::Integral:
		break;
	case Options::Help:
		drawHelpPage(window, &stackedView->helpPage);
		break;
	default:
		break;
	}
}
void destroyStackedView(StackedView* view) {

}