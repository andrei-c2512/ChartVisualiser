#include "SettingsPage.h"
#include "StringResources.hpp"
#include "SFHelper.h"


SettingsPage* createSettingsPage(sf::Rect<int> rect) {
	SettingsPage* page = new SettingsPage;
	page->rect = rect;

	page->title.setCharacterSize(30);
	page->title.setFont(Palette::font());
	page->title.setFillColor(Palette::mainTextColor());
	page->title.setString("Settings");
	page->title.setPosition(SFHelper::toVec2f(rect.getPosition()));

	page->languageList.resize((int)StringResources::Languages::COUNT);

	sf::Vector2i btnSize(SettingsPage::themeButtonSize, SettingsPage::themeButtonSize);
	initButton(&page->lightModeBtn, sf::Rect<int>(sf::Vector2<int>(0 ,  0),  btnSize), Palette::themeButtonPalette());
	setButtonIcon(&page->lightModeBtn, "GUI/Resources/lightModeIcon48x48.png");
	initButton(&page->darkModeBtn, sf::Rect<int>(sf::Vector2<int>(0, 0), btnSize), Palette::themeButtonPalette());
	setButtonIcon(&page->darkModeBtn, "GUI/Resources/darkModeIcon48x48.png");
	


	page->btnLayout = Widgets::Layout::createHorizontalLayout(
		sf::Rect<int>((int)page->title.getPosition().x, (int)page->title.getPosition().y + page->title.getLocalBounds().height, rect.width, btnSize.y),
		Widgets::Layout::Alignment::Center , Widgets::Layout::SpacingType::Balanced , { 5 ,5, 5 ,5} , 5);

	page->btnLayout->list.emplace_back(&page->lightModeBtn.rect);
	page->btnLayout->list.emplace_back(&page->darkModeBtn.rect);
	Widgets::Layout::applyLayout(*page->btnLayout);

	sf::Rect<int> checkboxRect = sf::Rect(0, 0, 150, 50);
	for (int32_t i = 0; i < page->languageList.size() ; i++) {
		page->languageList[i] = createCheckbox(checkboxRect);
	}
	
	

	return page;
}
void runSettingsPage(SettingsPage& page, const Mouse& mouse) {
	runButton(&page.darkModeBtn, mouse);
	runButton(&page.lightModeBtn, mouse);
}
void drawSettingsPage(sf::RenderWindow& window, SettingsPage& page) 
{
	window.draw(page.title);
	drawButton(window , &page.lightModeBtn);
	drawButton(window , &page.darkModeBtn);
}
void freeMem(SettingsPage* page) {
	for (Checkbox* box : page->languageList) {
		freeMem(box);
	}
}