#include "Window.hpp"

void	Window::display(void)
{
	SDL_RenderPresent(_mainRenderer);
}

void	Window::clear(void)
{
	SDL_RenderClear(_mainRenderer);
}

void	Window::refreshDisplay(void)
{
	clear();
	render();

	display();
}

void	Window::renderBackground()
{
	SDL_Rect	obj;

	obj.x = 0, obj.y = 0;
	obj.w = _width, obj.h = _height;

	SDL_SetRenderDrawColor(_mainRenderer, _backgroundColor.r, \
		_backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
	SDL_RenderFillRect(_mainRenderer, &obj);
}
