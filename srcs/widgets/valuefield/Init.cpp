#include "ValueField.hpp"

ValueField::ValueField(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& frameColor, const string& fontPath, \
    const Color& textColor, const int maxChar, const int minValue, const int maxValue) : \
        Element({x, y, width, height}), \
        _fontPath(fontPath), \
        _textColor(textColor), \
        _maxChar(maxChar), \
        _minValue(minValue), \
        _maxValue(maxValue)
{
    Properties  properties = {x, y, width, height};
    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursor.emplace(properties.x, properties.y + limit, \
        CURSOR_WIDTH, properties.height, frameColor);

    _background.emplace(properties.x, properties.y, properties.width, \
        properties.height, backColor, true, limit, frameColor);
}
