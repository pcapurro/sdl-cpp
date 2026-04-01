#ifndef IMAGE_TEXTURE_HPP
# define IMAGE_TEXTURE_HPP

# include "Global.hpp"

# include "Texture.hpp"
# include "Color.hpp"

class ImageTexture
{
	private:
		optional<Texture>	_texture;

		Color				_averageColor;

		void				calculateAverageColor(SDL_Surface* surface) noexcept;

	public:
		ImageTexture(const char* path, SDL_Renderer* renderer);
		ImageTexture(const char* path, const Color& color, SDL_Renderer* renderer);

		ImageTexture(ImageTexture&& original) = default;
		ImageTexture(const ImageTexture& original) = delete;

		ImageTexture&		operator=(ImageTexture&& original) = default;
		ImageTexture&		operator=(const ImageTexture& original) = delete;

		~ImageTexture(void) = default;

		SDL_Texture*		getTexture(void) const noexcept;
		Color				getAverageColor(void) const noexcept;
};

#endif
