#include "TextField.hpp"

TextField::TextField(const Properties& properties, const Color& backColor, \
    const string& text, const string& placeholder, const int size, const Color& textColor, \
    const string& fontPath, SDL_Renderer* renderer) : \
        Element(properties)
{
    _mainText.emplace(properties.x, properties.y, text, size, \
        textColor, fontPath, renderer, properties.width);

    _mainText.value().setX(properties.x, renderer);
    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    Color   placeholderColor = textColor;

    placeholderColor.a -= placeholderColor.a / 3;

    _placeholder.emplace(properties.x, properties.y, placeholder, size, \
        placeholderColor, fontPath, renderer, properties.width);

    _placeholder.value().setX(properties.x, renderer);
    _placeholder.value().setX(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, textColor);
}

TextField::TextField(const int x, const int y, const int width, const int height, \
    const Color& backColor, const string& text, const string& placeholder, const int size, \
    const Color& textColor, const string& fontPath, SDL_Renderer* renderer) : \
        Element({x, y, width, height})
{
    Properties  properties = {x, y, width, height};

    _mainText.emplace(x, y, text, size, \
        textColor, fontPath, renderer, properties.width);

    _mainText.value().setX(properties.x, renderer);
    _mainText.value().setY(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    _placeholder.emplace(properties.x, properties.y, placeholder, size, \
        textColor, fontPath, renderer, properties.width);

    _placeholder.value().setX(properties.x, renderer);
    _placeholder.value().setX(properties.y + \
        (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, textColor);
}

void    TextField::setSettings(const bool select, const int selectType, \
    const bool hover, const int hoverCursor, const bool highlight, const bool focus) noexcept
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

string  TextField::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText.value().getTextStr();
}

string  TextField::getPlaceholder(void) const
{
    if (!_placeholder.has_value())
        return "";

    return _placeholder.value().getTextStr();
}

void	TextField::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    _mainText.value().update(_mainText.value().getTextStr(), properties.width, renderer);

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

void	TextField::onStyleChanged(void)
{
    Shape*      back = &_background.value();

    back->setOpacity(getOpacity());

    back->setMainColor(getMainColor());
    back->setSelectColor(getSelectColor());
}

void	TextField::onSettingsChanged(void)
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

void	TextField::onStateChanged(void)
{
    Shape*      back = &_background.value();

    back->setHover(isHover());
    back->setSelected(isSelected());

    back->setHighlight(isHighlighted());
    back->setFocus(isFocused());
}

void    TextField::render(SDL_Renderer* renderer)
{
    Shape*      back = &_background.value();
    Text*       text = &_mainText.value();

    back->setX(getX(), renderer);
    back->setY(getY(), renderer);

    back->render(renderer);

    text->setX(getX() + (getWidth() / 2 - text->getWidth() / 2), renderer);
    text->setY(getY() + (getHeight() / 2 - text->getHeight() / 2), renderer);

    text->render(renderer);
}
