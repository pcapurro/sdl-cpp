#include "Text.hpp"

void    Text::setText(const string& text, const int size, const string& fontPath, \
    const int x, const int y, const int w, const int h, \
	Color* color, SDL_Texture* texture, const int type, const bool highlight, \
    const int highlightCursor, const int normalCursor, const bool visibility)
{
    _text = text;
    _size = size;

    _fontPath = fontPath;

    setElement(x, y, w, h, color, texture, type, highlight, \
        highlightCursor, normalCursor, visibility);
}

void	Text::setMainText(const string& newText)
{
    _text = newText;
}

void	Text::setFontPath(const string& newFontPath)
{
    _fontPath = newFontPath;
}

void	Text::loadFont(void)
{
	_font = TTF_OpenFont(_fontPath.c_str(), 24);

	if (_font == NULL)
		throw std::runtime_error("SDL failed to load a font.");
}
