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

	if (surface == nullptr)
		throw std::runtime_error("SDL failed to load a BMP path: " + string(SDL_GetError()));

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (_texture == nullptr)
		throw std::runtime_error("SDL failed to create a texture from a surface: " + string(SDL_GetError()));
}

Texture::Texture(const char* text, TTF_Font* font, SDL_Color color, \
	SDL_Renderer* renderer, const int maxWidth)
{
	SDL_Surface*	surface = nullptr;
	
	if (maxWidth > 0)
		surface = TTF_RenderText_Blended_Wrapped(font, text, color, maxWidth);
	else
		surface = TTF_RenderText_Blended(font, text, color);

	if (!surface)
		throw std::runtime_error("SDL failed to create a text from a surface: " + string(SDL_GetError()));

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!_texture)
		throw std::runtime_error("SDL failed to create a texture from a surface: " + string(SDL_GetError()));
}

Texture::~Texture(void) noexcept
{
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

SDL_Texture*	Texture::getTexture(void) const noexcept
{
	return _texture;
}
