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

	_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
		_width, _height, 0);
	if (_mainWindow == nullptr)
		throw std::runtime_error("SDL failed to create a window: " + string(SDL_GetError()));

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (_mainRenderer == nullptr)
		throw std::runtime_error("SDL failed to create a renderer: " + string(SDL_GetError()));

	SDL_SetRenderDrawBlendMode(_mainRenderer, SDL_BLENDMODE_BLEND);

	_normalCursor.emplace(SDL_SYSTEM_CURSOR_ARROW);
	_textCursor.emplace(SDL_SYSTEM_CURSOR_IBEAM);

	_loadingCursor.emplace(SDL_SYSTEM_CURSOR_WAIT);
	_crossHairCursor.emplace(SDL_SYSTEM_CURSOR_CROSSHAIR);

	_interactCursor.emplace(SDL_SYSTEM_CURSOR_HAND);
	_waitCursor.emplace(SDL_SYSTEM_CURSOR_WAITARROW);

	_noCursor.emplace(SDL_SYSTEM_CURSOR_NO);
}

Window::~Window(void)
{
	if (_mainRenderer)
		SDL_DestroyRenderer(_mainRenderer);
	if (_mainWindow)
		SDL_DestroyWindow(_mainWindow);
}

// void	Window::blur(const uint8_t blurA)
// {
// 	SDL_Rect	obj;

// 	obj.w = _width, obj.h = _height;
// 	obj.x = 0, obj.y = 0;

// 	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, blurA);
// 	SDL_RenderFillRect(_mainRenderer, &obj);
// }

void	Window::display(void)
{
	SDL_RenderPresent(_mainRenderer);
}

void	Window::clear(void)
{
	SDL_RenderClear(_mainRenderer);
}

SDL_Renderer*	Window::getRenderer(void) const
{
	return _mainRenderer;
}

int	Window::getWidth(void) const
{
	return _width;
}

int	Window::getHeight(void) const
{
	return _height;
}

int	Window::getX(void) const
{
	return _x;
}

int	Window::getY(void) const
{
	return _y;
}

void	Window::setX(const int x)
{
	_x = x;
}

void	Window::setY(const int y)
{
	_y = y;
}

void	Window::setWriteColor(const Color& color)
{
	_writeColor = color;
}

void	Window::setBackgroundColor(const Color& color)
{
	_backgroundColor = color;
}

Color	Window::getWriteColor(void) const
{
	return _writeColor;
}

Color	Window::getBackgroundColor(void) const
{
	return _backgroundColor;
}

SDL_Cursor*		Window::getCursor(const int value) const
{
	if (value == SDL_SYSTEM_CURSOR_IBEAM)
		return _textCursor.value().getCursor();

	else if (value == SDL_SYSTEM_CURSOR_WAIT)
		return _loadingCursor.value().getCursor();

	else if (value == SDL_SYSTEM_CURSOR_CROSSHAIR)
		return _crossHairCursor.value().getCursor();

	else if (value == SDL_SYSTEM_CURSOR_HAND)
		return _interactCursor.value().getCursor();

	else if (value == SDL_SYSTEM_CURSOR_WAITARROW)
		return _waitCursor.value().getCursor();

	else if (value == SDL_SYSTEM_CURSOR_NO)
		return _noCursor.value().getCursor();

	else
		return _normalCursor.value().getCursor();

	return nullptr;
}

void	Window::setTitle(const std::string& title)
{
	SDL_SetWindowTitle(_mainWindow, title.c_str());
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
