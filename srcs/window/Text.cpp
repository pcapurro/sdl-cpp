#include "Text.hpp"

Text::Text(const string& text, const int size, const string& fontPath, \
    const int x, const int y, const int w, const int h, Color* color, SDL_Texture* texture, \
    const int type, const bool highlight, const int highlightCursor, const int normalCursor, \
    const bool visibility) : _font(fontPath)
{
    _text = text;
    _size = size;

    setElement(x, y, w, h, color, texture, type, highlight, \
        highlightCursor, normalCursor, visibility);
}

void    Text::setText(const string& text, const int size, const string& fontPath, \
    const int x, const int y, const int w, const int h, Color* color, SDL_Texture* texture, \
    const int type, const bool highlight, const int highlightCursor, const int normalCursor, \
    const bool visibility)
{
    _text = text;
    _size = size;

    if (fontPath != "")
        _font.setPath(fontPath);

    setElement(x, y, w, h, color, texture, type, highlight, \
        highlightCursor, normalCursor, visibility);
}

void	Text::setMainText(const string& newText)
{
    _text = newText;
}

void	Text::setFontPath(const string& newFontPath)
{
    _font.setPath(newFontPath);
}
