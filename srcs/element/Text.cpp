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

    if (!wrapping)
    {
        _lines.emplace_back(text.c_str(), \
            _font.getFont(), renderer);

        int width = 0;

        SDL_QueryTexture(_lines[0].getTexture(), nullptr, nullptr, \
            &width, nullptr);

        setWidth(width);
    }
    else
    {
        vector<string>  lines;

        createWrappedLines(text, maxWidth, lines);

        for (const auto& line : lines)
        {
            _lines.emplace_back(line.c_str(), \
                _font.getFont(), renderer);
        }

        setWidth(maxWidth);
    }

    _lineHeight = TTF_FontLineSkip(_font.getFont());
    setHeight(_lineHeight * _lines.size());

    for (const auto& line : _lines)
    {
        SDL_SetTextureBlendMode(line.getTexture(), \
            SDL_BLENDMODE_BLEND);
    }
}

void    Text::createWrappedLines(const string& text, const int maxWidth, \
    vector<string>& lines)
{
    string          line;

    int             cursorX = 0;
    int             cursorY = 0;

    for (size_t i = 0; i < text.size(); i++)
    {
        char    c = text[i];
    
        int     minX, minY, maxX, maxY;
        int     charWidth;

        if (TTF_GlyphMetrics(_font.getFont(), c, &minX, &maxX, \
            &minY, &maxY, &charWidth) != 0)
            continue;

        if (cursorX + charWidth > maxWidth)
        {
            cursorX = 0;
            cursorY += _lineHeight;

            lines.push_back(line);
            line.clear();
        }
        
        line += c;

        _charEnds.push_back({cursorX, cursorY});
        cursorX += charWidth;

        if (i + 1 >= text.size())
            _charEnds.push_back({cursorX, cursorY});
    }

    if (line.size() > 0)
        lines.push_back(line);
}

void    Text::render(SDL_Renderer* renderer)
{
    if (!getVisibility() || _lines.size() == 0)
        return;

    SDL_Rect    main;

	main.x = getX(), main.y = getY();

    for (auto& line : _lines)
    {
        SDL_QueryTexture(line.getTexture(), nullptr, nullptr, \
            &main.w, &main.h);

        SDL_SetTextureColorMod(line.getTexture(), _writeColor.r, \
            _writeColor.g, _writeColor.b);
        SDL_SetTextureAlphaMod(line.getTexture(), _writeColor.a);

        SDL_RenderCopy(renderer, line.getTexture(), \
            nullptr, &main);

        main.y += _lineHeight;
    }

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
    return _lines.size();
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

    if (_lines.size() > 0)
        _lines.clear();

    if (!wrapping)
    {
        _lines.emplace_back(text.c_str(), \
            _font.getFont(), renderer);

        int width = 0;

        SDL_QueryTexture(_lines[0].getTexture(), nullptr, nullptr, \
            &width, nullptr);

        setWidth(width);
    }
    else
    {
        vector<string>  lines;

        createWrappedLines(text, maxWidth, lines);

        for (const auto& line : lines)
        {
            _lines.emplace_back(line.c_str(), \
                _font.getFont(), renderer);
        }

        setWidth(maxWidth);
    }
    
    setHeight(_lineHeight * _lines.size());

    for (const auto& line : _lines)
    {
        SDL_SetTextureBlendMode(line.getTexture(), \
            SDL_BLENDMODE_BLEND);
    }
}
