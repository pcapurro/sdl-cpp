#include "Window.hpp"

Window::~Window(void)
{
	if (_mainRenderer)
		SDL_DestroyRenderer(_mainRenderer);

	if (_mainWindow)
		SDL_DestroyWindow(_mainWindow);
}
