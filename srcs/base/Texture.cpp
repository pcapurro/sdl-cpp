#include "Texture.hpp"

Texture::~Texture(void)
{
	if (_texture != NULL && _texture != nullptr)
		SDL_DestroyTexture(_texture), _texture = nullptr;
}

SDL_Texture*	Texture::getTexture(void) const
{
	return (_texture);
}

void	Texture::setTexture(const char* path, const char* text, TTF_Font* font, \
	SDL_Color color, SDL_Renderer* renderer)
{
	if (path == NULL)
		loadText(text, font, color, renderer);
	else
		loadImage(path, renderer);
}

int		Texture::loadImage(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface*	surface = NULL;

	surface = SDL_LoadBMP(path);
	if (surface == NULL)
		return (1);
	else
	{
		if (_texture != NULL)
			SDL_DestroyTexture(_texture), _texture = NULL;

		_texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (_texture == NULL)
			return (1);
	}

	return (0);
}

int		Texture::loadText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
	SDL_Surface*	surface = NULL;

	surface = TTF_RenderText_Blended(font, text, color);
	if (surface == NULL)
		return (1);
	else
	{
		if (_texture != NULL)
			SDL_DestroyTexture(_texture), _texture = NULL;

		_texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (_texture == NULL)
			return (1);
	}

	return (0);
}
