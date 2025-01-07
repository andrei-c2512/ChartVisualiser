#include "StackedView.h"


void initStackedView(StackedView* stackedView, sf::Rect<int> rect) {
	stackedView->rect = rect;
	stackedView->option = Options::FunctionList;

	initFunctionManagerPage(&stackedView->functionPage, rect);
	initHelpPage(&stackedView->helpPage,rect);
	initFunctionDetailsPage(&stackedView->functionDetails, rect);
}
void runStackedView(StackedView* stackedView , const Mouse& mouse, const Keyboard& kb , Chart& chart) {
	switch (stackedView->option) {
	case Options::FunctionList:
		runFunctionManagerPage(&stackedView->functionPage , mouse , kb);
		break;
	case Options::Analysis:
		runFunctionDetailsPage(&stackedView->functionDetails, mouse, kb , chart);
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
		drawFunctionDetailsPage(window, &stackedView->functionDetails);
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
	destroyFunctionManagerPage(&view->functionPage);
}