#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth) : \
        Element({x, y, 0, 0}), \
        _writeColor(color),
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), renderer, maxWidth)
{
    SDL_SetTextureBlendMode(_text.getTexture(),\
        SDL_BLENDMODE_BLEND);

    SDL_QueryTexture(_text.getTexture(), nullptr, \
        nullptr, &_properties.w, &_properties.h);
}

Text::Text(const Properties& properties, const string& text, \
    const int size, const Color& color, const string& fontPath, \
    SDL_Renderer* renderer, const int maxWidth) : \
        Element(properties), \
        _writeColor(color),
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), renderer, maxWidth)
{
    SDL_SetTextureBlendMode(_text.getTexture(),\
        SDL_BLENDMODE_BLEND);
}

Text::Text(const int x, const int y, const int w, const int h, \
    const string& text, const int size, const Color& color, \
    const string& fontPath, SDL_Renderer* renderer, const int maxWidth) : \
        Element({x, y, w, h}), \
        _writeColor(color),
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), renderer, maxWidth)
{
    ;
}

void    Text::render(SDL_Renderer* renderer)
{
    if (!_visibility)
        return;

    SDL_Rect    main;

	main.x = _properties.x, main.y = _properties.y;
    main.w = _properties.w, main.h = _properties.h;

    SDL_SetTextureColorMod(_text.getTexture(), _writeColor.r, _writeColor.g, _writeColor.b);
    SDL_SetTextureAlphaMod(_text.getTexture(), _opacity);

    SDL_RenderCopy(renderer, _text.getTexture(), \
        nullptr, &main);

    if (_highlight)
    {
		int		colorValue = (_writeColor.r + _writeColor.g + _writeColor.b) / 3;

		if (colorValue < 128)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
		else
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);

        SDL_RenderFillRect(renderer, &main);
    }
}

void    Text::setColor(Color color) noexcept
{
    _writeColor = color;
}
