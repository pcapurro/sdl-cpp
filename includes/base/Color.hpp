#ifndef COLOR_HPP
# define COLOR_HPP

# include "Global.hpp"

class Color
{
	public:
		unsigned char	r = 0;
		unsigned char	g = 0;
		unsigned char	b = 0;

		unsigned char	a = 255;

		SDL_Color		toSDL(void) const
			{ return {r, g, b, a}; }
};

#endif
