#include "TextButton.hpp"

TextButton::TextButton(const Properties& properties, const Color& backColor, \
    const string& text, const int size, const Color& textColor, \
    const string& fontPath, SDL_Renderer* renderer) : \
        Element(properties)
{
    _mainText.emplace(properties.x, properties.y, text, size, \
        textColor, fontPath, renderer, properties.width);

    _mainText.value().setX(properties.x + \
        (properties.width / 2 - _mainText.value().getWidth() / 2));

    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2));

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
        (properties.width / 2 - _mainText.value().getWidth() / 2));

    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2));

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, textColor);
}

void    TextButton::setSettings(const bool select, const int selectType, \
    const bool hover, const int hoverCursor, const bool highlight, const bool focus)
{
    select ? enableSelect() : disableSelect();
    if (select && selectType != DEFAULT && selectType != NONE)
        setSelectType(selectType);

    hover ? enableHover() : disableHover();
    if (hover && hoverCursor != DEFAULT && hoverCursor != NONE)
        setHoverCursor(hoverCursor);

    highlight ? enableHighlight() : disableHighlight();
    focus ? enableFocus() : disableFocus();
}

void    TextButton::render(SDL_Renderer* renderer)
{
    Shape*      back = &_background.value();
    Text*       text = &_mainText.value();

    if (isHoverPossible())
        back->setHover(isHover()), back->setHoverCursor(getHoverCursor());

    if (isSelectPossible())
        back->setSelected(isSelected()), back->setSelectColor(getSelectColor());

    if (isHighlightPossible())
        back->enableHighlight(), back->setHighlight(isHighlighted());

    if (isFocusPossible())
        back->enableFocus(), back->setFocus(isFocused());

    back->setX(getX());
    back->setY(getY());

    back->render(renderer);

    text->setX(getX() + (getWidth() / 2 - text->getWidth() / 2));

    text->setY(getY() + (getHeight() / 2 - text->getHeight() / 2));

    text->render(renderer);
}
