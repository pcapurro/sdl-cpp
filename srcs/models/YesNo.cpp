#include "YesNo.hpp"

YesNo::YesNo(const string& name, const int width, const int height, \
    const string& fontPath, const bool darkMode, const string& titleText, \
	const bool titleLimit, const string& text, const string& logoPath, \
	const int logoWidth, const int logoHeight) : Window(name, width, height)
{
	SDL_Renderer*	renderer = getRenderer();
	Config			globalConfig;
	Color			writeColor;

	bool			logo = logoPath.size() > 0 ? true : false;
	bool			title = titleText.size() > 0 ? true : false;

	if (darkMode == true)
		writeColor = WHITE, setBackgroundColor(BLACK);
	else
		writeColor = BLACK, setBackgroundColor(WHITE);

	globalConfig.x = width * LIMIT_RATIO;
	globalConfig.y = height * LIMIT_RATIO;

	if (logo)
	{
		Texture		logoImg(logoPath.c_str(), renderer);
		Config		logoConfig;

		logoConfig.x = globalConfig.x, logoConfig.y = globalConfig.y;
		logoConfig.w = logoWidth, logoConfig.h = logoHeight;

		_elements.emplace_back(std::move(logoConfig));
		_elements.back().setTexture(logoImg.getTexture());

		logoImg.setTexture(nullptr);
		globalConfig.x += (width * LIMIT_RATIO) + logoWidth;
	}

	if (title)
	{
		int		titleSize = height * TITLE_RATIO;
		int		newWidth = width - (width * LIMIT_RATIO * 2);

		if (logo)
			newWidth -= (logoWidth * 2) - (width * LIMIT_RATIO);

		_texts.emplace_back(std::move(globalConfig), titleText.c_str(), \
			titleSize, writeColor, fontPath, renderer, newWidth);

		globalConfig.y += _texts.back().getHeight();

		if (titleLimit == true)
		{
			Config		limitConfig;

			limitConfig.x = globalConfig.x;
			limitConfig.y = globalConfig.y + (height * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);

			limitConfig.w = newWidth;
			limitConfig.h = LIMIT_HEIGHT;

			limitConfig.color = writeColor;

			_elements.emplace_back(std::move(limitConfig));
			globalConfig.y += (height * LIMIT_RATIO) + (LIMIT_HEIGHT * 2);
		}
	}

	globalConfig.x = width * LIMIT_RATIO;
	globalConfig.y += height * LIMIT_RATIO;

	int		textSize = height * TEXT_RATIO;

	_texts.emplace_back(std::move(globalConfig), text.c_str(), textSize, writeColor, \
	 	fontPath, renderer, width - (width * LIMIT_RATIO));
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

    drawBackground();

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
