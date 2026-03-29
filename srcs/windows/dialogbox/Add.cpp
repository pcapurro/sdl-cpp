#include "DialogBox.hpp"

void	DialogBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
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

void	DialogBox::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * Render::TitleRatio;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, fontPath, getWriteColor(), maxWidth, true, getRenderer());

	_elements.emplace_back(std::move(textElement));
}

void	DialogBox::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	auto	shapeElement = std::make_unique<Shape> (cursorX, cursorY, \
		width, limitHeight, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	DialogBox::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * Render::TextRatio;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, fontPath, getWriteColor(), maxWidth, true, getRenderer());

	_elements.emplace_back(std::move(textElement));
}

void	DialogBox::addButtons(const string& fontPath, \
	const vector<string>& buttonsTexts)
{
	int				textSize = getHeight() * Render::TextRatio;
	int				spaceSize = (getWidth() * Render::LimitRatio);
	int				limitY = getHeight() * Render::LimitRatio;
	int				totalWidth = 0;

	SDL_Renderer*	renderer = getRenderer();

    _buttons.reserve(4);

	for (size_t i = 0; i < buttonsTexts.size() && i < 4; i++)
	{
		auto button = std::make_unique<TextButton>(0, 0, ((textSize * 5) / 10) * 10, \
			((textSize * 2) / 10) * 10, getBackgroundColor(), buttonsTexts[i], textSize, \
			getWriteColor(), fontPath, renderer);

		button->setY(getHeight() - limitY - button->getHeight(), renderer);
		button->setSettings(false, State::None, true, SDL_SYSTEM_CURSOR_HAND, true, true);

		totalWidth += button->getWidth();
		if (i + 1 < buttonsTexts.size() && i + 1 < 4)
			totalWidth += spaceSize;

		_buttons.emplace_back(std::move(button));
	}

	int		cursorX = (getWidth() / 2) - (totalWidth / 2);

	for (const auto& button : _buttons)
	{
		button->setX(cursorX, renderer);
		button->setY(getHeight() - limitY - button->getHeight(), renderer);

		button->setSettings(false, State::None, true, \
			SDL_SYSTEM_CURSOR_HAND, true, true);

		cursorX += button->getWidth() + spaceSize;
	}
}
