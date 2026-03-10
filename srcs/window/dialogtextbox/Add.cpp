#include "DialogTextBox.hpp"

void	DialogTextBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool centered)
{
	Properties		logoProperties;
	SDL_Renderer*	renderer = getRenderer();

	if (!centered)
		logoProperties.x = cursorX;

	logoProperties.y = cursorY;

	logoProperties.width = logoWidth;
	logoProperties.height = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties.x, logoProperties.y, \
		logoProperties.width, logoProperties.height, logoPath.c_str(), renderer);

	if (centered)
		image->setX(getWidth() / 2 - (image->getWidth() / 2), renderer);

	_elements.emplace_back(std::move(image));
}

void	DialogTextBox::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, fontPath, getWriteColor(), getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void	DialogTextBox::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	auto	shapeElement = std::make_unique<Shape>(cursorX, cursorY, width, \
		LIMIT_HEIGHT, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	DialogTextBox::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, fontPath, getWriteColor(), getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void    DialogTextBox::addTextField(const int cursorX, const string& fontPath, \
	const int maxText)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;
	int				limitY = getHeight() * LIMIT_RATIO;

	int				globalWidth = ((textSize * 5) / 10) * 10;
	int				globalHeight = ((textSize * 2) / 10) * 10;

	SDL_Renderer*	renderer = getRenderer();

    auto textField = std::make_unique<TextField>(cursorX, 0, 0, globalHeight, \
		getBackgroundColor(), getWriteColor(), _fontPath, getWriteColor(), maxText);

	auto mainButton = std::make_unique<TextButton>(cursorX, 0, globalWidth, \
		globalHeight, getBackgroundColor(), "OK", textSize, getWriteColor(), fontPath, renderer);

	textField->setWidth(getWidth() - (limitX * 3) - mainButton->getWidth(), renderer);
	textField->setY(getHeight() - limitY - mainButton->getHeight(), renderer);

	mainButton->setX(textField->getX() + textField->getWidth() + limitX, renderer);
	mainButton->setY(getHeight() - limitY - mainButton->getHeight(), renderer);

	mainButton->setSettings(false, NONE, true, \
		SDL_SYSTEM_CURSOR_HAND, true, true);

	textField->setSettings(true, HIGHLIGHT_SELECT, true, \
		SDL_SYSTEM_CURSOR_IBEAM, false, false);

	Color	color = BLUE;
	color.a = HIGHLIGHT_OPACITY;

	textField->setSelectColor(color);

    _buttons.reserve(2);

	_buttons.emplace_back(std::move(textField));
	_buttons.emplace_back(std::move(mainButton));
}

void	DialogTextBox::addErrorText(const int cursorX, const string& fontPath)
{
	int				limitY = getHeight() * LIMIT_RATIO;
	int				textSize = getHeight() * TEXT_RATIO;

	Color			errorColor = RED;

	SDL_Renderer*	renderer = getRenderer();

	auto	textElement = std::make_unique<Text>(cursorX, 0, "No error", \
		textSize, fontPath, errorColor, renderer);

	int		y = _buttons.front()->getY() - limitY;

	textElement->setY(y - textElement->getHeight(), renderer);
	textElement->setVisibility(false);

	_elements.emplace_back(std::move(textElement));
}
