#include "YesNo.hpp"

YesNo::YesNo(const string& name, const int width, const int height, \
	const string& text, const string& title, const string& fontPath) : Window(name, width, height)
{
	_text.setText(text, 24, fontPath, 0, 0, 50, 20);
	_title.setText(title, 24, fontPath, 0, 0, 50, 20);

	_text.loadFont();
	_title.loadFont();

	setX(0);
	setY(0);

	_state = 0;

	SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);
}

void	YesNo::generateElements(void)
{
	;
}

void	YesNo::setText(const string& newText)
{
	_text.setMainText(newText);
}

void	YesNo::setFontPath(const string& newFontPath)
{
	_text.setFontPath(newFontPath);
	_text.loadFont();
}

void	YesNo::draw(void)
{
	SDL_Renderer*	renderer = getRenderer();

	drawBackground({42, 42, 42, 255});

	vector<Element>	elements;
	elements.push_back(_title);
	elements.push_back(_text);

	drawElements(elements);

	(void) renderer;
}

int	YesNo::routine(void)
{
	int	value = 0;

	while (true)
	{
		value = waitForEvent();

		if (value != 0)
			break;
	}

	return value;
}

void	YesNo::reactEvent(SDL_Event* event)
{
	(void) event;

	/*

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
		int type = element->getType();

		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if (type == YES)
				_state = 2;
			if (type == NO)
				_state = 1;
		}
	}

	*/
}

int	YesNo::waitForEvent(void)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_PollEvent(&event) == true)
	{
		if (event.type == SDL_QUIT \
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (1);

		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN \
			|| event.key.keysym.sym == SDLK_KP_ENTER))
			return (2);

		x = event.button.x;
		y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return (0);
		else
			setX(x), setY(y);

		// cout << event.button.x << " ; " << event.button.y << endl;
		// cout << x << " ; " << y << endl;

		// reactEvent(&event);

		clear();
		draw();
		render();
	}

	return (_state);
}
