#include "Text.hpp"

Text::Text(const Config& config, const string& text, const int size, \
    const Color& color, const string& fontPath, SDL_Renderer* renderer, const int maxWidth) : \
    Element(config), \
    _font(fontPath, size)
{
    int width = 0;
    int height = 0;

    Texture     texture(text.c_str(), _font.getFont(), \
        {color.r, color.g, color.b, color.a}, renderer, maxWidth);

    SDL_QueryTexture(texture.getTexture(), nullptr, \
        nullptr, &width, &height);

    setWidth(width);
    setHeight(height);

    setTexture(texture);
}
