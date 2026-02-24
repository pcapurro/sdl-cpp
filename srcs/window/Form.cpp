#include "Form.hpp"

void    Form::render(SDL_Renderer* renderer, const Config& config)
{
	if (config.visibility == false)
        return;

	SDL_Rect	obj;

	obj.x = config.x, obj.y = config.y;
	obj.w = config.w, obj.h = config.h;

	SDL_SetRenderDrawColor(renderer, config.color.r, \
		config.color.g, config.color.b, config.color.a);

	SDL_RenderFillRect(renderer, &obj);
}
