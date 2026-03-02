#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth) : \
        Element({x, y, 0, 0}), \
        _writeColor(color),
        _font(fontPath, size), \
        _text(text.c_str(), _font.getFont(), renderer, maxWidth)
{
    int     width = 0;
    int     height = 0;

    SDL_SetTextureBlendMode(_text.getTexture(),\
        SDL_BLENDMODE_BLEND);

    SDL_QueryTexture(_text.getTexture(), nullptr, \
        nullptr, &width, &height);

    setWidth(width);
    setHeight(height);
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
    if (!getVisibility())
        return;

    SDL_Rect    main;

	main.x = getX(), main.y = getY();
    main.w = getWidth(), main.h = getHeight();

    SDL_SetTextureColorMod(_text.getTexture(), _writeColor.r, _writeColor.g, _writeColor.b);
    SDL_SetTextureAlphaMod(_text.getTexture(), getOpacity());

    SDL_RenderCopy(renderer, _text.getTexture(), \
        nullptr, &main);

    if (isHighlighted())
    {
		Color	highlightColor;

		if (_writeColor.getAverage() < 128)
			highlightColor.setColor(255, 255, 255, HIGHLIGHT_OPACITY);
		else
			highlightColor.setColor(0, 0, 0, HIGHLIGHT_OPACITY);

		Render::renderHighlight(getX(), getY(), getWidth(), \
			getHeight(), highlightColor, renderer);
    }

    if (isSelected() && getSelectType() != NONE)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
    }
}

void    Text::setColor(Color color) noexcept
{
    _writeColor = color;
}
