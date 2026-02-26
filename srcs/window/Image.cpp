#include "Image.hpp"

Image::Image(const Properties& properties, const char* path, \
    SDL_Renderer* renderer) : \
        Element(properties), \
        _image(path, renderer)
{
    ;
}

Image::Image(const int x, const int y, const int w, const int h, \
    const char* path, SDL_Renderer* renderer) : \
        Element({x, y, w, h}), \
        _image(path, renderer)
{
    ;
}

void    Image::render(SDL_Renderer* renderer)
{
    SDL_Rect                main;

    main.x = _properties.x;
    main.y = _properties.y;

    main.w = _properties.w;
    main.h = _properties.h;

    SDL_RenderCopy(renderer, _image.getTexture(), nullptr, &main);
}
