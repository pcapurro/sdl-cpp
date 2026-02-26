#include "Shape.hpp"

Shape::Shape(const int x, const int y, const int w, const int h, \
    const Color& color, const bool border, \
    const int borderThickness, const Color& borderColor) : \
		Element({x, y, w, h}), _color(color)
{
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
    SDL_Rect	main;

	main.x = _properties.x, main.y = _properties.y;
	main.w = _properties.w, main.h = _properties.h;

	if (_border)
	{
		SDL_SetRenderDrawColor(renderer, _borderColor.r, _borderColor.g, \
			_borderColor.b, _borderColor.a);
		
		SDL_RenderFillRect(renderer, &main);

		main.x += _borderThickness / 2, main.y += _borderThickness / 2;
		main.w -= _borderThickness, main.h -= _borderThickness;

		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, \
			_color.b, _color.a);

		SDL_RenderFillRect(renderer, &main);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, \
			_color.b, _color.a);

		SDL_RenderFillRect(renderer, &main);
	}
}
