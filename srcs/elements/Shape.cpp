#include "Shape.hpp"

Shape::Shape(const int x, const int y, const int w, const int h, \
    const Color& color, const bool border, \
    const int borderThickness, const Color& borderColor) : \
		Element({x, y, w, h}, {color, borderColor})
{
	_border = border;

	if (_border)
	{
		_borderThickness = borderThickness;
		_borderColor = borderColor;
	}
}

void    Shape::render(SDL_Renderer* renderer)
{	
    if (!isVisible())
        return;

    SDL_Rect	main, center;
	Color		mainColor = getMainColor();

	main.x = getX(), main.y = getY();
	main.w = getWidth(), main.h = getHeight();

	center = main;

	SDL_SetRenderDrawColor(renderer, mainColor.r, mainColor.g, \
		mainColor.b, mainColor.a);

	SDL_RenderFillRect(renderer, &main);

	if (_border && getWidth() > 0 && getHeight() > 0)
	{
		SDL_Rect    shapes[4];

		SDL_SetRenderDrawColor(renderer, _borderColor.r, _borderColor.g, \
	    	_borderColor.b, _borderColor.a);

		shapes[0] = {main.x, main.y, _borderThickness, main.h};
		shapes[1] = {main.x + main.w - _borderThickness, main.y, _borderThickness, main.h};

		shapes[2] = {main.x + _borderThickness, main.y, main.w - 2 * _borderThickness, _borderThickness};
		shapes[3] = {main.x + _borderThickness, main.y + main.h - _borderThickness, \
			main.w - 2 * _borderThickness, _borderThickness};

		for (const auto& shape : shapes)
			SDL_RenderFillRect(renderer, &shape);
	}

	if ((isHighlightPossible() && isHighlighted()) \
        || (isHoverPossible() && isHover()))
	{
		Color		highlightColor;
		uint8_t		opacity = Render::HiglihtOpacity;

        if (isFocusPossible() && isFocused())
            opacity = Render::FocusOpacity;

		if (mainColor.getAverage() < 128)
			highlightColor.setColor(255, 255, 255, opacity);
		else
			highlightColor.setColor(0, 0, 0, opacity);

		Render::renderHighlight(getX(), getY(), getWidth(), \
			getHeight(), highlightColor, renderer);
	}

    if (isSelectPossible() && isSelected() && getSelectType() != State::None)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
    }
}

int		Shape::getBorderThickness(void) const noexcept
{
	return _borderThickness;
}

Color	Shape::getBorderColor(void) const noexcept
{
	return _borderColor;
}

void	Shape::setBorderThickness(const int thickness) noexcept
{
	_borderThickness = thickness;
}

void	Shape::setBorderColor(Color& color) noexcept
{
	_borderColor = color;
}
