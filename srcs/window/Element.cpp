#include "Element.hpp"

bool	Element::isAbove(const int x, const int y) const
{
	if (x >= _properties.x && x <= _properties.x + _properties.w)
	{
		if (y >= _properties.y && y <= _properties.y + _properties.h)
			return true;
	}

	return false;
}

void	Element::setX(const int x)
{
	_properties.x = x;
}

void	Element::setY(const int y)
{
	_properties.y = y;
}

void	Element::setWidth(const int w)
{
	_properties.w = w;
}

void	Element::setHeight(const int h)
{
	_properties.h = h;
}

int		Element::getX(void) const
{
	return _properties.x;
}

int		Element::getY(void) const
{
	return _properties.y;
}

int		Element::getWidth(void) const
{
	return _properties.w;
}

int		Element::getHeight(void) const
{
	return _properties.h;
}
