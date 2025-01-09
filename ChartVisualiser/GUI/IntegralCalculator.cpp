#include "IntegralCalculator.h"
#include "SFHelper.h"
#include "Palette.h"
#include "../Tools.h"


IntegralCalculator* createIntegralCalculator(sf::Rect<int> rect) {
	IntegralCalculator* calc = new IntegralCalculator;

	if (calc->integralTexture.loadFromFile("GUI/Resources/integralIcon128x128.png") == false) {
		std::cout << "Could not load integral image";
	}
	
	calc->integralSprite.setTexture(calc->integralTexture);

	const int textRectWidth = 120;
	const int characterSize = 20;
	const int integralSize = 128;

	calc->integralSprite.setPosition(sf::Vector2f(rect.left, getCentered(rect.top, integralSize + 2 * characterSize, integralSize)));


	sf::Rect<int> textBox = sf::Rect(rect.left + integralSize, rect.top, textRectWidth, integralSize  + 2 * characterSize);
	auto list = getDispersedPositionY(textBox, 2, sf::Vector2i(characterSize , characterSize));
	
	calc->startText.setPosition(SFHelper::toVec2f(list[0]));
	calc->endText.setPosition(SFHelper::toVec2f(list[1]));

	auto initText = [characterSize](sf::Text& text) {
		text.setCharacterSize(characterSize);
		text.setFillColor(Palette::mainTextColor());
		text.setFont(Palette::font());
		};

	initText(calc->startText);
	initText(calc->endText);

	calc->startText.setString("Start");
	calc->endText.setString("End");

	auto startTextSize = calc->startText.getLocalBounds();
	const auto lineEditSize = sf::Vector2i(120, characterSize);

	const int integralImageRight = calc->integralSprite.getPosition().x + calc->integralTexture.getSize().x;

	initTextEdit(&calc->startEdit, sf::Vector2i(integralImageRight, list[0].y), lineEditSize);

	auto endTextSize = calc->endText.getLocalBounds();
	initTextEdit(&calc->endEdit, sf::Vector2i(integralImageRight, list[1].y), lineEditSize);

	initText(calc->equationText);
	const int equationCharacterSize = 40;
	calc->equationText.setCharacterSize(equationCharacterSize);
	calc->equationText.setString("f(x) = ");
	calc->equationText.setPosition(sf::Vector2f(integralImageRight , getCentered(rect.top, integralSize + 2 * characterSize, equationCharacterSize)));


	initText(calc->resultText);
	calc->resultText.setCharacterSize(equationCharacterSize);
	calc->resultText.setPosition(topRight(calc->equationText));
	calc->resultText.setString("...");

	auto filter = [](TextEdit& edit , char ch) {
		std::string_view text = edit.text;
		float num = floatNumber(edit.text);

		if (ch == '`' || ch == '\n')
			return true;

		if (text.size() == 0)
			return digit(ch);
		if (num == std::numeric_limits<float>::max()) {

		}
		else {
			if (num == 0.0f) {
				if (text.find('.') != std::string::npos)
				{
					return digit(ch);
				}
				else {
					return digit(ch) || ch == '.';
				}
			}
			else {
				if (text.find('.') != std::string::npos)
				{
					return digit(ch);
				}
				else {
					return digit(ch) || ch == '.';
				}
			}
		}
		return false;
	};

	calc->endEdit.charFilter = filter;
	calc->startEdit.charFilter = filter;
	return calc;
}
void runIntegralCalculator(IntegralCalculator& calculator, const Mouse& mouse, const Keyboard& kb, FunctionString& funcStr) {
	runTextEdit(&calculator.endEdit , mouse , kb);
	runTextEdit(&calculator.startEdit, mouse, kb);

	updateResult(calculator , funcStr);
}
void drawIntegralCalculator(sf::RenderWindow& window, IntegralCalculator& calculator) {
	window.draw(calculator.integralSprite);
	//window.draw(calculator.startText);
	//window.draw(calculator.endText);
	window.draw(calculator.equationText);
	window.draw(calculator.resultText);
	drawTextEdit(window, &calculator.endEdit);
	drawTextEdit(window, &calculator.startEdit);
}

void updateResult(IntegralCalculator& calculator, FunctionString& funcStr) {
	float down = floatNumber(calculator.endEdit.text);
	float up = floatNumber(calculator.startEdit.text);

	if (!(down == std::numeric_limits<float>::max() || up == std::numeric_limits<float>::max()) && down <= up)
	{
		float result = calculateIntegral(funcStr.funcStr, {}, {}, funcStr.steps, down, up);
		calculator.resultText.setString(std::to_string(result));
	}
	else
		calculator.resultText.setString("...");
}