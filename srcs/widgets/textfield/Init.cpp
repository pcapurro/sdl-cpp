#include "TextField.hpp"

TextField::TextField(const Properties& properties, const Color& backColor, \
    const Color& frameColor, const string& fontPath, const Color& textColor, \
    const int maxChar, const bool wrapping) : \
        Element(properties), \
        _maxChar(maxChar), \
        _fontPath(fontPath), \
        _textColor(textColor), \
        _wrapping(wrapping)
{
    int     limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursorPos = 0;

    _cursor.emplace(Properties{properties.x, properties.y + limit, \
        CURSOR_WIDTH, properties.height - (limit * 2)}, frameColor);

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
}

TextField::TextField(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& frameColor, const string& fontPath, \
    const Color& textColor, const int maxChar, \
    const bool wrapping) : \
        Element({x, y, width, height}), \
        _maxChar(maxChar), \
        _fontPath(fontPath), \
        _textColor(textColor), \
        _wrapping(wrapping)
{
    Properties  properties = {x, y, width, height};
    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursor.emplace(Properties{properties.x, properties.y + limit, \
        CURSOR_WIDTH, properties.height - (limit * 2)}, frameColor);

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
}
