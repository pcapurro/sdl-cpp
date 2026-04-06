#include "ImageButton.hpp"

ImageButton::ImageButton(const int x, const int y, const int width, const int height, \
    const string& path, const Color& mainColor, const Color& backColor, \
    const int borderThickness, const Color& borderColor, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
    Properties  properties = {x, y, width, height};

    _mainImage.emplace(x, y, properties.width, \
        properties.height, path.c_str(), mainColor, renderer);

    _mainImage->setX(properties.x, renderer);
    _mainImage->setY(properties.y, renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * Render::LimitRatio;

    _background.emplace(properties.x, properties.y, properties.width, \
        properties.height, backColor, true, limit, borderColor);

    if (borderThickness > 0)
    {
        _border.emplace(properties.x, properties.y, properties.width, properties.height, \
            Color::Invisible, true, borderThickness, borderColor);
    }
}
