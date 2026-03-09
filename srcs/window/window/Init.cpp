#include "Window.hpp"

Window::Window(const string& name, const int width, const int height) : \
	_width(width), \
	_height(height), \
	_name(name)
{
	if (_width < MIN_WINDOW_W)
		_width = MIN_WINDOW_W;

	if (_height < MIN_WINDOW_H)
		_height = MIN_WINDOW_H;

	_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, _width, _height, 0);
	if (!_mainWindow)
	{
		throw std::runtime_error("SDL failed to create a window: " \
			+ string(SDL_GetError()));
	}

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!_mainRenderer)
	{
		throw std::runtime_error("SDL failed to create a renderer: " \
			+ string(SDL_GetError()));
	}

	SDL_SetRenderDrawBlendMode(_mainRenderer, SDL_BLENDMODE_BLEND);

	_normalCursor.emplace(SDL_SYSTEM_CURSOR_ARROW);
	_textCursor.emplace(SDL_SYSTEM_CURSOR_IBEAM);

	_loadingCursor.emplace(SDL_SYSTEM_CURSOR_WAIT);
	_crossHairCursor.emplace(SDL_SYSTEM_CURSOR_CROSSHAIR);

	_interactCursor.emplace(SDL_SYSTEM_CURSOR_HAND);
	_waitCursor.emplace(SDL_SYSTEM_CURSOR_WAITARROW);

	_noCursor.emplace(SDL_SYSTEM_CURSOR_NO);
}
