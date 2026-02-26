#include "Image.hpp"

Image::Image(const Config& frameConfig, const char* path, \
    SDL_Renderer* renderer, Layout layout) : \
        Element(frameConfig), \
        _image(path, renderer), \
        _layout(layout) {}

void    Image::render(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

    obj.w = (_layout.widthPercent * _frameConfig.w) / 100;
    obj.h = (_layout.heightPercent * _frameConfig.h) / 100;

    if (_layout.scaleProp)
    {
        float   imageRatio = (float) _layout.originalWidth / (float) _layout.originalHeight;
        float   ratio = (float) obj.w / (float) obj.h;

        if (ratio > imageRatio)
            obj.w = obj.h * imageRatio;
        else
            obj.h = obj.w / imageRatio;
    }

    obj.x = _frameConfig.x + ((_layout.xPercent * _frameConfig.w) / 100);
    obj.y = _frameConfig.y + ((_layout.yPercent * _frameConfig.h) / 100);

    if (_layout.xCentered)
        obj.x -= obj.w / 2;
    if (_layout.yCentered)
        obj.y -= obj.h / 2;

    if (obj.x < 0)
        obj.x = 0;
    if (obj.y < 0)
        obj.y = 0;

    SDL_RenderCopy(renderer, _image.getTexture(), nullptr, &obj);
}
