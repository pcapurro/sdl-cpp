#include "YesNo.hpp"

YesNo::YesNo(const string& name, const int width, const int height, \
    const string& fontPath, const bool darkMode, const string& titleText, \
	const bool titleLimit, const string& text, const string& logoPath, \
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

	_elements.push_back(std::move(image));
}

void	YesNo::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.push_back(std::move(textElement));
}

void	YesNo::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	Properties		limitFrame;

	limitFrame.x = cursorX;
	limitFrame.y = cursorY;

	limitFrame.width = width;
	limitFrame.height = LIMIT_HEIGHT;

	auto	shapeElement = std::make_unique<Shape>(limitFrame, getWriteColor());

	_elements.push_back(std::move(shapeElement));
}

void	YesNo::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.push_back(std::move(textElement));
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

		reactEvent(&event, x, y);
	}
	else
		reactEvent(&event);

	return OK;
}

void	YesNo::refreshDisplay(void)
{
	clear();
	render();

	display();
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

void	YesNo::reactEvent(SDL_Event* event, \
	const int x, const int y)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		for (auto& element : _elements)
		{
			if (!element.get()->isAbove(x, y) || element.get()->isSelected())
				element.get()->setSelected(false);
			else
				element.get()->setSelected(true);
		}
	}

	if (event->type == SDL_MOUSEMOTION)
	{
		Image*	ptr = nullptr;

		for (auto& element : _elements)
		{
			ptr = dynamic_cast<Image*>(element.get());

			if (!ptr)
				continue;

			if (element.get()->isAbove(x, y) == true)
				element.get()->setHighlight(true);
			else
				element.get()->setHighlight(false);
		}
	}

	refreshDisplay();
}
