#include "Ok.hpp"

Ok::Ok(const string& name, const int width, const int height, 
	const string& text, const string& fontPath) : Window(name, width, height)
{
	_text = text;
	_fontPath = fontPath;

	setX(0);
	setY(0);

	_state = 0;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

	loadFont();
}

void	Ok::generateElements(void)
{
	;
}

void	Ok::setText(const string& newText)
{
	_text = newText;
}

void	Ok::setFontPath(const string& newFontPath)
{
	_fontPath = newFontPath;

	loadFont();
}

void	Ok::loadFont(void)
{
	_font = TTF_OpenFont(_fontPath.c_str(), 24);

	if (_font == NULL)
		throw std::runtime_error("SDL failed to load a font.");
}

void	Ok::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

	drawBackground({0, 0, 0, 255});
	drawElements(_elements);

	(void) renderer;
}

void	Ok::reactEvent(SDL_Event* event)
{
	int			x = getX(), y = getY();
	Element*	element = NULL;

	for (unsigned int i = 0; i != _elements.size(); i++)
	{
		if (_elements.at(i).isAbove(x, y) == true)
			element = &_elements.at(i);
	}

	if (element == NULL)
		return ;
	else
	{
		if (event->type == SDL_MOUSEBUTTONDOWN)
			_state = 2;
	}
}

int	Ok::routine(void)
{
	int	value = 0;

	while (true)
	{
		value = waitForEvent();

		if (value == 2)
			break;
	}

	return value;
}

int	Ok::waitForEvent(void)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT || event.window.event == SDL_WINDOWEVENT_CLOSE \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_ENTER) \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (2);

		x = event.button.x;
		y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return (0);
		else
			setX(x), setY(y);

		// cout << event.button.x << " ; " << event.button.y << endl;
		// cout << x << " ; " << y << endl;

		reactEvent(&event);

		clear();
		draw();
		render();
	}

	return (_state);
}
