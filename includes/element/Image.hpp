#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "Texture.hpp"

# include "Element.hpp"

class Image final : public Element
{
    private:
        Texture     _image;

    public:
        Image(void) = delete;

        Image(const Properties& properties, const char* path, \
            SDL_Renderer* renderer);

        Image(const int x, const int y, const int w, const int h, \
            const char* path, SDL_Renderer* renderer);

        void        render(SDL_Renderer* renderer);
};

#endif
