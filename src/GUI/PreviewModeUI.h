#pragma once
#include "Button.h"

struct PreviewModeUI {
	sf::Rect<int> rect;
	Button goBackButton;
	Button saveToFileButton;

	static constexpr int32_t btnSize = 64;
	static constexpr int32_t spacing = 32;
};

PreviewModeUI* initPreviewModeUI(sf::Rect<int> rect);
void runPreviewModeUI(PreviewModeUI* ui, const Mouse& mouse);
void drawPreviewModeUI(sf::RenderWindow& window, PreviewModeUI* ui);