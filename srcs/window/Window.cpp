#include "Window.hpp"

Window::Window(const string& name, const int width, const int height) : \
	_width(width), \
	_height(height), \
	_name(name)
{
	_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
		_width, _height, 0);
	if (_mainWindow == nullptr)
		throw std::runtime_error("SDL failed to create a window: " + string(SDL_GetError()));

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (_mainRenderer == nullptr)
		throw std::runtime_error("SDL failed to create a renderer: " + string(SDL_GetError()));

	_normalCursor.emplace(Cursor(SDL_SYSTEM_CURSOR_ARROW));
	_interactCursor.emplace(Cursor(SDL_SYSTEM_CURSOR_HAND));
	_crossHairCursor.emplace(Cursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	_textCursor.emplace(Cursor(SDL_SYSTEM_CURSOR_IBEAM));
}

Window::~Window(void)
{
	if (_mainRenderer)
		SDL_DestroyRenderer(_mainRenderer);
	if (_mainWindow)
		SDL_DestroyWindow(_mainWindow);
}

void	Window::blur(const uint8_t blurA)
{
	SDL_Rect	obj;

	obj.w = _width, obj.h = _height;
	obj.x = 0, obj.y = 0;

	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, blurA);
	SDL_RenderFillRect(_mainRenderer, &obj);
}

void	Window::render(void)
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

SDL_Cursor*		Window::getCursor(const uint8_t value) const
{
	if (value == NM_CURSOR)
		return _normalCursor.value().getCursor();
	else if (value == INT_CURSOR)
		return _interactCursor.value().getCursor();
	else if (value == CROSS_CURSOR)
		return _crossHairCursor.value().getCursor();
	else if (value == TXT_CURSOR)
		return _textCursor.value().getCursor();

	return nullptr;
}

void	Window::setTitle(const std::string& title)
{
	SDL_SetWindowTitle(_mainWindow, title.c_str());
}

void	Window::drawBackground()
{
	SDL_Rect	obj;

	obj.x = 0, obj.y = 0;
	obj.w = _width, obj.h = _height;

	SDL_SetRenderDrawColor(_mainRenderer, _backgroundColor.r, \
		_backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
	SDL_RenderFillRect(_mainRenderer, &obj);
}
