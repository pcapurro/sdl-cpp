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

	Config		globalFrameConfig;

	globalFrameConfig.x = width * LIMIT_RATIO;
	globalFrameConfig.y = height * LIMIT_RATIO;

	if (logoPath.size() > 0)
		addLogo(globalFrameConfig, logoPath, logoWidth, logoHeight);

	if (titleText.size() > 0)
	{
		addTitleText(globalFrameConfig, titleText, fontPath, \
			!logoPath.empty(), logoWidth);

		if (titleLimit)
			addTitleLimit(globalFrameConfig, !logoPath.empty(), logoWidth);
	}

	addText(globalFrameConfig, text, fontPath);
}

void	YesNo::addLogo(Config& globalFrameConfig, const string& logoPath, \
	const int logoWidth, const int logoHeight)
{
	Layout			logoLayout;
	Config			logoFrameConfig;

	logoFrameConfig.x = getWidth() * LIMIT_RATIO;
	logoFrameConfig.y = getHeight() * LIMIT_RATIO;

	logoFrameConfig.w = logoWidth;
	logoFrameConfig.h = logoHeight;

	logoFrameConfig.type = IMAGE;

	logoLayout.widthPercent = 100;
	logoLayout.heightPercent = 100;

	logoLayout.xPercent = 50;
	logoLayout.yPercent = 50;

	logoLayout.xCentered = true;
	logoLayout.yCentered = true;

	Element			element(logoFrameConfig);

	element.addWidget(std::make_unique<Image>(logoPath.c_str(), getRenderer(), logoLayout));
	_elements.push_back(std::move(element));

	globalFrameConfig.x += (getWidth() * LIMIT_RATIO) + logoWidth;
}

void	YesNo::addTitleText(Config& globalFrameConfig, const string& text, \
	const string& fontPath, const bool logo, const int logoWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;
	int		newWidth = getWidth() - (getWidth() * LIMIT_RATIO * 2);

	if (logo)
		newWidth -= (logoWidth * 2) - (getWidth() * LIMIT_RATIO);

	globalFrameConfig.type = TEXT;

	Element				element(globalFrameConfig);
	unique_ptr<Text>	ptr = std::make_unique<Text>(text.c_str(), titleSize, \
		getWriteColor(), fontPath, getRenderer(), newWidth);

	globalFrameConfig.y += ptr.get()->getRealHeight();

	element.addWidget(std::move(ptr));
	_elements.push_back(std::move(element));
}

void	YesNo::addTitleLimit(Config& globalFrameConfig, const bool logo, const int logoWidth)
{
	Config		limitFrameConfig;

	limitFrameConfig.x = globalFrameConfig.x;
	limitFrameConfig.y = globalFrameConfig.y + (getHeight() * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);

	limitFrameConfig.w = getWidth();

	if (!logo)
		limitFrameConfig.w -= (getWidth() * LIMIT_RATIO * 2);
	else
		limitFrameConfig.w -= (getWidth() * LIMIT_RATIO + (logoWidth * 2));

	limitFrameConfig.h = LIMIT_HEIGHT;

	limitFrameConfig.color = getWriteColor();
	limitFrameConfig.type = ELEMENT;

	Element			element(limitFrameConfig);

	element.addWidget(std::make_unique<Form>());
	_elements.push_back(std::move(element));

	globalFrameConfig.y += (getHeight() * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);
}

void	YesNo::addText(Config& globalFrameConfig, const string& text, const string& fontPath)
{
	globalFrameConfig.x = getWidth() * LIMIT_RATIO;
	globalFrameConfig.y += getHeight() * LIMIT_RATIO;

	globalFrameConfig.type = TEXT;

	int			textSize = getHeight() * TEXT_RATIO;
	Element		element(globalFrameConfig);

	element.addWidget(std::make_unique<Text>(text.c_str(), textSize, getWriteColor(), \
	 	fontPath, getRenderer(), getWidth() - (getWidth() * LIMIT_RATIO)));

	_elements.push_back(std::move(element));
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
			element.render(renderer);
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
		for (auto& element : _elements)
		{
			if (element.isAbove(x, y) == true)
				{ display(); return; }
		}
	}
}
