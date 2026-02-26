#include "Element.hpp"

bool	Element::isAbove(const int x, const int y) const
{
	if (x >= _frameConfig.x && x <= _frameConfig.x + _frameConfig.w)
	{
		if (y >= _frameConfig.y && y <= _frameConfig.y + _frameConfig.h)
			return true;
	}

	return false;
}

void	Element::setX(const int x)
{
	_frameConfig.x = x;
}

void	Element::setY(const int y)
{
	_frameConfig.y = y;
}

void	Element::setWidth(const int w)
{
	_frameConfig.w = w;
}

void	Element::setHeight(const int h)
{
	_frameConfig.h = h;
}

void	Element::setVisibility(const bool value)
{
	_frameConfig.visibility = value;
}

void	Element::setColor(const Color color)
{
	_frameConfig.color = color;
}

void	Element::setOpacity(const int opacity)
{
	_frameConfig.color.a = opacity;
}

Color	Element::getColor(void) const
{
	return _frameConfig.color;
}

int		Element::getType(void) const
{
	return _frameConfig.type;
}

int		Element::getHighlightCursor(void) const
{
	return _frameConfig.highlightCursor;
}

int		Element::getNormalCursor(void) const
{
	return _frameConfig.normalCursor;
}

int		Element::getX(void) const
{
	return _frameConfig.x;
}

int		Element::getY(void) const
{
	return _frameConfig.y;
}

int		Element::getWidth(void) const
{
	return _frameConfig.w;
}

int		Element::getHeight(void) const
{
	return _frameConfig.h;
}
