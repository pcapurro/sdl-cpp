#ifndef COLOR_HPP
# define COLOR_HPP

# include "Global.hpp"

class Color
{
	public:
		uint8_t			r = 0;
		uint8_t			g = 0;
		uint8_t			b = 0;

		uint8_t			a = 255;

		SDL_Color		toSDL(void) const noexcept;
		int				getAverage(void) const noexcept;
};

#endif
