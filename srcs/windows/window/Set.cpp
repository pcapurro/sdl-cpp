#include "Window.hpp"

void	Window::setX(const int x) noexcept
{
	_x = x;
}

void	Window::setY(const int y) noexcept
{
	_y = y;
}

void	Window::setWriteColor(const Color& color) noexcept
{
	_writeColor = color;
}

void	Window::setBackgroundColor(const Color& color) noexcept
{
	_backgroundColor = color;
}

void	Window::setTitle(const std::string& title)
{
	SDL_SetWindowTitle(_mainWindow, title.c_str());
}
