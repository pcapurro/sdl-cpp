#ifndef SURFACE_HPP
# define SURFACE_HPP

# include "Global.hpp"

# include "Font.hpp"
# include "Color.hpp"

class Surface
{
    private:
        SDL_Surface*    _surface = nullptr;

    public:
        Surface(const char* bmpPath);
        Surface(Font& fontPath, const char* text, const Color& color);

        ~Surface(void);

        SDL_Surface*    getSurface(void) const noexcept;
};

#endif
