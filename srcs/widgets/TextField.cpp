#include "TextField.hpp"

TextField::TextField(const Properties& properties, const Color& backColor, \
    const Color& frameColor) : \
        Element(properties)
{
    int     limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
}

TextField::TextField(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& frameColor) : \
        Element({x, y, width, height})
{
    Properties  properties = {x, y, width, height};
    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
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

void    TextField::updateText(const string& text, const string& fontPath, \
    const Color& textColor, SDL_Renderer* renderer)
{
    if (_mainText.has_value())
        _mainText.value().update(text, getWidth(), renderer);
    else
    {
        int     cursorX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText.emplace(getX() + cursorX, 0,
            text, 42, textColor, fontPath, renderer, getWidth());

        _mainText->setX(getX() + cursorX, renderer);
        _mainText->setY(getY() + (getHeight() / 2 - \
            _mainText->getHeight() / 2), renderer);
    }
}

string  TextField::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText.value().getTextStr();
}

void	TextField::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    if (_mainText.has_value())
    {
        _mainText.value().update(_mainText.value().getTextStr(), properties.width, renderer);

        int         cursorX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText.value().setX(properties.x + cursorX, renderer);

        _mainText.value().setY(properties.y + \
            (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);
    }

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

    if (isHighlighted() && getText() == "")
        back->setHighlight(true);
    else
        back->setHighlight(false);

    back->setFocus(isFocused());
}

void    TextField::render(SDL_Renderer* renderer)
{
    Shape*      back = _background.has_value() ? \
        &_background.value() : nullptr;
    Text*       text = _mainText.has_value() ? \
        &_mainText.value() : nullptr;

    if (back)
    {
        back->setX(getX(), renderer);
        back->setY(getY(), renderer);

        back->render(renderer);
    }

    if (text)
    {
        int         cursorX = (getWidth() / 2) * LIMIT_RATIO;

        text->setX(getX() + cursorX, renderer);
        text->setY(getY() + (getHeight() / 2 - text->getHeight() / 2), renderer);

        text->render(renderer);
    }
}
