#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth) : \
        Element({x, y, 0, 0}), \
        _font(fontPath, size), \
        _writeColor(color)
{
    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth);

    int     width = 0;
    int     height = 0;

    SDL_SetTextureBlendMode(_text.value().getTexture(),\
        SDL_BLENDMODE_BLEND);

    SDL_QueryTexture(_text.value().getTexture(), nullptr, \
        nullptr, &width, &height);

    setWidth(width);
    setHeight(height);

    _free = false;
}

Text::Text(const Properties& properties, const string& text, \
    const int size, const Color& color, const string& fontPath, \
    SDL_Renderer* renderer, const int maxWidth) : \
        Element(properties), \
        _font(fontPath, size), \
        _writeColor(color)
{    
    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth);

    SDL_SetTextureBlendMode(_text.value().getTexture(),\
        SDL_BLENDMODE_BLEND);

    _free = true;
}

void    Text::render(SDL_Renderer* renderer)
{
    if (!getVisibility())
        return;

    SDL_Rect    main;

	main.x = getX(), main.y = getY();
    main.w = getWidth(), main.h = getHeight();

    SDL_SetTextureColorMod(_text.value().getTexture(), _writeColor.r, _writeColor.g, _writeColor.b);
    SDL_SetTextureAlphaMod(_text.value().getTexture(), getOpacity());

    SDL_RenderCopy(renderer, _text.value().getTexture(), \
        nullptr, &main);

    if (isHighlightPossible() && isHighlighted())
    {
		Color	    highlightColor;
		uint8_t		opacity = HIGHLIGHT_OPACITY;

        if (isFocusPossible() && isFocused())
            opacity = FOCUS_OPACITY;

		if (_writeColor.getAverage() < 128)
			highlightColor.setColor(255, 255, 255, opacity);
		else
			highlightColor.setColor(0, 0, 0, opacity);

		Render::renderHighlight(getX(), getY(), getWidth(), \
			getHeight(), highlightColor, renderer);
    }

    if (isSelectPossible() && isSelected() && getSelectType() != NONE)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
    }
}

void    Text::setColor(Color color) noexcept
{
    _writeColor = color;
}

void    Text::update(const string& text, const int maxWidth, \
    SDL_Renderer* renderer) noexcept
{
    _text.reset();

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth);

    if (!_free)
    {
        int     width = 0;
        int     height = 0;

        SDL_QueryTexture(_text.value().getTexture(), nullptr, \
            nullptr, &width, &height);

        setWidth(width);
        setHeight(height);
    }
}
