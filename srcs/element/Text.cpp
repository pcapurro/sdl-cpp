#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth, const bool wrapping) : \
        Element({x, y, 0, 0}), \
        _textStr(text), \
        _writeColor(color), \
        _font(fontPath, size), \
        _wrapping(wrapping)
{
    _free = false;

    if (text.size() <= 0)
        return;

    int     width = 0;
    int     height = 0;

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth, wrapping);

    SDL_SetTextureBlendMode(_text.value().getTexture(),\
        SDL_BLENDMODE_BLEND);

    SDL_QueryTexture(_text.value().getTexture(), nullptr, \
        nullptr, &width, &height);

    setWidth(width, renderer);
    setHeight(height, renderer);
}

Text::Text(const Properties& properties, const string& text, \
    const int size, const Color& color, const string& fontPath, \
    SDL_Renderer* renderer, const int maxWidth, const bool wrapping) : \
        Element(properties), \
        _textStr(text), \
        _writeColor(color), \
        _font(fontPath, size), \
        _wrapping(wrapping)
{
    _free = true;

    if (text.size() <= 0)
        return;

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth, wrapping);

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

bool    Text::isWrapped(void) const noexcept
{
    return _wrapping;
}

int     Text::getClosestCharX(const int x) const noexcept
{
    for (size_t i = 0; i < _charEnds.size(); i++)
    {
        if (_charEnds[i] >= x)
        {
            if (i == 0)
                return _charEnds[i];

            int     afterDistX = _charEnds[i] - x;
            int     beforeDistX = x - _charEnds[i - 1];

            if (afterDistX > beforeDistX)
                return _charEnds[i - 1];
            else
                return _charEnds[i];
        }
    }

    return _charEnds.back();
}

void    Text::calculateEndPoints(void)
{
    int     cursorX = getX();
    int     charWidth;
    int     minX, maxX, minY, maxY;

    _charEnds.clear();
    _charEnds.reserve(_textStr.size());

    _charEnds.push_back(cursorX);

    for (const auto& c : _textStr)
    {
        if (TTF_GlyphMetrics(_font.getFont(), c, &minX, &maxX, \
            &minY, &maxY, &charWidth) != 0)
            continue;

        cursorX += charWidth;
        _charEnds.push_back(cursorX);
    }
}

void    Text::update(const string& text, const int maxWidth, \
    const bool wrapping, SDL_Renderer* renderer)
{
    if (!wrapping)
    {
        int width = 0;

        TTF_SizeText(_font.getFont(), text.c_str(), \
            &width, nullptr);

        if (width > maxWidth)
            return;
    }
    
    _textStr = text;

    if (!_text.has_value())
        _text.reset();

    _text.emplace(text.c_str(), _font.getFont(), \
        renderer, maxWidth, wrapping);

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

        calculateEndPoints();
    }
}
