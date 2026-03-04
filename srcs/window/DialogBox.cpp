#include "DialogBox.hpp"

DialogBox::DialogBox(const string& name, const int width, const int height, \
	const string& fontPath, const bool darkMode, const string& titleText, \
	const bool titleLimit, const string& text, const vector<string>& buttonsTexts, \
	const string& logoPath, const int logoWidth, const int logoHeight, \
	const bool logoCentered) : \
		Window(name, width, height), \
		_tabCursor(0), \
		_textButtons(buttonsTexts)
{
	int		limitX = width * LIMIT_RATIO;
	int		limitY = height * LIMIT_RATIO;

	int		cursorX = limitX;
	int		cursorY = limitY;

	int		maxWidth = width - (limitX * 2);

	if (darkMode)
		setWriteColor(WHITE), setBackgroundColor(BLACK);
	else
		setWriteColor(BLACK), setBackgroundColor(WHITE);

	_elements.reserve(6);

	if (logoPath.size() > 0)
	{
		addLogo(cursorX, cursorY, logoPath, logoWidth, \
			logoHeight, logoCentered);

		if (titleText.size() == 0 || logoCentered)
			cursorY += _elements.back().get()->getHeight() + limitY;
	}

	if (titleText.size() > 0)
	{
		if (_elements.size() > 0 && !logoCentered)
			cursorX += _elements.back().get()->getWidth() + limitX;

		maxWidth = width - cursorX - limitX;

		addTitleText(cursorX, cursorY, titleText, fontPath, maxWidth);

		cursorY += _elements.back().get()->getHeight() + limitY;
	}

	if (titleLimit)
	{
		addTitleLimit(cursorX, cursorY, maxWidth);
		cursorY += _elements.back().get()->getHeight() + limitY;
	}

	if (logoPath.size() > 0)
	{
		int		logoBottomY = _elements.front()->getHeight() + limitY;

		cursorY = std::max(logoBottomY, cursorY);
		cursorY += limitY;
	}
	
	cursorX = limitX;

	maxWidth = width - (limitX * 2);

	addText(cursorX, cursorY, text, fontPath, maxWidth);

	cursorY += _elements.back().get()->getHeight() + limitY;

	if (buttonsTexts.size() > 0)
		addButtons(fontPath, buttonsTexts);
}

void	DialogBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool centered)
{
	Properties		logoProperties;

	if (!centered)
		logoProperties.x = cursorX;

	logoProperties.y = cursorY;

	logoProperties.width = logoWidth;
	logoProperties.height = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties, \
		logoPath.c_str(), getRenderer());

	if (centered)
		image.get()->setX(getWidth() / 2 - (image.get()->getWidth() / 2));

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
	Properties		limitFrame;

	limitFrame.x = cursorX;
	limitFrame.y = cursorY;

	limitFrame.width = width;
	limitFrame.height = LIMIT_HEIGHT;

	auto	shapeElement = std::make_unique<Shape>(limitFrame, getWriteColor());

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

	for (size_t i = 0; i < buttonsTexts.size() && i < 4; i++)
	{
		auto button = std::make_unique<TextButton>(Properties{0, 0, ((textSize * 5) / 10) * 10, \
			((textSize * 2) / 10) * 10}, getBackgroundColor(), buttonsTexts[i], textSize, \
			getWriteColor(), fontPath, getRenderer());

		button.get()->setY(getHeight() - limitY - button.get()->getHeight());
		button.get()->setSettings(false, NONE, true, SDL_SYSTEM_CURSOR_HAND, true, true);

		totalWidth += button.get()->getWidth();
		if (i + 1 < buttonsTexts.size() && i + 1 < 4)
			totalWidth += spaceSize;

		_buttons.emplace_back(std::move(button));
	}

	int		cursorX = (getWidth() / 2) - (totalWidth / 2);

	for (const auto& button : _buttons)
	{
		button->setX(cursorX);
		button->setY(getHeight() - limitY - \
			button->getHeight());

		button->setSettings(false, NONE, true, \
			SDL_SYSTEM_CURSOR_HAND, true, true);

		cursorX += button->getWidth() + spaceSize;
	}
}

int     DialogBox::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value != OK)
            return value;
    }

    return OK;
}

int     DialogBox::waitForEvent(void)
{
	int			value = OK;
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_WaitEvent(&event) == 0)
	{
		throw std::runtime_error("SDL failed listening to events: " + \
			string(SDL_GetError()));
	}

	if (event.type == SDL_QUIT \
		|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		return END;

	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN \
		|| event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.type == SDL_MOUSEMOTION)
			x = event.motion.x, y = event.motion.y;
		else if (event.type == SDL_MOUSEBUTTONDOWN \
			|| event.type == SDL_MOUSEBUTTONUP)
			x = event.button.x, y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return OK;
		else
			setX(x), setY(y);

		value = reactEvent(&event, x, y);
	}
	else
		value = reactEvent(&event);

	return value;
}

void	DialogBox::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (renderer)
	{
		for (auto& element : _elements)
			element.get()->render(renderer);

		for (auto& button : _buttons)
			button.get()->render(renderer);
	}
}

void	DialogBox::reactMouseMotion(const int x, const int y)
{
	bool	isAbove = false;

	for (auto& button : _buttons)
	{
		if (button.get()->isAbove(x, y) == true)
		{
			isAbove = true;

			button.get()->setHighlight(true);
			button.get()->setHover(true);

			SDL_SetCursor(getCursor(button.get()->getHoverCursor()));
		}
		else
			button.get()->setHighlight(false);
	}

	if (!isAbove)
		SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

int		DialogBox::reactMouseButtonUp(const int x, const int y)
{
	for (auto& button : _buttons)
	{
		if (button->isAbove(x, y) && button->isFocused())
		{
			for (size_t i = 0; i < _textButtons.size(); i++)
			{
				if (_textButtons[i] == button->getText())
					return i + 1;
			}
		}
		else
			button->setFocus(false);
	}

	return OK;
}

void	DialogBox::reactMouseButtonDown(const int x, const int y)
{
	for (auto& button : _buttons)
	{
		if (button->isAbove(x, y))
			button->setFocus(true);
	}
}

int		DialogBox::reactKeyButtonDown(const int key)
{
	if (key == SDLK_TAB)
	{
		_buttons[_tabCursor].get()->setHighlight(false);

		if (_tabCursor < _buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		_buttons[_tabCursor].get()->setHighlight(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
		return _tabCursor + 1;

	return OK;
}

int		DialogBox::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);

	else if (event->type == SDL_MOUSEBUTTONDOWN)
		reactMouseButtonDown(x, y);

	else if (event->type == SDL_MOUSEBUTTONUP)
		value = reactMouseButtonUp(x, y);

	else if (event->type == SDL_KEYDOWN)
		value = reactKeyButtonDown(event->key.keysym.sym);

	refreshDisplay();

	return value;
}
