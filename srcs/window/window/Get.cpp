#include "Window.hpp"

SDL_Renderer*	Window::getRenderer(void) const noexcept
{
	return _mainRenderer;
}

int	Window::getWidth(void) const noexcept
{
	return _width;
}

int	Window::getHeight(void) const noexcept
{
	return _height;
}

int	Window::getX(void) const noexcept
{
	return _x;
}

int	Window::getY(void) const noexcept
{
	return _y;
}

Color	Window::getWriteColor(void) const noexcept
{
	return _writeColor;
}

Color	Window::getBackgroundColor(void) const noexcept
{
	return _backgroundColor;
}

SDL_Cursor*		Window::getCursor(const int value) const noexcept
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
