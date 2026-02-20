#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "Global.hpp"

class Texture
{
	private:
		SDL_Texture*	_texture = NULL;

	public:
		Texture(void) = default;

		~Texture(void);

		SDL_Texture*	getTexture(void) const;

		int				loadImage(const char* path, SDL_Renderer* renderer);
		int				loadText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);

		void			setTexture(const char* path, const char* text, TTF_Font* font, \
							SDL_Color color, SDL_Renderer* renderer);
};

#endif
