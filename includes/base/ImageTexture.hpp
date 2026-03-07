#ifndef IMAGE_TEXTURE_HPP
# define IMAGE_TEXTURE_HPP

# include "Global.hpp"

# include "Color.hpp"

class ImageTexture
{
	private:
		SDL_Texture*	_texture = nullptr;

		Color			_averageColor;

	public:
		ImageTexture(const ImageTexture& original) = delete;
		ImageTexture(ImageTexture&& original) noexcept;

		ImageTexture(const char* path, SDL_Renderer* renderer);

		ImageTexture&		operator=(const ImageTexture& original) = delete;
		ImageTexture&		operator=(ImageTexture&& original) noexcept;

		~ImageTexture(void) noexcept;

		void			calculateAverageColor(SDL_Surface* surface) noexcept;

		SDL_Texture*	getTexture(void) const noexcept;
		Color			getAverageColor(void) const noexcept;
};

#endif
