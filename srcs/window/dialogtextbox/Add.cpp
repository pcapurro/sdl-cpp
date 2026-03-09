#include "DialogTextBox.hpp"

void	DialogTextBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool centered)
{
	Properties		logoProperties;

	if (!centered)
		logoProperties.x = cursorX;

	logoProperties.y = cursorY;

	logoProperties.width = logoWidth;
	logoProperties.height = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties.x, logoProperties.y, \
		logoProperties.width, logoProperties.height, logoPath.c_str(), getRenderer());

	if (centered)
		image.get()->setX(getWidth() / 2 - (image.get()->getWidth() / 2), getRenderer());

	_elements.emplace_back(std::move(image));
}

void	DialogTextBox::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

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
		textSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void    DialogTextBox::addTextField(const int cursorX, const string& fontPath, \
	const int maxText)
{
    int		textSize = getHeight() * TEXT_RATIO;
	int		limitX = getWidth() * LIMIT_RATIO;
	int		limitY = getHeight() * LIMIT_RATIO;

	int		globalWidth = ((textSize * 5) / 10) * 10;
	int		globalHeight = ((textSize * 2) / 10) * 10;

    auto textField = std::make_unique<TextField>(cursorX, 0, 0, globalHeight, \
		getBackgroundColor(), getWriteColor(), _fontPath, getWriteColor(), maxText);

	auto mainButton = std::make_unique<TextButton>(cursorX, 0, globalWidth, \
		globalHeight, getBackgroundColor(), "OK", textSize, getWriteColor(), fontPath, getRenderer());

	TextField*	text = textField.get();
	TextButton*	button = mainButton.get();

	text->setWidth(getWidth() - (limitX * 3) - button->getWidth(), getRenderer());
	text->setY(getHeight() - limitY - button->getHeight(), getRenderer());

	button->setX(text->getX() + text->getWidth() + limitX, getRenderer());
	button->setY(getHeight() - limitY - button->getHeight(), getRenderer());

	button->setSettings(false, NONE, true, \
		SDL_SYSTEM_CURSOR_HAND, true, true);

	text->setSettings(true, HIGHLIGHT_SELECT, true, \
		SDL_SYSTEM_CURSOR_IBEAM, false, false);

	Color	color = BLUE;

	color.a = HIGHLIGHT_OPACITY;
	text->setSelectColor(color);

    _buttons.reserve(2);

	_buttons.emplace_back(std::move(textField));
	_buttons.emplace_back(std::move(mainButton));
}

void	DialogTextBox::addErrorText(const int cursorX, const string& fontPath)
{
	int		limitY = getHeight() * LIMIT_RATIO;
	int		textSize = getHeight() * TEXT_RATIO;

	Color	errorColor = RED;

	auto	textElement = std::make_unique<Text>(cursorX, 0, "No error", \
		textSize, errorColor, fontPath, getRenderer());

	int		y = _buttons.front().get()->getY() - (limitY / 2);

	textElement.get()->setY(y - textElement.get()->getHeight(), getRenderer());
	textElement.get()->setVisibility(false);

	_elements.emplace_back(std::move(textElement));
}
