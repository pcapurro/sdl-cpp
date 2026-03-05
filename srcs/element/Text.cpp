#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth) : \
        Element({x, y, 0, 0}), \
        _textStr(text), \
        _writeColor(color), \
        _font(fontPath, size)
{
    _free = false;

    if (text.size() <= 0)
        return;

    int     width = 0;
    int     height = 0;

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth);

    SDL_SetTextureBlendMode(_text.value().getTexture(),\
        SDL_BLENDMODE_BLEND);

    SDL_QueryTexture(_text.value().getTexture(), nullptr, \
        nullptr, &width, &height);

    setWidth(width, renderer);
    setHeight(height, renderer);
}

Text::Text(const Properties& properties, const string& text, \
    const int size, const Color& color, const string& fontPath, \
    SDL_Renderer* renderer, const int maxWidth) : \
        Element(properties), \
        _textStr(text), \
        _writeColor(color), \
        _font(fontPath, size)
{
    _free = true;

    if (text.size() <= 0)
        return;

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth);

    SDL_SetTextureBlendMode(_text.value().getTexture(),\
        SDL_BLENDMODE_BLEND);
}

void    Text::render(SDL_Renderer* renderer)
{
    if (!getVisibility() || !_text.has_value())
        return;

    SDL_Rect    main;

	main.x = getX(), main.y = getY();
    main.w = getWidth(), main.h = getHeight();

    SDL_SetTextureColorMod(_text.value().getTexture(), _writeColor.r, \
        _writeColor.g, _writeColor.b);
    SDL_SetTextureAlphaMod(_text.value().getTexture(), _writeColor.a);

    SDL_RenderCopy(renderer, _text.value().getTexture(), \
        nullptr, &main);

    if ((isHighlightPossible() && isHighlighted()) \
        || (isHoverPossible() && isHover()))
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

string  Text::getTextStr(void) const noexcept
{
    return _textStr;
}

void    Text::update(const string& text, const int maxWidth, \
    SDL_Renderer* renderer)
{
    _textStr = text;

    if (!_text.has_value())
        _text.reset();

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth);

    SDL_SetTextureBlendMode(_text.value().getTexture(),\
        SDL_BLENDMODE_BLEND);

    if (!_free)
    {
        int     width = 0;
        int     height = 0;

        SDL_QueryTexture(_text.value().getTexture(), nullptr, \
            nullptr, &width, &height);

        setWidth(width, renderer);
        setHeight(height, renderer);
    }
}
