#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "ImageTexture.hpp"

# include "Element.hpp"

class Image final : public Element
{
    private:
        optional<ImageTexture>  _image;

    public:
        Image(void) = delete;

        Image(const int x, const int y, const int w, const int h, \
            const char* path, SDL_Renderer* renderer);

        void                    render(SDL_Renderer* renderer);
};

#endif
