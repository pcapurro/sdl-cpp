#include "Texture.hpp"

Texture::Texture(SDL_Texture* texture)
{
	_texture = texture;
}

Texture::Texture(Texture&& original) noexcept
{
    _texture = original._texture;
	original._texture = nullptr;
}

Texture&    Texture::operator=(Texture&& original) noexcept
{
	if (this == &original)
		return *this;

	SDL_DestroyTexture(_texture);
	_texture = original._texture;

	original._texture = nullptr;

	return *this;
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
