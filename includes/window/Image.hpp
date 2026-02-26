#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "Texture.hpp"
# include "Layout.hpp"
# include "Element.hpp"

class Image final : public Element
{
    private:
        Texture     _image;
        Layout      _layout;

    public:
        Image(void) = delete;
        Image(const Config& frameConfig, const char* path, \
            SDL_Renderer* renderer, Layout layout = Layout{});

        void        render(SDL_Renderer* SDL_RendererFlip);
};

#endif
