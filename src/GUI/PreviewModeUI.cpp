#include "PreviewModeUI.h"

PreviewModeUI* initPreviewModeUI(sf::Rect<int> rect) {
	PreviewModeUI* ui = new PreviewModeUI;
	ui->rect = rect;


	sf::Vector2i size(PreviewModeUI::btnSize, PreviewModeUI::btnSize);
	initButton(&ui->goBackButton,
		sf::Rect(sf::Vector2i(rect.left + PreviewModeUI::spacing, rect.top + rect.height - PreviewModeUI::btnSize - PreviewModeUI::spacing), size),
		Palette::navigationButtonPalette());

	initButton(&ui->saveToFileButton,
		sf::Rect(sf::Vector2i(rect.left + rect.width - PreviewModeUI::btnSize - PreviewModeUI::spacing , 
			rect.top + rect.height - PreviewModeUI::btnSize - PreviewModeUI::spacing), size),
		Palette::navigationButtonPalette()
	);

	setButtonIcon(&ui->goBackButton, "Resources/goBackButton64x57.png");
	setButtonIcon(&ui->saveToFileButton, "Resources/saveToFileIcon64x64.png");

	return ui;
}

void runPreviewModeUI(PreviewModeUI* ui, const Mouse& mouse) {
	runButton(&ui->goBackButton, mouse);
	runButton(&ui->saveToFileButton, mouse);
}
void drawPreviewModeUI(sf::RenderWindow& window, PreviewModeUI* ui) {
	drawButton(window, &ui->goBackButton);
	drawButton(window, &ui->saveToFileButton);
}
