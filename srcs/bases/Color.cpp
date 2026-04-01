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

SDL_Color    Color::toSDLColor(const Color& color) noexcept
{
    SDL_Color   sdlColor;

    sdlColor.r = color.r;
    sdlColor.g = color.g;
    sdlColor.b = color.b;

    sdlColor.a = color.a;

    return sdlColor;
}

int  Color::getAverage(const Color& color) noexcept
{
    int     value = (color.r + color.g + color.b) / 3;

    return value;
}

void    Color::colorSurface(const Color& color, SDL_Surface* surface)
{
    int                 pixelsTotal = surface->w * surface->h;
    Uint32*             pixels = (Uint32*) surface->pixels;

    SDL_PixelFormat*    format = surface->format;

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    for (int i = 0; i < pixelsTotal; i++)
    {
        Uint8   pixelR, pixelG, pixelB, pixelA;

        SDL_GetRGBA(pixels[i], format, &pixelR, \
            &pixelG, &pixelB, &pixelA);

        if (pixelA == 0)
            continue;

        pixelR = color.r, pixelG = color.g, pixelB = color.b;

        pixels[i] = SDL_MapRGBA(format, pixelR, \
            pixelG, pixelB, pixelA);
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}
