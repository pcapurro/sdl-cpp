#include "Image.hpp"

Image::Image(const char* path, SDL_Renderer* renderer, Layout layout) : \
    Widget(IMAGE, layout), _image(path, renderer) {}

void    Image::render(SDL_Renderer* renderer, const Config& frameConfig)
{
	SDL_Rect	obj;
    Layout      layout = getLayout();

    obj.w = (layout.widthPercent * frameConfig.w) / 100;
    obj.h = (layout.heightPercent * frameConfig.h) / 100;

    if (layout.scaleProportionally)
    {
        float   imageRatio = (float) layout.originalWidth / (float) layout.originalHeight;
        float   ratio = (float) obj.w / (float) obj.h;

        if (ratio > imageRatio)
            obj.w = obj.h * imageRatio;
        else
            obj.h = obj.w / imageRatio;
    }

    obj.x = frameConfig.x + ((layout.xPercent * frameConfig.w) / 100);
    obj.y = frameConfig.y + ((layout.yPercent * frameConfig.h) / 100);

    if (layout.xCentered)
        obj.x -= obj.w / 2;
    if (layout.yCentered)
        obj.y -= obj.h / 2;

    if (obj.x < 0)
        obj.x = 0;
    if (obj.y < 0)
        obj.y = 0;

    SDL_RenderCopy(renderer, _image.getTexture(), nullptr, &obj);
}
