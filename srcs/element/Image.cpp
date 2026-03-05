#include "Image.hpp"

Image::Image(const Properties& properties, const char* path, \
    SDL_Renderer* renderer) : \
        Element(properties)
{
    _image.emplace(path, renderer);

    SDL_SetTextureBlendMode(_image.value().getTexture(),\
        SDL_BLENDMODE_BLEND);
}

Image::Image(const int x, const int y, const int w, const int h, \
    const char* path, SDL_Renderer* renderer) : \
        Element({x, y, w, h})
{
    _image.emplace(path, renderer);

    SDL_SetTextureBlendMode(_image.value().getTexture(), \
        SDL_BLENDMODE_BLEND);
}

void    Image::render(SDL_Renderer* renderer)
{
    if (!getVisibility() || !_image.has_value())
        return;

    SDL_Rect    main;

    main.x = getX(), main.y = getY();
    main.w = getWidth(), main.h = getHeight();

    SDL_SetTextureAlphaMod(_image.value().getTexture(), getOpacity());

    SDL_RenderCopy(renderer, _image.value().getTexture(), \
        nullptr, &main);

    if (isHighlightPossible() && isHighlighted())
    {
        Color       avgColor = _image.value().getAverageColor();
        Color       highlightColor;
        uint8_t     opacity = HIGHLIGHT_OPACITY;

        if (isFocusPossible() && isFocused())
            opacity = FOCUS_OPACITY;

		if (avgColor.getAverage() < 128)
            highlightColor.setColor(0, 0, 0, opacity);
        else
            highlightColor.setColor(255, 255, 255, opacity);

        Render::renderHighlight(getX(), getY(), getWidth(), \
            getHeight(), highlightColor, renderer);
    }

    if (isSelectPossible() && isSelected() && getSelectType() != NONE)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
    }
}

void    Image::update(const char* path, SDL_Renderer* renderer)
{
    _image.reset();

    _image.emplace(path, renderer);
}
