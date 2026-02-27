#include "Element.hpp"

Element::Element(const Properties& properties) noexcept : \
	_properties(properties)
{
	_opacity = 255;
	_highlight = false;

	_visibility = true;
}

bool	Element::isAbove(const int x, const int y) const  noexcept
{
	if (x >= _properties.x && x <= _properties.x + _properties.w)
	{
		if (y >= _properties.y && y <= _properties.y + _properties.h)
			return true;
	}

	return false;
}

void	Element::setX(const int x) noexcept
{
	_properties.x = x;
}

void	Element::setY(const int y) noexcept
{
	_properties.y = y;
}

void	Element::setWidth(const int w) noexcept
{
	_properties.w = w;
}

void	Element::setHeight(const int h) noexcept
{
	_properties.h = h;
}

void	Element::setOpacity(const uint8_t opacity) noexcept
{
	_opacity = opacity;
}

void	Element::setHighlight(const bool highlight) noexcept
{
	_highlight = highlight;
}

void	Element::setVisibility(const bool visibility) noexcept
{
	_visibility = visibility;
}

int		Element::getX(void) const noexcept
{
	return _properties.x;
}

int		Element::getY(void) const noexcept
{
	return _properties.y;
}

int		Element::getWidth(void) const noexcept
{
	return _properties.w;
}

int		Element::getHeight(void) const noexcept
{
	return _properties.h;
}

uint8_t		Element::getOpacity(void) const noexcept
{
	return _opacity;
}

bool	Element::getHighlight(void) const noexcept
{
	return _highlight;
}

bool	Element::getVisibility(void) const noexcept
{
	return _visibility;
}
