#include "Window.hpp"

Window::Window(const string& name, const size_t width, const size_t height, \
	const bool visible) : \
		_width(width), \
		_height(height), \
		_name(name)
{
	_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, _width, _height, visible ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN);

	if (!_mainWindow)
	{
		throw std::runtime_error("SDL failed to create a window (" \
			+ string(SDL_GetError()) + ").");
	}

	_windowId = SDL_GetWindowID(_mainWindow);

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!_mainRenderer)
	{
		throw std::runtime_error("SDL failed to create a renderer (" \
			+ string(SDL_GetError()) + ").");
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
