#include "Form.hpp"

void    Form::render(SDL_Renderer* renderer, const Config& frameConfig)
{
	if (frameConfig.visibility == false)
        return;

	SDL_Rect	obj;

	obj.x = frameConfig.x, obj.y = frameConfig.y;
	obj.w = frameConfig.w, obj.h = frameConfig.h;

	SDL_SetRenderDrawColor(renderer, frameConfig.color.r, \
		frameConfig.color.g, frameConfig.color.b, frameConfig.color.a);

	SDL_RenderFillRect(renderer, &obj);
}
