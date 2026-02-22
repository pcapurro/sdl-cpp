#include "Text.hpp"

Text::Text(const Config& config, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer) : \
    Element(config), \
    _font(fontPath, size), \
    _texture(text.c_str(), _font.getFont(), \
        {color.r, color.g, color.b, color.a}, renderer)
{
    int width = 0;
    int height = 0;

    SDL_QueryTexture(_texture.getTexture(), nullptr, \
        nullptr, &width, &height);

    setW(width);
    setH(height);

    setTexture(_texture.getTexture());
}
