#include "Element.hpp"

void	Element::render(SDL_Renderer* renderer)
{
	if (_config.visibility == false)
		return;

	for (const auto& widget : _widgets)
	{
		if (widget)
			widget.get()->render(renderer, _config);
	}
}

bool	Element::isAbove(const int x, const int y) const
{
	if (x >= _config.x && x <= _config.x + _config.w)
	{
		if (y >= _config.y && y <= _config.y + _config.h)
			return true;
	}

	return false;
}

void	Element::addWidget(unique_ptr<Widget>&& widget)
{
	_widgets.push_back(std::move(widget));
}

void	Element::setX(const int x)
{
	_config.x = x;
}

void	Element::setY(const int y)
{
	_config.y = y;
}

void	Element::setWidth(const int w)
{
	_config.w = w;
}

void	Element::setHeight(const int h)
{
	_config.h = h;
}

void	Element::setVisibility(const bool value)
{
	_config.visibility = value;
}

void	Element::setColor(const Color color)
{
	_config.color = color;
}

void	Element::setOpacity(const int opacity)
{
	_config.color.a = opacity;
}

Color	Element::getColor(void) const
{
	return _config.color;
}

int		Element::getType(void) const
{
	return _config.type;
}

int		Element::getHighlightCursor(void) const
{
	return _config.highlightCursor;
}

int		Element::getNormalCursor(void) const
{
	return _config.normalCursor;
}

int		Element::getX(void) const
{
	return _config.x;
}

int		Element::getY(void) const
{
	return _config.y;
}

int		Element::getWidth(void) const
{
	return _config.w;
}

int		Element::getHeight(void) const
{
	return _config.h;
}
