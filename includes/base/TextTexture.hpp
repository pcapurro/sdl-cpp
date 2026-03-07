#ifndef TEXTTEXTURE_HPP
# define TEXTTEXTURE_HPP

# include "Global.hpp"

# include "Color.hpp"

class TextTexture
{
	private:
		SDL_Texture*	_texture = nullptr;

		bool			_wrap = false;
		int				_linesNb = 0;
		int				_linesHeight = 0;

		Color			_averageColor;

	public:
		TextTexture(const TextTexture& original) = delete;
		TextTexture(TextTexture&& original) noexcept;

		TextTexture(const char* text, TTF_Font* font, SDL_Renderer* renderer, \
			const int maxWidth, const bool wrapping);

		TextTexture&		operator=(const TextTexture& original) = delete;
		TextTexture&		operator=(TextTexture&& original) noexcept;

		~TextTexture(void) noexcept;

		void			calculateAverageColor(SDL_Surface* surface) noexcept;

		bool			isWrapped(void) const noexcept;
		int				getLinesNb(void) const noexcept;
		int				getLinesHeight(void) const noexcept;

		SDL_Texture*	getTexture(void) const noexcept;
		Color			getAverageColor(void) const noexcept;
};

#endif
