#include "Text.hpp"

Text::Text(const Config& frameConfig, const string& text, const int size, const Color& color, \
    const string& fontPath, SDL_Renderer* renderer, const int maxWidth) : \
    Element(frameConfig), \
    _font(fontPath, size), \
    _text(text.c_str(), _font.getFont(), color.toSDL(), renderer, maxWidth)
{
    SDL_QueryTexture(_text.getTexture(), nullptr, \
        nullptr, &_realWidth, &_realHeight);
}

void    Text::render(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = _frameConfig.x, obj.y = _frameConfig.y;
    obj.w = _realWidth, obj.h = _realHeight;

    SDL_SetRenderDrawColor(renderer, _frameConfig.color.r, \
        _frameConfig.color.g, _frameConfig.color.b, _frameConfig.color.a);

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
