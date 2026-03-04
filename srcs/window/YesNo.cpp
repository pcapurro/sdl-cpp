#include "YesNo.hpp"

YesNo::YesNo(const string& name, const int width, const int height, \
	const string& fontPath, const bool darkMode, const string& titleText, \
	const bool titleLimit, const string& text, const string& leftbuttonText, \
	const string& rightButtonText, const string& logoPath, \
	const int logoWidth, const int logoHeight) : Window(name, width, height)
{
	if (darkMode)
		setWriteColor(WHITE), setBackgroundColor(BLACK);
	else
		setWriteColor(BLACK), setBackgroundColor(WHITE);

	int		limitX = width * LIMIT_RATIO;
	int		limitY = height * LIMIT_RATIO;

	int		cursorX = limitX;
	int		cursorY = limitY;

	int		maxWidth = 0;

	_elements.reserve(6);

	if (logoPath.size() > 0)
		addLogo(cursorX, cursorY, logoPath, logoWidth, logoHeight);

	if (titleText.size() > 0)
	{
		if (_elements.size() > 0)
			cursorX += _elements.back().get()->getWidth() + limitX;

		maxWidth = width - cursorX - limitX;

		addTitleText(cursorX, cursorY, titleText, fontPath, maxWidth);

		cursorY += _elements.back().get()->getHeight() + limitY;

		if (titleLimit)
		{
			addTitleLimit(cursorX, cursorY, maxWidth);
			cursorY += _elements.back().get()->getHeight() + limitY;
		}

		if (logoPath.size() > 0)
		{
			int		logoBottomY = _elements.front()->getHeight() + limitY;

			cursorY = std::max(logoBottomY, cursorY);
		}
		
		cursorX = limitX;
	}

	maxWidth = width - (limitX * 2);

	addText(cursorX, cursorY, text, fontPath, maxWidth);

	cursorY += _elements.back().get()->getHeight() + limitY;

	addButtons(fontPath, leftbuttonText, rightButtonText);
}

void	YesNo::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
	const int logoWidth, const int logoHeight)
{
	Properties		logoProperties;

	logoProperties.x = cursorX;
	logoProperties.y = cursorY;

	logoProperties.width = logoWidth;
	logoProperties.height = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties, \
		logoPath.c_str(), getRenderer());

	_elements.emplace_back(std::move(image));
}

void	YesNo::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void	YesNo::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	Properties		limitFrame;

	limitFrame.x = cursorX;
	limitFrame.y = cursorY;

	limitFrame.width = width;
	limitFrame.height = LIMIT_HEIGHT;

	auto	shapeElement = std::make_unique<Shape>(limitFrame, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	YesNo::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void	YesNo::addButtons(const string& fontPath, \
	const string& leftButtonText, const string& rightButtonText)
{
	int				textSize = getHeight() * TEXT_RATIO;
	int				spaceSize = (getWidth() * LIMIT_RATIO);
	int				limitY = getHeight() * LIMIT_RATIO;

	auto leftButton = std::make_unique<TextButton>(Properties{0, 0, 50, 25}, \
						getBackgroundColor(), leftButtonText, textSize, getWriteColor(), fontPath, getRenderer());

	auto rightButton = std::make_unique<TextButton>(Properties{0, 0, 50, 25}, \
						getBackgroundColor(), rightButtonText, textSize, getWriteColor(), fontPath, getRenderer());

	TextButton*		leftElement = leftButton.get();
	TextButton*		rightElement = rightButton.get();

	int				totalWidth = leftElement->getWidth() + rightElement->getWidth() + spaceSize;
	int				centerX = (getWidth() / 2) - (totalWidth / 2);

	leftElement->setX(centerX);
	rightElement->setX(centerX + leftElement->getWidth() + spaceSize);

	leftElement->setY(getHeight() - limitY - leftElement->getHeight());
	rightElement->setY(getHeight() - limitY - rightElement->getHeight());

	leftElement->setSettings(false, NONE, true, \
		SDL_SYSTEM_CURSOR_HAND, true, true);

	rightElement->setSettings(false, NONE, true, \
		SDL_SYSTEM_CURSOR_HAND, true, true);

	_elements.emplace_back(std::move(leftButton));
	_elements.emplace_back(std::move(rightButton));
}

int     YesNo::routine(void)
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

int     YesNo::waitForEvent(void)
{
	int			value = OK;
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_WaitEvent(&event) == 0)
		throw std::runtime_error("SDL failed listening to events: " + string(SDL_GetError()));

	if (event.type == SDL_QUIT \
		|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		return END;

	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN \
		|| event.key.keysym.sym == SDLK_KP_ENTER))
		return ENTER;

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

		// cout << event.button.x << " ; " << event.button.y << endl;
		// cout << x << " ; " << y << endl;

		value = reactEvent(&event, x, y);
	}
	else
		value = reactEvent(&event);

	return value;
}

void	YesNo::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (renderer)
	{
		for (auto& element : _elements)
			element.get()->render(renderer);
	}
}

int		YesNo::reactButtonsEvent(SDL_Event* event, const int x, const int y)
{
	TextButton*		leftButton = dynamic_cast<TextButton*> \
		(_elements[_elements.size() - 2].get());

	TextButton*		rightButton = dynamic_cast<TextButton*> \
		(_elements.back().get());

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (leftButton->isAbove(x, y))
			leftButton->setFocus(true);
		else if (rightButton->isAbove(x, y))
			rightButton->setFocus(true);
	}

	if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (leftButton->isAbove(x, y) && leftButton->isFocused())
			return YES;
		else if (rightButton->isAbove(x, y) && rightButton->isFocused())
			return NO;
		else
		{
			if (leftButton->isFocused())
				leftButton->setFocus(false);
			if (rightButton->isFocused())
				rightButton->setFocus(false);
		}
	}

	return OK;
}

int		YesNo::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
	{
		bool	isAbove = false;

		for (auto& element : _elements)
		{
			if (element.get()->isAbove(x, y) == true)
			{
				element.get()->setHighlight(true);

				isAbove = true;

				element.get()->setHover(true);
				SDL_SetCursor(getCursor(element.get()->getHoverCursor()));
			}
			else
				element.get()->setHighlight(false), element.get()->setHover(false);
		}

		if (!isAbove)
			SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
	}

	value = reactButtonsEvent(event, x, y);

	refreshDisplay();

	return value;
}
