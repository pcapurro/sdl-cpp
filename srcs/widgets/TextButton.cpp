#include "TextButton.hpp"

TextButton::TextButton(const Properties& properties, const Color& backColor, \
    const string& text, const int size, const Color& textColor, \
    const string& fontPath, SDL_Renderer* renderer) : \
        Element(properties)
{
    _mainText.emplace(properties.x, properties.y, text, size, \
        textColor, fontPath, renderer, properties.width);

    _mainText.value().setX(properties.x + \
        (properties.width / 2 - _mainText.value().getWidth() / 2), renderer);

    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, textColor);
}

TextButton::TextButton(const int x, const int y, const int width, const int height, \
    const Color& backColor, const string& text, const int size, \
    const Color& textColor, const string& fontPath, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
    Properties  properties = {x, y, width, height};

    _mainText.emplace(x, y, text, size, \
        textColor, fontPath, renderer, width);

    _mainText.value().setX(properties.x + \
        (properties.width / 2 - _mainText.value().getWidth() / 2), renderer);

    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, textColor);
}

string  TextButton::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText.value().getTextStr();
}

void	TextButton::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _mainText.value().update(_mainText.value().getTextStr(), \
        properties.width, _mainText.value().isWrapped(), renderer);

    _mainText.value().setX(properties.x + \
        (properties.width / 2 - _mainText.value().getWidth() / 2), renderer);

    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.value().update(properties.x, properties.y, \
        properties.width, properties.height, limit, renderer);
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
        back->enableHover(), back->setHoverCursor(getHoverCursor());
    else
        back->disableHover();

    if (isSelectPossible())
        back->enableSelect(), back->setSelectColor(getSelectColor());

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

void    TextButton::onMouseDown(const int x, const int y)
{
    (void) x;
    (void) y;

    setClick(true, false);
    setFocus(true, false);

    onStateChanged();
}

void    TextButton::onMouseDownOutside(void)
{
    setClick(false, false);
    setSelected(false, false);
    setFocus(false, false);

    onStateChanged();
}

void    TextButton::onMouseUp(const int x, const int y)
{
    (void) x;
    (void) y;

    setFocus(false);
}

void    TextButton::onMouseUpOutside(void)
{
    setFocus(false);
}

void    TextButton::onMouseHover(const int x, const int y)
{
    (void) x;
    (void) y;

    setHover(true);
}

void    TextButton::onMouseHoverOutside(void)
{
    setHover(false);
}

void    TextButton::render(SDL_Renderer* renderer)
{
    Shape*      back = &_background.value();
    Text*       text = &_mainText.value();

    back->render(renderer);
    text->render(renderer);
}
