#include "ImageTexture.hpp"

ImageTexture::ImageTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_Texture*	texture = nullptr;
	Surface			surface(path);

	calculateAverageColor(surface.getSurface());

	texture = SDL_CreateTextureFromSurface(renderer, surface.getSurface());

	if (!texture)
	{
		throw std::runtime_error("SDL failed to create a texture from a surface (" \
			+ string(SDL_GetError()) + ").");
	}

	_texture.emplace(texture);
}

ImageTexture::ImageTexture(const char* path, const Color& color, SDL_Renderer* renderer)
{
	SDL_Texture*	texture = nullptr;
	Surface			surface(path);

	if (color != Color::Invisible)
		Color::colorSurface(color, surface.getSurface());

	calculateAverageColor(surface.getSurface());

	texture = SDL_CreateTextureFromSurface(renderer, surface.getSurface());

	if (!texture)
	{
		throw std::runtime_error("SDL failed to create a texture from a surface (" \
			+ string(SDL_GetError()) + ").");
	}

	_texture.emplace(texture);
}

void	ImageTexture::calculateAverageColor(SDL_Surface* surface) noexcept
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

SDL_Texture*	ImageTexture::getTexture(void) const noexcept
{
	return _texture->getTexture();
}

Color		ImageTexture::getAverageColor(void) const noexcept
{
	return _averageColor;
}
