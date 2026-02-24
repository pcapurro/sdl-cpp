#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "Texture.hpp"
# include "Render.hpp"

class Image final : public Render
{
    private:
        Texture     _image;

    public:
        Image(void) = delete;
        Image(const char* path, SDL_Renderer* renderer);

        void        render(SDL_Renderer* renderer, const Config& config);
};

#endif
