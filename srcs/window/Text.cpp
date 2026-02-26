#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth) : \
        Element({x, y, 0, 0}), \
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), color.toSDL(), renderer, maxWidth)
{
    SDL_QueryTexture(_text.getTexture(), nullptr, \
        nullptr, &_properties.w, &_properties.h);
}

Text::Text(const Properties& properties, const string& text, \
    const int size, const Color& color, const string& fontPath, \
    SDL_Renderer* renderer, const int maxWidth) : \
        Element(properties), \
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), color.toSDL(), renderer, maxWidth)
{
    ;
}

Text::Text(const int x, const int y, const int w, const int h, \
    const string& text, const int size, const Color& color, \
    const string& fontPath, SDL_Renderer* renderer, const int maxWidth) : \
        Element({x, y, w, h}), \
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), color.toSDL(), renderer, maxWidth)
{
    ;
}

void    Text::render(SDL_Renderer* renderer)
{
    SDL_Rect    main;

	main.x = _properties.x, main.y = _properties.y;
    main.w = _properties.w, main.h = _properties.h;

    SDL_SetRenderDrawColor(renderer, _writeColor.r, _writeColor.g, \
        _writeColor.b, _writeColor.a);

    SDL_RenderCopy(renderer, _text.getTexture(), \
        nullptr, &main);
}
