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

void    TextField::clear(void)
{
    _mainText.reset();
}

void    TextField::update(const string& text, const string& fontPath, \
    const Color& textColor, SDL_Renderer* renderer)
{
    if (_mainText.has_value())
        _mainText.value().update(text, getWidth(), renderer);
    else
    {
        int     cursorX = (getWidth() / 2) * LIMIT_RATIO;
        int     textRatio = getHeight() / 4;

        _mainText.emplace(getX() + cursorX, 0, text, getHeight() - textRatio, \
            textColor, fontPath, renderer, getWidth());

        onPropertiesChanged(renderer);
        onStateChanged();

        onStyleChanged();
        onSettingsChanged();
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
    Text*       text = _mainText.has_value() ? \
        &_mainText.value() : nullptr;

    if (text)
        text->setSelectColor(getSelectColor());
}

void	TextField::onSettingsChanged(void)
{
    Shape*      back = &_background.value();
    Text*       text = _mainText.has_value() ? \
        &_mainText.value() : nullptr;

    if (isHoverPossible())
        back->enableHover();
    else
        back->disableHover();

    if (text)
    {
        if (isSelectPossible())
            text->enableSelect(), text->setSelectType(getSelectType());
        else
            text->disableSelect();

        if (isHoverPossible())
            text->enableHover();
        else
            text->disableHover();
    }
}

void	TextField::onStateChanged(void)
{
    Shape*      back = &_background.value();
    Text*       text = _mainText.has_value() ? \
        &_mainText.value() : nullptr;

    if (text)
    {
        text->setHover(!isClicked());
        text->setSelected(isSelected());

        back->setHover(false);
    }
    else
        back->setHover(isHover());
}

void    TextField::onMouseDown(void)
{
    setClick(true, false);
    setFocus(true, false);

    onStateChanged();
}

void    TextField::onMouseDownOutside(void)
{
    setClick(false, false);
    setSelected(false, false);
    setFocus(false, false);

    onStateChanged();
}

void    TextField::onMouseUp(void)
{
    setFocus(false);
}

void    TextField::onMouseUpOutside(void)
{
    setFocus(false);
}

void    TextField::onMouseHover(void)
{    
    setHover(true);
}

void    TextField::onMouseHoverOutside(void)
{
    setHover(false);
}

void    TextField::onButtonDown(const int key)
{
    if (key == SDLK_BACKSPACE || key  == SDLK_DELETE)
    {
        if (!isClicked())
            return;

        string	text = getText();
        
        if (isSelected() && text.size() <= 1)
            clear();
        else if (key != SDLK_DELETE)
        {
            text.pop_back();

            // update();
        }
    }
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
