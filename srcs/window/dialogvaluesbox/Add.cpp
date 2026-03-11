#include "DialogValuesBox.hpp"

void	DialogValuesBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
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

void	DialogValuesBox::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, fontPath, getWriteColor(), maxWidth, true, getRenderer());

	_elements.emplace_back(std::move(textElement));
}

void	DialogValuesBox::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	auto	shapeElement = std::make_unique<Shape>(cursorX, cursorY, width, \
		LIMIT_HEIGHT, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	DialogValuesBox::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, fontPath, getWriteColor(), maxWidth, true, getRenderer());

	_elements.emplace_back(std::move(textElement));
}

void	DialogValuesBox::addFieldsTitles(const string& fontPath)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;
	int				limitY = getHeight() * LIMIT_RATIO;

	SDL_Renderer*	renderer = getRenderer();

	auto 	downRightText = std::make_unique<Text>(getX() + limitX, 0, _titles[0], textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	downRightText->setY(getHeight() - (limitY * 2) - downRightText->getHeight());

	if (_titles.size() > 1)
	{
		auto 	upLeftText = std::make_unique<Text>(getX() + limitX, 0, _titles[1], textSize, \
			fontPath, getWriteColor(), 0, false, renderer);

		upLeftText->setY(downRightText->getY() - (limitY * 2) - upLeftText->getHeight());

		_elements.emplace_back(std::move(upLeftText));
	}

	_elements.emplace_back(std::move(downRightText));
}

void	DialogValuesBox::addFields(const string& fontPath, const int maxText)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;

	int				globalWidth = ((textSize * 5) / 10) * 10;
	int				globalHeight = ((textSize * 2) / 10) * 10;

	Text*			upText = dynamic_cast<Text*>(_elements[_elements.size() - 2].get());
	Text*			downText = dynamic_cast<Text*>(_elements.back().get());

	int				globalX = 0;

	if (_titles.size() > 1)
	{
		if (downText->getX() + downText->getWidth() > upText->getX() + upText->getWidth())
			globalX = downText->getX() + downText->getWidth();
		else
			globalX = upText->getX() + upText->getWidth();
	}
	else
		globalX = downText->getX() + downText->getWidth();

	SDL_Renderer*	renderer = getRenderer();

	_downField = std::make_unique<ValueField>(globalX + limitX, 0, \
		globalWidth, globalHeight, getBackgroundColor(), getWriteColor(), \
		fontPath, getWriteColor(), maxText);

	_downField->setY(downText->getY(), renderer);	
	_downField->setSettings(true, HIGHLIGHT_SELECT, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

	Color	color = BLUE;
	color.a = HIGHLIGHT_OPACITY;

	_downField->setSelectColor(color);

	if (_titles.size() > 1)
	{
		_upField = std::make_unique<ValueField>(globalX + limitX, 0, globalWidth, globalHeight, \
			getBackgroundColor(), getWriteColor(), fontPath, getWriteColor(), maxText);

		_upField->setY(upText->getY(), renderer);
		_upField->setSettings(true, HIGHLIGHT_SELECT, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

		_upField->setSelectColor(color);
	}
}

void	DialogValuesBox::addFieldsUnits(const string& fontPath)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;

	SDL_Renderer*	renderer = getRenderer();

	auto	rightDownText = std::make_unique<Text>(0, 0, _units[0], textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	rightDownText->setX(_downField->getX() + _downField->getWidth() + (limitX / 2));
	rightDownText->setY(_downField->getY());

	if (_upField)
	{
		auto	rightUpText = std::make_unique<Text>(0, 0, _units[1], textSize, \
			fontPath, getWriteColor(), 0, false, renderer);
		
		rightUpText->setX(_upField->getX() + _upField->getWidth() + (limitX / 2));
		rightUpText->setY(_upField->getY());

		_elements.emplace_back(std::move(rightUpText));
	}

	_elements.emplace_back(std::move(rightDownText));
}

void	DialogValuesBox::addFieldsErrors(const string& fontPath)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;

	SDL_Renderer*	renderer = getRenderer();

	_downError = std::make_unique<Text>(0, 0, "Default error", textSize, \
		fontPath, getWriteColor(), 0, false, renderer);

	Text*	downText = dynamic_cast<Text*>(_elements.back().get());

	_downError->setX(downText->getX() + downText->getWidth() + (limitX / 2));
	_downError->setY(downText->getY());

	Color	color = RED;

	_downError->setColor(color);
	_downError->setVisibility(false);

	if (_upField)
	{
		Text*	upText = dynamic_cast<Text*>(_elements[_elements.size() - 2].get());
		_upError = std::make_unique<Text>(0, 0, "Default error", textSize, \
			fontPath, getWriteColor(), 0, false, renderer);

		_upError->setX(upText->getX() + upText->getWidth() + (limitX / 2));
		_upError->setY(upText->getY());

		_upError->setColor(color);
		_upError->setVisibility(false);
	}
}

void	DialogValuesBox::addButton(const string& fontPath)
{
    int				textSize = getHeight() * TEXT_RATIO;
	int				limitX = getWidth() * LIMIT_RATIO;
	int				limitY = getHeight() * LIMIT_RATIO;

	int				globalWidth = ((textSize * 5) / 10) * 10;
	int				globalHeight = ((textSize * 2) / 10) * 10;

	SDL_Renderer*	renderer = getRenderer();

	_okButton = std::make_unique<TextButton>(0, 0, globalWidth, globalHeight, \
		getBackgroundColor(), "OK", textSize, getWriteColor(), fontPath, renderer);

	_okButton->setX(getWidth() - limitX - _okButton->getWidth(), renderer);
	_okButton->setY(getHeight() - limitY - _okButton->getHeight(), renderer);

	_okButton->setSettings(false, NONE, true, SDL_SYSTEM_CURSOR_HAND, true, true);
}
