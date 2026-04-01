#include "Window.hpp"

void	Window::setCursorX(const int x) noexcept
{
	_cursorX = x;
}

void	Window::setCursorY(const int y) noexcept
{
	_cursorY = y;
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
