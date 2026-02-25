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

	Config		globalConfig;

	globalConfig.x = width * LIMIT_RATIO;
	globalConfig.y = height * LIMIT_RATIO;

	if (logoPath.size() > 0)
		addLogo(globalConfig, logoPath, logoWidth, logoHeight);

	if (titleText.size() > 0)
	{
		addTitleText(globalConfig, titleText, fontPath, \
			!logoPath.empty(), logoWidth);

		if (titleLimit)
			addTitleLimit(globalConfig, !logoPath.empty(), logoWidth);
	}

	addText(globalConfig, text, fontPath);
}

void	YesNo::addLogo(Config& globalConfig, const string& logoPath, \
	const int logoWidth, const int logoHeight)
{
	SDL_Renderer*	renderer = getRenderer();
	Texture			logoImg(logoPath.c_str(), renderer);
	Config			logoConfig;

	logoConfig.x = getWidth() * LIMIT_RATIO;
	logoConfig.y = getHeight() * LIMIT_RATIO;

	logoConfig.w = logoWidth, logoConfig.h = logoHeight;
	logoConfig.type = IMAGE;

	Element			element(logoConfig);

	element.addRender(std::make_unique<Image>(logoPath.c_str(), renderer));
	_elements.push_back(std::move(element));

	globalConfig.x += (getWidth() * LIMIT_RATIO) + logoWidth;
}

void	YesNo::addTitleText(Config& globalConfig, const string& text, \
	const string& fontPath, const bool logo, const int logoWidth)
{
	SDL_Renderer*	renderer = getRenderer();
	int				titleSize = getHeight() * TITLE_RATIO;
	int				newWidth = getWidth() - (getWidth() * LIMIT_RATIO * 2);

	if (logo)
		newWidth -= (logoWidth * 2) - (getWidth() * LIMIT_RATIO);

	globalConfig.type = TEXT;

	Element				element(globalConfig);
	unique_ptr<Text>	ptr = std::make_unique<Text>(text.c_str(), titleSize, \
		getWriteColor(), fontPath, renderer, newWidth);

	globalConfig.y += ptr.get()->getRealHeight();

	element.addRender(std::move(ptr));
	_elements.push_back(std::move(element));
}

void	YesNo::addTitleLimit(Config& globalConfig, const bool logo, const int logoWidth)
{
	Config		limitConfig;

	limitConfig.x = globalConfig.x;
	limitConfig.y = globalConfig.y + (getHeight() * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);

	limitConfig.w = getWidth();

	if (!logo)
		limitConfig.w -= (getWidth() * LIMIT_RATIO * 2);
	else
		limitConfig.w -= (getWidth() * LIMIT_RATIO + (logoWidth * 2));

	limitConfig.h = LIMIT_HEIGHT;

	limitConfig.color = getWriteColor();
	limitConfig.type = ELEMENT;

	Element			element(limitConfig);

	element.addRender(std::make_unique<Form>());
	_elements.push_back(std::move(element));

	globalConfig.y += (getHeight() * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);
}

void	YesNo::addText(Config& globalConfig, const string& text, const string& fontPath)
{
	SDL_Renderer*	renderer = getRenderer();

	globalConfig.x = getWidth() * LIMIT_RATIO;
	globalConfig.y += getHeight() * LIMIT_RATIO;

	int		textSize = getHeight() * TEXT_RATIO;

	globalConfig.type = TEXT;

	Element			element(globalConfig);

	element.addRender(std::make_unique<Text>(text.c_str(), textSize, getWriteColor(), \
	 	fontPath, renderer, getWidth() - (getWidth() * LIMIT_RATIO)));

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
