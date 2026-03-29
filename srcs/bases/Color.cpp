#include "Color.hpp"

bool    Color::operator==(const Color& other) const
{
    if (r == other.r && g == other.g && b == other.b && a == other.a)
        return true;

    return false;
}

bool    Color::operator!=(const Color& other) const
{
    if (r != other.r || g != other.g || b != other.b || a != other.a)
        return true;

    return false;
}

SDL_Color   Color::toSDLColor(void) const noexcept
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

void    Color::setColor(const uint8_t r, const uint8_t g, \
    const uint8_t b, const uint8_t a) noexcept
{
    this->r = r;
    this->g = g;
    this->b = b;

    this->a = a;
}
