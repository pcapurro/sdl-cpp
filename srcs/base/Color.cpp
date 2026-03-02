#include "Color.hpp"

SDL_Color   Color::toSDL(void) const noexcept
{
    SDL_Color   color;

    color.r = r;
    color.g = g;
    color.b = b;

    color.a = a;

    return color;
}

int     Color::getAverage(void) const noexcept
{
    int     value = (r + g + b) / 3;

    return value;
}

void    Color::setColor(const int r, const int g, const int b, const int a)
{
    this->r = r;
    this->g = g;
    this->b = b;

    this->a = a;
}
