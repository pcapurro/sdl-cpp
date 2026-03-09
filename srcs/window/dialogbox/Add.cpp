#include "DialogBox.hpp"

void	DialogBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
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

void	DialogBox::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void	DialogBox::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	auto	shapeElement = std::make_unique<Shape> (cursorX, cursorY, \
		width, LIMIT_HEIGHT, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	DialogBox::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void	DialogBox::addButtons(const string& fontPath, \
	const vector<string>& buttonsTexts)
{
	int		textSize = getHeight() * TEXT_RATIO;
	int		spaceSize = (getWidth() * LIMIT_RATIO);
	int		limitY = getHeight() * LIMIT_RATIO;
	int		totalWidth = 0;

    _buttons.reserve(4);

	for (size_t i = 0; i < buttonsTexts.size() && i < MAX_BUTTONS; i++)
	{
		auto button = std::make_unique<TextButton>(0, 0, ((textSize * 5) / 10) * 10, \
			((textSize * 2) / 10) * 10, getBackgroundColor(), buttonsTexts[i], textSize, \
			getWriteColor(), fontPath, getRenderer());

		button.get()->setY(getHeight() - limitY - button.get()->getHeight(), getRenderer());
		button.get()->setSettings(false, NONE, true, SDL_SYSTEM_CURSOR_HAND, true, true);

		totalWidth += button.get()->getWidth();
		if (i + 1 < buttonsTexts.size() && i + 1 < MAX_BUTTONS)
			totalWidth += spaceSize;

		_buttons.emplace_back(std::move(button));
	}

	int		cursorX = (getWidth() / 2) - (totalWidth / 2);

	for (const auto& button : _buttons)
	{
		button->setX(cursorX, getRenderer());
		button->setY(getHeight() - limitY - button->getHeight(), getRenderer());

		button->setSettings(false, NONE, true, \
			SDL_SYSTEM_CURSOR_HAND, true, true);

		cursorX += button->getWidth() + spaceSize;
	}
}
