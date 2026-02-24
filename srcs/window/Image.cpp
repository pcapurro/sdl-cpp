#include "Image.hpp"

Image::Image(const char* path, SDL_Renderer* renderer) : _image(path, renderer) {}

void    Image::render(SDL_Renderer* renderer, const Config& config)
{
	SDL_Rect	obj;

	obj.x = config.x, obj.y = config.y;
	obj.w = config.w, obj.h = config.h;

	if (config.visibility == false)
        return;

    SDL_SetRenderDrawColor(renderer, config.color.r, \
        config.color.g, config.color.b, config.color.a);

    SDL_RenderCopy(renderer, _image.getTexture(), nullptr, &obj);
}
