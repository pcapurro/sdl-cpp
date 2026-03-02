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
    if (!getVisibility())
        return;

    SDL_Rect	main, center;

	main.x = getX(), main.y = getY();
	main.w = getWidth(), main.h = getHeight();

	center = main;

	if (_border && _borderThickness <= getWidth() \
		&& _borderThickness <= getHeight())
	{
		center.x = main.x + _borderThickness;
		center.y = main.y + _borderThickness;

		center.w = main.w - 2 * _borderThickness;
		center.h = main.h - 2 * _borderThickness;

		SDL_SetRenderDrawColor(renderer, _borderColor.r, \
			_borderColor.g, _borderColor.b, getOpacity());
		SDL_RenderFillRect(renderer, &main);

		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, \
			_color.b, getOpacity());
		SDL_RenderFillRect(renderer, &center);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, \
			_color.b, getOpacity());

		SDL_RenderFillRect(renderer, &main);
	}

	if (isHighlighted())
	{
		Color	highlightColor;

		if (_color.getAverage() < 128)
			highlightColor.setColor(255, 255, 255, HIGHLIGHT_OPACITY);
		else
			highlightColor.setColor(0, 0, 0, HIGHLIGHT_OPACITY);

		Render::renderHighlight(getX(), getY(), getWidth(), \
			getHeight(), highlightColor, renderer);
	}

    if (isSelected() && getSelectType() != NONE)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
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
