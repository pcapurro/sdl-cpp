#include "Window.hpp"

Window::Window(const std::string name, const int width, const int height)
{
	_width = width;
	_height = height;

	_name = name;

	_mainWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
		_width, _height, 0);
	if (_mainWindow == NULL)
		throw std::runtime_error("SDL failed.");

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (_mainRenderer == NULL)
		throw std::runtime_error("SDL failed.");

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	_crossHairCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	_textCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);

	if (_normalCursor == NULL || _interactCursor == NULL \
		|| _crossHairCursor == NULL || _textCursor == NULL)
		throw std::runtime_error("SDL failed.");
}

Window::~Window(void)
{
	if (_normalCursor != nullptr && _normalCursor != NULL)
		SDL_FreeCursor(_normalCursor);
	if (_interactCursor != nullptr && _interactCursor != NULL)
		SDL_FreeCursor(_interactCursor);
	if (_crossHairCursor != nullptr && _interactCursor != NULL)
		SDL_FreeCursor(_crossHairCursor);
	if (_textCursor != nullptr && _textCursor != NULL)
		SDL_FreeCursor(_crossHairCursor);

	if (_mainRenderer != nullptr && _mainRenderer != NULL)
		SDL_DestroyRenderer(_mainRenderer);
	if (_mainWindow != nullptr && _mainWindow != NULL)
		SDL_DestroyWindow(_mainWindow);
}

void	Window::blur(void)
{
	SDL_Rect	obj;

	obj.w = _width, obj.h = _height;
	obj.x = 0, obj.y = 0;

	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 125);
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
	return (_mainRenderer);
}

int	Window::getWidth(void) const
{
	return (_width);
}

int	Window::getHeight(void) const
{
	return (_height);
}

int	Window::getX(void) const
{
	return (_x);
}

int	Window::getY(void) const
{
	return (_y);
}

void	Window::setX(const int x)
{
	_x = x;
}

void	Window::setY(const int y)
{
	_y = y;
}

SDL_Cursor*		Window::getCursor(const int value) const
{
	if (value == 0)
		return (_normalCursor);
	if (value == 1)
		return (_interactCursor);
	if (value == 2)
		return (_crossHairCursor);
	if (value == 3)
		return (_textCursor);

	return (nullptr);
}

void	Window::drawBackground(Color color)
{
	SDL_Rect	obj;

	obj.x = 0, obj.y = 0;
	obj.w = _width, obj.h = _height;

	SDL_SetRenderDrawColor(_mainRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(_mainRenderer, &obj);
}

void	Window::drawElements(std::vector<Element>* elements)
{
	for (unsigned int i = 0; i != elements->size(); i++)
		elements->at(i).draw(_mainRenderer);
}
