#include "Image.hpp"

Image::Image(const char* path, SDL_Renderer* renderer) : _image(path, renderer) {}

void    Image::render(SDL_Renderer* renderer, const Config& frameConfig)
{
	SDL_Rect	obj;

	obj.x = frameConfig.x, obj.y = frameConfig.y;
	obj.w = frameConfig.w, obj.h = frameConfig.h;

    SDL_RenderCopy(renderer, _image.getTexture(), nullptr, &obj);
}
