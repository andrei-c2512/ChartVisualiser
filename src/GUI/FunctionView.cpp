#include "FunctionView.h"
#include "SFHelper.h"

void initFunctionView(FunctionView* view, sf::Rect<int> rect) {
	view->rect = rect;
	view->rightMargin = 8;

	view->optionTab = new OptionTab;
	view->stackedView = new StackedView;

	const int tabStretch = 2;
	const int contentStretch = 7;

	const int segment = view->rect.width / (tabStretch + contentStretch);
	const int tabWidth = segment * tabStretch;
	const int contentWidth = segment * contentStretch;

	initOptionTab(view->optionTab , sf::Rect<int>(rect.getPosition(), sf::Vector2i(tabWidth - 5, view->rect.height)));
	initStackedView(view->stackedView,
		sf::Rect(sf::Vector2i(rect.left + tabWidth + view->rightMargin, rect.top), sf::Vector2i(contentWidth, rect.height)));
}

void setRect(FunctionView* view, sf::Rect<int> rect) {

}
void runFunctionView(FunctionView* view, const Mouse& mouse ,const Keyboard& kb, Chart& chart) {
	auto before = view->stackedView->option;
	view->stackedView->option = view->optionTab->currentOption;

	if (before != view->stackedView->option && view->stackedView->option == Options::Analysis) {
		view->stackedView->functionDetails.indexChanged = true;
	}
	runOptionTab(view->optionTab, mouse);
	runStackedView(view->stackedView, mouse, kb , chart);
	if (view->stackedView->option == Options::FunctionList) {
		int index = detailsButtonPressed(&view->stackedView->functionPage);
		if (index != -1) {
			auto& optionList = view->optionTab->optionList;

			view->optionTab->lastSelected = int(Options::Analysis);
			optionList[Options::Analysis]->selected = true;
			optionList[Options::Analysis]->state = ViewState::SELECTED;
			optionList[Options::FunctionList]->selected = false;
			optionList[Options::FunctionList]->state = ViewState::NONE;
			view->stackedView->option = view->optionTab->currentOption = Options::Analysis;
			view->stackedView->functionDetails.index = index;
			view->stackedView->functionDetails.indexChanged = true;
		}
	}
}
void drawFunctionView(sf::RenderWindow& window, FunctionView* view) {
	sf::RectangleShape rect;
	rect.setPosition(SFHelper::toVec2f(view->rect.getPosition() + sf::Vector2i(view->optionTab->rect.width, 0)));
	rect.setSize(sf::Vector2f(view->rightMargin, view->rect.height));
	rect.setFillColor(Palette::optionTabMarginColor());

	window.draw(rect);
	drawOptionTab(window , view->optionTab);
	drawStackedView(window, view->stackedView);
}
void destroyFunctionView(FunctionView* view) {
	destroyOptionTab(view->optionTab);
	freeMem(view->stackedView);

	delete view->optionTab;
	delete view->stackedView;
}
