#include "TextTexture.hpp"

TextTexture::TextTexture(const char* text, Font& font, \
	SDL_Renderer* renderer)
{
	SDL_Texture*	texture = nullptr;
	Surface			surface(font, text, Color::White);

	calculateAverageColor(surface.getSurface());

	texture = SDL_CreateTextureFromSurface(renderer, surface.getSurface());

	if (!texture)
	{
		throw std::runtime_error("SDL failed to create a texture from a surface (" \
			+ string(SDL_GetError()) + ").");
	}

	SDL_QueryTexture(texture, nullptr, nullptr, \
        &_width, &_height);

	_texture.emplace(texture);
}

void	TextTexture::calculateAverageColor(SDL_Surface* surface) noexcept
{
	Uint64	rSum = 0, gSum = 0, bSum = 0;
	int		count = 0;

	Uint32*	pixels = (Uint32*) surface->pixels;

	for (int i = 0; i < surface->h; i++)
	{
		for (int k = 0; k < surface->w; k++)
		{
			uint8_t	r, g, b, a;

			SDL_GetRGBA(pixels[i * surface->w + k], \
				surface->format, &r, &g, &b, &a);

			if (a == 0)
				continue;

			rSum += r, gSum += g, bSum += b;
			count++;
		}
	}

	if (count == 0)
		_averageColor = {0, 0, 0, 255};
	else
	{
		_averageColor.r = rSum / count;
		_averageColor.g = gSum / count;
		_averageColor.b = bSum / count;
	}
}

int		TextTexture::getWidth(void) const noexcept
{
	return _width;
}

int		TextTexture::getHeight(void) const noexcept
{
	return _height;
}

SDL_Texture*	TextTexture::getTexture(void) const noexcept
{
	return _texture->getTexture();
}

Color		TextTexture::getAverageColor(void) const noexcept
{
	return _averageColor;
}
