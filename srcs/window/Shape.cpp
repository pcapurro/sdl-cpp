#include "Shape.hpp"

Shape::Shape(const int x, const int y, const int w, const int h, \
    const Color& color, const bool border, \
    const int borderThickness, const Color& borderColor) : \
		Element({x, y, w, h}), _color(color)
{
	setOpacity(_color.a);

	_border = border;

	if (_border)
		_borderThickness = borderThickness, _borderColor = borderColor;
}

Shape::Shape(const Properties& properties, const Color& color, \
	const bool border, const int borderThickness, const Color& borderColor) : \
		Element(properties), _color(color)
{
	_border = border;

	if (_border)
		_borderThickness = borderThickness, _borderColor = borderColor;
}

void    Shape::render(SDL_Renderer* renderer)
{
    if (!_visibility)
        return;

    SDL_Rect	main, center;

	main.x = _properties.x, main.y = _properties.y;
	main.w = _properties.w, main.h = _properties.h;

	center = main;

	if (_border && _borderThickness <= _properties.w \
		&& _borderThickness <= _properties.h)
	{
		center.x = main.x + _borderThickness;
		center.y = main.y + _borderThickness;

		center.w = main.w - 2 * _borderThickness;
		center.h = main.h - 2 * _borderThickness;

		SDL_SetRenderDrawColor(renderer, _borderColor.r, \
			_borderColor.g, _borderColor.b, _opacity);
		SDL_RenderFillRect(renderer, &main);

		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, \
			_color.b, _opacity);
		SDL_RenderFillRect(renderer, &center);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, \
			_color.b, _opacity);

		SDL_RenderFillRect(renderer, &main);
	}

	if (_highlight)
	{
		int		colorValue = (_color.r + _color.g + _color.b) / 3;

		if (colorValue < 128)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
		else
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);

		SDL_RenderFillRect(renderer, &center);
	}
}

void	Shape::setColor(Color color) noexcept
{
	_color = color;
}

void	Shape::setBorderColor(Color color) noexcept
{
	_borderColor = color;
}
