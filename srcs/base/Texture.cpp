#include "Texture.hpp"

Texture::Texture(Texture&& original) noexcept : \
	_texture(original._texture)
{
	original._texture = nullptr;
}

Texture&	Texture::operator=(Texture&& original) noexcept
{
	if (this == &original)
		return *this;

	SDL_DestroyTexture(_texture);
	_texture = original._texture;

	original._texture = nullptr;

	return *this;
}

Texture::Texture(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface*	surface = SDL_LoadBMP(path);

	if (!surface)
	{
		throw std::runtime_error("SDL failed to load a BMP path: " \
			+ string(SDL_GetError()));
	}

	calculateAverageColor(surface);

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!_texture)
	{
		throw std::runtime_error("SDL failed to create a texture from a surface: " \
			+ string(SDL_GetError()));
	}
}

Texture::Texture(const char* text, TTF_Font* font, \
	SDL_Renderer* renderer, const int maxWidth)
{
	SDL_Surface*	surface = nullptr;
	
	if (maxWidth > 0)
		surface = TTF_RenderText_Blended_Wrapped(font, text, WHITE, maxWidth);
	else
		surface = TTF_RenderText_Blended(font, text, WHITE);

	if (!surface)
	{
		throw std::runtime_error("SDL failed to create a text from a surface: " \
			+ string(SDL_GetError()));
	}

	calculateAverageColor(surface);

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!_texture)
	{
		throw std::runtime_error("SDL failed to create a texture from a surface: " \
			+ string(SDL_GetError()));
	}
}

Texture::~Texture(void) noexcept
{
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

void	Texture::calculateAverageColor(SDL_Surface* surface) noexcept
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

SDL_Texture*	Texture::getTexture(void) const noexcept
{
	return _texture;
}

Color		Texture::getAverageColor(void) const noexcept
{
	return _averageColor;
}
