#ifndef TEXTTEXTURE_HPP
# define TEXTTEXTURE_HPP

# include "Global.hpp"

# include "Texture.hpp"
# include "Font.hpp"
# include "Color.hpp"

class TextTexture
{
	private:
		int					_width = 0;
		int					_height = 0;

		optional<Texture>	_texture;
		Color				_averageColor;

	public:
		TextTexture(const char* text, Font& font, SDL_Renderer* renderer);
		TextTexture(TextTexture&& original) = default;
		TextTexture(const TextTexture& original) = delete;

		TextTexture&		operator=(TextTexture&& original) = default;
		TextTexture&		operator=(const TextTexture& original) = delete;

		~TextTexture(void) = default;

		void				calculateAverageColor(SDL_Surface* surface) noexcept;

		int					getWidth(void) const noexcept;
		int					getHeight(void) const noexcept;

		SDL_Texture*		getTexture(void) const noexcept;
		Color				getAverageColor(void) const noexcept;
};

#endif
