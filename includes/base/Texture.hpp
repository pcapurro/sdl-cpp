#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "Global.hpp"

# include "Color.hpp"

class Texture
{
	private:
		SDL_Texture*	_texture = nullptr;

		bool			_wrap = false;
		int				_linesNb = 0;
		int				_linesHeight = 0;

		Color			_averageColor;

	public:
		Texture(const Texture& original) = delete;
		Texture(Texture&& original) noexcept;

		Texture(const char* path, SDL_Renderer* renderer);

		Texture(const char* text, TTF_Font* font, SDL_Renderer* renderer, \
			const int maxWidth, const bool wrapping);

		Texture&		operator=(const Texture& original) = delete;
		Texture&		operator=(Texture&& original) noexcept;

		~Texture(void) noexcept;

		void			calculateAverageColor(SDL_Surface* surface) noexcept;

		bool			isWrapped(void) const noexcept;
		int				getLinesNb(void) const noexcept;
		int				getLinesHeight(void) const noexcept;

		SDL_Texture*	getTexture(void) const noexcept;
		Color			getAverageColor(void) const noexcept;
};

#endif
