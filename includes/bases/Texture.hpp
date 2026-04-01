#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "Global.hpp"

# include "Surface.hpp"

class Texture
{
    private:
        SDL_Texture*    _texture = nullptr;

    public:
        Texture(SDL_Texture* texture);

		Texture(const Texture& original) = delete;
		Texture(Texture&& original) noexcept;

		Texture&		operator=(const Texture& original) = delete;
		Texture&		operator=(Texture&& original) noexcept;

		~Texture(void) noexcept;

		SDL_Texture*	getTexture(void) const noexcept;
};

#endif
