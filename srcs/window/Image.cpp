#include "Image.hpp"

Image::Image(const Properties& properties, const char* path, \
    SDL_Renderer* renderer) : \
        Element(properties), \
        _image(path, renderer)
{
    SDL_SetTextureBlendMode(_image.getTexture(),\
        SDL_BLENDMODE_BLEND);
}

Image::Image(const int x, const int y, const int w, const int h, \
    const char* path, SDL_Renderer* renderer) : \
        Element({x, y, w, h}), \
        _image(path, renderer)
{
    SDL_SetTextureBlendMode(_image.getTexture(), \
        SDL_BLENDMODE_BLEND);
}

void    Image::render(SDL_Renderer* renderer)
{
    if (!_visibility)
        return;

    SDL_Rect    main;

    main.x = _properties.x, main.y = _properties.y;
    main.w = _properties.w, main.h = _properties.h;

    SDL_SetTextureAlphaMod(_image.getTexture(), _opacity);

    SDL_RenderCopy(renderer, _image.getTexture(), \
        nullptr, &main);

    if (_highlight)
    {
        SDL_Rect    highlight = main;
        Color       avgColor = _image.getAverageColor();
        int         colorValue = (avgColor.r + avgColor.g + avgColor.b) / 3;

		if (colorValue < 128)
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);

		SDL_RenderFillRect(renderer, &highlight);
    }
}
