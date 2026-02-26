#include "Shape.hpp"

Shape::Shape(const Config& frameConfig) : Element(frameConfig)
{
	;
}

void    Shape::render(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = _frameConfig.x, obj.y = _frameConfig.y;
	obj.w = _frameConfig.w, obj.h = _frameConfig.h;

	SDL_SetRenderDrawColor(renderer, _frameConfig.color.r, \
		_frameConfig.color.g, _frameConfig.color.b, _frameConfig.color.a);

	SDL_RenderFillRect(renderer, &obj);
}
