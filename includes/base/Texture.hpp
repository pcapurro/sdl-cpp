#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "Global.hpp"

class Texture
{
	private:
		SDL_Texture*	_texture = nullptr;

	public:
		Texture(void) = default;
		Texture(const Texture& original) = delete;
		Texture(Texture&& original) noexcept;

		Texture&	operator=(const Texture& original) noexcept = delete;
		Texture&	operator=(Texture&& original) noexcept;

		~Texture(void);

		SDL_Texture*	getTexture(void) const;

		void			loadImage(const char* path, SDL_Renderer* renderer);
		void			loadText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
};

#endif
