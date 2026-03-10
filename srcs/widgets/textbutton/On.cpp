#include "TextButton.hpp"

void	TextButton::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _mainText->update(_mainText->getTextStr(), \
        properties.width, true, renderer);

    _background->setWidth(properties.width);
    _background->setHeight(properties.height);
}

void	TextButton::onPositionChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _mainText->setX(properties.x + \
        (properties.width / 2 - _mainText->getWidth() / 2), renderer);

    _mainText->setY(properties.y + \
        (properties.height / 2 - _mainText->getHeight() / 2), renderer);

    _background->setX(properties.x);
    _background->setY(properties.y);
}

void	TextButton::onStyleChanged(void)
{
    Shape*      back = &_background.value();

    back->setMainColor(getMainColor());
    back->setSelectColor(getSelectColor());
}

void	TextButton::onSettingsChanged(void)
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

void	TextButton::onStateChanged(void)
{
    Shape*      back = &_background.value();

    back->setHover(isHover());
    back->setSelected(isSelected());

    back->setHighlight(isHighlighted());
    back->setFocus(isFocused());
}

void    TextButton::onMouseDown(const int x, const int y, \
    SDL_Renderer* renderer)
{
    setClick(true, false);
    setFocus(true, false);

    onStateChanged();

    (void) x;
    (void) y;

    (void) renderer;
}

void    TextButton::onMouseDownOutside(SDL_Renderer* renderer)
{
    setClick(false, false);
    setSelected(false, false);
    setFocus(false, false);

    onStateChanged();

    (void) renderer;
}

void    TextButton::onMouseUp(const int x, const int y, \
    SDL_Renderer* renderer)
{
    setFocus(false);

    (void) x;
    (void) y;

    (void) renderer;
}

void    TextButton::onMouseHover(const int x, const int y, \
    SDL_Renderer* renderer)
{
    setHover(true);

    (void) x;
    (void) y;

    (void) renderer;
}

void    TextButton::onMouseHoverOutside(SDL_Renderer* renderer)
{
    setHover(false);

    (void) renderer;
}
