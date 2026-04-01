#include "Surface.hpp"

Surface::Surface(const char* bmpPath)
{
    _surface = SDL_LoadBMP(bmpPath);

	if (!_surface)
	{
		throw std::runtime_error("SDL failed to load a BMP path (" \
			+ string(SDL_GetError()) + ").\nPath: '" + bmpPath + "'");
	}
}

Surface::Surface(Font& fontPath, const char* text, const Color& color)
{
    TTF_Font*   font = fontPath.getFont();

    if (!font)
        return;

    _surface = TTF_RenderText_Blended(fontPath.getFont(), \
        text, color.toSDLColor());

	if (!_surface)
	{
		throw std::runtime_error("SDL failed to create a text surface (" \
			+ string(SDL_GetError()) + ").\nText: '" + text + "'");
	}
}

Surface::~Surface(void)
{
    if (_surface)
        SDL_FreeSurface(_surface);
}

SDL_Surface*    Surface::getSurface(void) const noexcept
{
    return _surface;
}
