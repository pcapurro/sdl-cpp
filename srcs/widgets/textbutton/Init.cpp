#include "TextButton.hpp"

TextButton::TextButton(const int x, const int y, const int width, const int height, \
    const Color& backColor, const string& text, const int size, \
    const Color& textColor, const string& fontPath, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
    Properties  properties = {x, y, width, height};

    _mainText.emplace(x, y, text, size, \
        textColor, fontPath, renderer, width);

    _mainText->setX(properties.x + \
        (properties.width / 2 - _mainText->getWidth() / 2), renderer);

    _mainText->setY(properties.y + \
        (properties.height / 2 - _mainText->getHeight() / 2), renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties.x, properties.y, properties.width, \
        properties.height, backColor, true, limit, textColor);
}
