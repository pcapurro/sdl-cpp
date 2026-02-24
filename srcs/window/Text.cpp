#include "Text.hpp"

Text::Text(const string& text, const int size, const Color& color, \
    const string& fontPath, SDL_Renderer* renderer, const int maxWidth) : \
    _font(fontPath, size), \
    _text(text.c_str(), _font.getFont(), color.toSDL(), renderer, maxWidth)
{
    SDL_QueryTexture(_text.getTexture(), nullptr, \
        nullptr, &_realWidth, &_realHeight);
}

void    Text::render(SDL_Renderer* renderer, const Config& config)
{
	SDL_Rect	obj;

	obj.x = config.x, obj.y = config.y;
    obj.w = _realWidth, obj.h = _realHeight;

	if (config.visibility == false)
        return;

    SDL_SetRenderDrawColor(renderer, config.color.r, \
        config.color.g, config.color.b, config.color.a);

    SDL_RenderCopy(renderer, _text.getTexture(), nullptr, &obj);
}

int     Text::getRealWidth(void) const
{
    return _realWidth;
}

int     Text::getRealHeight(void) const
{
    return _realHeight;
}
