#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "Global.hpp"

class Texture
{
	private:
		SDL_Texture*	_texture = nullptr;

	public:
		Texture(const Texture& original) = delete;
		Texture(Texture&& original) noexcept;

		Texture(const char* path, SDL_Renderer* renderer);
		Texture(const char* text, TTF_Font* font, SDL_Color color, \
			SDL_Renderer* renderer, const int maxWidth);

		Texture&		operator=(const Texture& original) = delete;
		Texture&		operator=(Texture& original) noexcept;
		Texture&		operator=(Texture&& original) noexcept;

		~Texture(void) noexcept;

		SDL_Texture*	getTexture(void) const;
};

#endif
