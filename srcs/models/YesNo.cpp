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

	Properties		globalFrame;

	globalFrame.x = width * LIMIT_RATIO;
	globalFrame.y = height * LIMIT_RATIO;

	if (logoPath.size() > 0)
		addLogo(globalFrame, logoPath, logoWidth, logoHeight);

	if (titleText.size() > 0)
	{
		addTitleText(globalFrame, titleText, fontPath, \
			!logoPath.empty(), logoWidth);

		if (titleLimit)
			addTitleLimit(globalFrame, !logoPath.empty(), logoWidth);
	}

	addText(globalFrame, text, fontPath);
}

void	YesNo::addLogo(Properties& globalFrame, const string& logoPath, \
	const int logoWidth, const int logoHeight)
{
	Properties		logoProperties;

	logoProperties.x = getWidth() * LIMIT_RATIO;
	logoProperties.y = getHeight() * LIMIT_RATIO;

	logoProperties.w = logoWidth;
	logoProperties.h = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties, \
		logoPath.c_str(), getRenderer());

	_elements.push_back(std::move(image));

	globalFrame.x += (getWidth() * LIMIT_RATIO) + logoWidth;
}

void	YesNo::addTitleText(Properties& globalFrame, const string& text, \
	const string& fontPath, const bool logo, const int logoWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;
	int		newWidth = getWidth() - (getWidth() * LIMIT_RATIO * 2);

	if (logo)
		newWidth -= (logoWidth * 2) - (getWidth() * LIMIT_RATIO);

	unique_ptr<Text>	textElement = std::make_unique<Text>(globalFrame.x, globalFrame.y, \
		text.c_str(), titleSize, getWriteColor(), fontPath, getRenderer(), newWidth);

	globalFrame.y += textElement.get()->getHeight();

	_elements.push_back(std::move(textElement));
}

void	YesNo::addTitleLimit(Properties& globalFrame, const bool logo, const int logoWidth)
{
	Properties		limitFrame;

	limitFrame.x = globalFrame.x;
	limitFrame.y = globalFrame.y + (getHeight() * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);

	limitFrame.w = getWidth();

	if (!logo)
		limitFrame.w -= (getWidth() * LIMIT_RATIO * 2);
	else
		limitFrame.w -= (getWidth() * LIMIT_RATIO + (logoWidth * 2));

	limitFrame.h = LIMIT_HEIGHT;

	auto	shapeElement = std::make_unique<Shape>(limitFrame, getWriteColor());

	_elements.push_back(std::move(shapeElement));

	globalFrame.y += (getHeight() * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);
}

void	YesNo::addText(Properties& globalFrame, const string& text, const string& fontPath)
{
	globalFrame.x = getWidth() * LIMIT_RATIO;
	globalFrame.y += getHeight() * LIMIT_RATIO;

	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(globalFrame.x, globalFrame.y, text.c_str(), \
		textSize, getWriteColor(), fontPath, getRenderer(), getWidth() - (getWidth() * LIMIT_RATIO));

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
    if (event->type == SDL_KEYDOWN && event->type == SDL_KEYUP \
		&& event->button.button == SDLK_TAB)
	{
		;
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
