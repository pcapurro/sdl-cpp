#include "YesNo.hpp"

YesNo::YesNo(const string& name, const int width, const int height, \
    const string& fontPath, const string& title, const bool titleLimit, \
	const string& text, const string& logoPath) : Window(name, width, height)
{
	SDL_Renderer*	renderer = getRenderer();
	Config			globalConfig;

	globalConfig.x = width * LIMIT_RATIO;

	if (title.size() > 0)
	{
		globalConfig.y = height * LIMIT_RATIO;

		int		titleSize = height * TITLE_RATIO;
		Text	titleText(globalConfig, title.c_str(), titleSize, BLACK, \
			fontPath, renderer, width - (width * LIMIT_RATIO));

		_texts.push_back(std::move(titleText));
		globalConfig.y += titleText.getHeight();

		if (titleLimit == true)
		{
			Config		limitConfig;

			limitConfig.x = width * LIMIT_RATIO;
			limitConfig.y = globalConfig.y + ((height * LIMIT_RATIO) / 2);

			limitConfig.w = width - ((width * LIMIT_RATIO) * 2);
			limitConfig.h = LIMIT_HEIGHT;

			limitConfig.color = BLACK;

			Element		limit(limitConfig);

			_elements.push_back(std::move(limit));
			globalConfig.y += LIMIT_HEIGHT * 2;
		}
	}

	globalConfig.y += height * LIMIT_RATIO;

	int		textSize = height * TEXT_RATIO;
	Text	mainText(globalConfig, text.c_str(), textSize, BLACK, \
	 	fontPath, renderer, width - (width * LIMIT_RATIO));

	_texts.push_back(std::move(mainText));

	(void) logoPath;
}

int     YesNo::routine(void)
{
    int     value = OK;

	draw();
	render();

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

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return END;

		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN \
			|| event.key.keysym.sym == SDLK_KP_ENTER))
			return ENTER;

		x = event.button.x;
		y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return OK;
		else
			setX(x), setY(y);

		// cout << event.button.x << " ; " << event.button.y << endl;
		// cout << x << " ; " << y << endl;

		reactEvent(&event);

		clear();
		draw();
		render();
	}

	return OK;
}

void     YesNo::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

    drawBackground(WHITE);

	if (renderer)
	{
		for (auto& element : _elements)
			element.draw(renderer);

		for (auto& text : _texts)
			text.draw(renderer);
	}
}

void     YesNo::reactEvent(SDL_Event* event)
{
    (void) event;
}
