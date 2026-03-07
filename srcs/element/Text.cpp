#include "Text.hpp"

Text::Text(const int x, const int y, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, \
    const int maxWidth, const bool wrapping) : \
        Element({x, y, 0, 0}), \
        _textStr(text), \
        _writeColor(color), \
        _font(fontPath, size), \
        _maxWidth(maxWidth), \
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
        _maxWidth(maxWidth), \
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

int     Text::getLinesNb(void) const noexcept
{
    if (!_text.has_value())
        return 0;

    return _text.value().getLinesNb();
}

size_t  Text::getClosestCharIndex(const int x, const int y) const noexcept
{
    int     newY = 0;

    for (size_t i = 0; i < _charEnds.size(); i++)
    {
        if (y < _charEnds[i].y + _text.value().getLinesHeight() || i + 1 >= _charEnds.size())
            { newY = _charEnds[i].y; break; }
    }

    for (size_t i = 0; i < _charEnds.size(); i++)
    {
        if (_charEnds[i].y != newY \
            || _charEnds[i].x < x)
            continue;

        if (i == 0)
            return i;

        int     afterDistX = _charEnds[i].x - x;
        int     beforeDistX = x - _charEnds[i - 1].x;

        if (afterDistX > beforeDistX)
            return i - 1;
        else
            return i;
    }

    return _charEnds.size() - 1;
}

int     Text::getCharWidth(const int cursor) const noexcept
{
    if (cursor < 0 || cursor >= (int) _textStr.size())
        return -1;

    int     minX, maxX, minY, maxY;
    int     width;

    if (TTF_GlyphMetrics(_font.getFont(), _textStr[cursor], \
        &minX, &maxX, &minY, &maxY, &width) != 0)
        return -2;

    return width;
}

int     Text::getCharNumber(const int x, const int y) const noexcept
{
    for (size_t i = 0; i < _charEnds.size(); i++)
    {
        if (_charEnds[i].x == x && _charEnds[i].y == y)
            return i;
    }

    return 0;
}

Point   Text::getChar(const int cursor)
{
    if (cursor < 0 || cursor >= _charEnds.size())
        return {0, 0};

    return { _charEnds[cursor].x, _charEnds[cursor].y };
}

Point   Text::getClosestCharX(const int x, const int y) const noexcept
{
    size_t  closest = getClosestCharIndex(x, y);

    return { _charEnds[closest].x, _charEnds[closest].y };
}

Point   Text::getPreviousChar(const int x, const int y) const noexcept
{
    size_t  closest = getClosestCharIndex(x, y);

    if (closest == 0)
        return { _charEnds[closest].x, _charEnds[closest].y };

    return { _charEnds[closest - 1].x, _charEnds[closest - 1].y };
}

Point   Text::getNextChar(const int x, const int y) const noexcept
{
    size_t  closest = getClosestCharIndex(x, y);

    if (closest + 1 == _charEnds.size())
        return { _charEnds[closest].x, _charEnds[closest].y };

    return { _charEnds[closest + 1].x, _charEnds[closest + 1].y };
}

void    Text::calculateEndPoints(void)
{
    int     cursorX = getX();
    int     cursorY = getY();

    int     charWidth;
    int     minX, maxX, minY, maxY;

    _charEnds.clear();
    _charEnds.reserve(_textStr.size());

    _charEnds.push_back({cursorX, cursorY});

    for (const auto& c : _textStr)
    {
        if (TTF_GlyphMetrics(_font.getFont(), c, &minX, &maxX, \
            &minY, &maxY, &charWidth) != 0)
            continue;

        if (cursorX + charWidth > getX() + _maxWidth)
            cursorX = getX(), cursorY += _text.value().getLinesHeight();

        cursorX += charWidth;
        _charEnds.push_back({cursorX, cursorY});
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
