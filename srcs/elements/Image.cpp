#include "Image.hpp"

Image::Image(const int x, const int y, const int w, const int h, \
    const char* path, SDL_Renderer* renderer) : \
        Element({x, y, w, h})
{
    _image.emplace(path, renderer);

    SDL_SetTextureBlendMode(_image->getTexture(), \
        SDL_BLENDMODE_BLEND);
}

Image::Image(const int x, const int y, const int w, const int h, \
    const char* path, const Color& color, SDL_Renderer* renderer) : \
        Element({x, y, w, h})
{
    _image.emplace(path, color, renderer);

    SDL_SetTextureBlendMode(_image->getTexture(), \
        SDL_BLENDMODE_BLEND);
}

void    Image::render(SDL_Renderer* renderer)
{
    if (!isVisible() || !_image)
        return;

    SDL_Rect    main;

    main.x = getX(), main.y = getY();
    main.w = getWidth(), main.h = getHeight();

    SDL_SetTextureAlphaMod(_image->getTexture(), getMainColor().a);

    SDL_RendererFlip    flip = SDL_FLIP_NONE;

    if (_horizontalFlip && _verticalFlip)
        flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    else if (_horizontalFlip)
        flip = SDL_FLIP_HORIZONTAL;
    else if (_verticalFlip)
        flip = SDL_FLIP_VERTICAL;

    SDL_RenderCopyEx(renderer, _image->getTexture(), \
        nullptr, &main, 0.0, nullptr, flip);

    if ((isHighlightPossible() && isHighlighted()) \
        || (isHoverPossible() && isHover()))
    {
        Color       avgColor = _image->getAverageColor();
        Color       highlightColor;
        uint8_t     opacity = Render::HiglihtOpacity;

        if (isFocusPossible() && isFocused())
            opacity = Render::FocusOpacity;

		if (avgColor.getAverage() < 128)
            highlightColor.setColor(0, 0, 0, opacity);
        else
            highlightColor.setColor(255, 255, 255, opacity);

        Render::renderHighlight(getX(), getY(), getWidth(), \
            getHeight(), highlightColor, renderer);
    }

    if (isSelectPossible() && isSelected() && getSelectType() != State::None)
    {
        Render::renderSelect(getSelectType(), getX(), getY(), \
            getWidth(), getHeight(), getSelectColor(), renderer);
    }
}

Color   Image::getAverageColor(void) const noexcept
{
    return _image->getAverageColor();
}

void    Image::setHorizontalFlip(const bool value)
{
    _horizontalFlip = value;
}

void    Image::setVerticalFlip(const bool value)
{
    _verticalFlip = value;
}
