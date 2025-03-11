#include "StackedView.h"


void initStackedView(StackedView* stackedView, sf::Rect<int> rect) {
	stackedView->rect = rect;
	stackedView->option = Options::FunctionList;

	initFunctionManagerPage(&stackedView->functionPage, rect);
	initHelpPage(&stackedView->helpPage,rect);
	initFunctionDetailsPage(&stackedView->functionDetails, rect);

	stackedView->settingsPage = createSettingsPage(rect);
}
void runStackedView(StackedView* stackedView , const Mouse& mouse, const Keyboard& kb , Chart& chart) {
	switch (stackedView->option) {
	case Options::FunctionList:
		runFunctionManagerPage(&stackedView->functionPage , mouse , kb);
		break;
	case Options::Analysis:
		runFunctionDetailsPage(&stackedView->functionDetails, mouse, kb , chart);
		break;
	case Options::Settings:
		runSettingsPage(*stackedView->settingsPage, mouse);
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
	case Options::Settings:
		drawSettingsPage(window, *stackedView->settingsPage);
		break;
	case Options::Help:
		drawHelpPage(window, &stackedView->helpPage);
		break;
	default:
		break;
	}
}
void freeMem(StackedView* view) {
	destroyFunctionManagerPage(&view->functionPage);
	freeMem(&view->functionDetails);
	freeMem(view->settingsPage);
}

