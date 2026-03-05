#include "Shape.hpp"

Shape::Shape(const int x, const int y, const int w, const int h, \
    const Color& color, const bool border, \
    const int borderThickness, const Color& borderColor) : \
		Element({x, y, w, h}, {color.a, color, borderColor})
{
	_border = border;

	if (_border)
		_borderThickness = borderThickness, _borderColor = borderColor;
}

Shape::Shape(const Properties& properties, const Color& color, \
	const bool border, const int borderThickness, const Color& borderColor) : \
		Element(properties, {color.a, color, borderColor})
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
	Color		mainColor = getMainColor();

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

		SDL_SetRenderDrawColor(renderer, mainColor.r, mainColor.g, \
			mainColor.b, getOpacity());
		SDL_RenderFillRect(renderer, &center);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, mainColor.r, mainColor.g, \
			mainColor.b, getOpacity());

		SDL_RenderFillRect(renderer, &main);
	}

	if (isHighlightPossible() && isHighlighted())
	{
		Color		highlightColor;
		uint8_t		opacity = HIGHLIGHT_OPACITY;

        if (isFocusPossible() && isFocused())
            opacity = FOCUS_OPACITY;

		if (mainColor.getAverage() < 128)
			highlightColor.setColor(255, 255, 255, opacity);
		else
			highlightColor.setColor(0, 0, 0, opacity);

		Render::renderHighlight(getX(), getY(), getWidth(), \
			getHeight(), highlightColor, renderer);
	}

    if (isSelectPossible() && isSelected() && getSelectType() != NONE)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
    }
}

void	Shape::setBorderColor(Color color) noexcept
{
	_borderColor = color;
}

void	Shape::update(const int x, const int y, const int width, const int height, \
    const int borderThickness, SDL_Renderer* renderer)
{
	setX(x, renderer);
	setY(y, renderer);

	setWidth(width, renderer);
	setHeight(height, renderer);

	if (_border)
		_borderThickness = borderThickness;
}
