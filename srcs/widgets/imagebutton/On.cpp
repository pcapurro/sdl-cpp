#include "ImageButton.hpp"

void	ImageButton::onPropertiesChanged(SDL_Renderer* /*renderer*/)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _mainImage->setWidth(properties.width);
    _mainImage->setHeight(properties.height);

    _background->setWidth(properties.width);
    _background->setHeight(properties.height);

    _border->setWidth(properties.width);
    _border->setHeight(properties.height);
}

void	ImageButton::onPositionChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _mainImage->setX(properties.x + \
        (properties.width / 2 - _mainImage->getWidth() / 2), renderer);

    _mainImage->setY(properties.y + \
        (properties.height / 2 - _mainImage->getHeight() / 2), renderer);

    _background->setX(properties.x);
    _background->setY(properties.y);

    _border->setX(properties.x);
    _border->setY(properties.y);
}

void	ImageButton::onStyleChanged(void)
{
    Shape*      back = &_background.value();

    back->setMainColor(getMainColor());
    back->setSelectColor(getSelectColor());
}

void	ImageButton::onSettingsChanged(void)
{
    Shape*      back = &_background.value();

    if (isHoverPossible())
    {
        back->enableHover();
        back->setHoverCursor(getHoverCursor());
    }
    else
        back->disableHover();

    if (isSelectPossible())
    {
        back->enableSelect();
        back->setSelectColor(getSelectColor());
    }

    if (isHighlightPossible())
        back->enableHighlight();
    else
        back->disableHighlight();

    if (isFocusPossible())
        back->enableFocus();
    else
        back->disableFocus();
}

void	ImageButton::onStateChanged(void)
{
    Shape*      back = &_background.value();

    back->setHover(isHover());
    back->setSelected(isSelected());

    back->setHighlight(isHighlighted());
    back->setFocus(isFocused());
}

void    ImageButton::onMouseDown(const int /*x*/, const int /*y*/, \
    SDL_Renderer* /*renderer*/)
{
    setClick(true, false);
    setFocus(true, false);

    onStateChanged();
}

void    ImageButton::onMouseDownOutside(SDL_Renderer* /*renderer*/)
{
    setClick(false, false);
    setSelected(false, false);
    setFocus(false, false);

    onStateChanged();
}

void    ImageButton::onMouseUp(const int /*x*/, const int /*y*/, \
    SDL_Renderer* /*renderer*/)
{
    setFocus(false);
}

void    ImageButton::onMouseHover(const int /*x*/, const int /*y*/, \
    SDL_Renderer* /*renderer*/)
{
    setHover(true);
}

void    ImageButton::onMouseHoverOutside(SDL_Renderer* /*renderer*/)
{
    setHover(false);
}
