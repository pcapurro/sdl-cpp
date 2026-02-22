#include "Text.hpp"

Text::Text(const Config& config, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer) : \
    Element(config), \
    _font(fontPath, size), \
    _texture(text.c_str(), _font.getFont(), \
        {color.r, color.g, color.b, color.a}, renderer)
{
    setTexture(_texture.getTexture());
}
