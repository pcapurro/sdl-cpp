#include "TextField.hpp"

void	TextField::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    if (_mainText.has_value())
    {
        _mainText.value().update(_mainText.value().getTextStr(), \
            properties.width, _wrapping, renderer);
    }

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.value().update(properties.x, properties.y, \
        properties.width, properties.height, limit, renderer);

    _background.value().setWidth(properties.width, renderer);
    _background.value().setHeight(properties.height, renderer);

    _cursor.value().setHeight(properties.height - (limit * 2), renderer);
}

void	TextField::onPositionChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};
    int         cursorX = (getWidth() / 2) * LIMIT_RATIO;

    if (_mainText.has_value())
    {
        _mainText.value().setX(properties.x + cursorX, renderer);

        _mainText.value().setY(properties.y + \
            (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);
    }

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.value().setX(properties.x);
    _background.value().setY(properties.y);

    _cursor.value().setX(properties.x + cursorX);
    _cursor.value().setY(properties.y + limit);
}

void	TextField::onStyleChanged(void)
{
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
        text->setHover(isHover());
        text->setSelected(isSelected());

        back->setHover(false);
    }
    else
        back->setHover(isHover());
}

void    TextField::onMouseDown(const int x, const int y)
{
    (void) x;
    (void) y;

    setClick(true, false);
    setHover(false, false);

    if (isSelected())
        setSelected(false, false);

    onStateChanged();
}

void    TextField::onMouseDownDouble(const int x, const int y)
{
    (void) x;
    (void) y;

    setClick(true, false);

    if (_mainText.has_value())
        setSelected(true, false);

    onStateChanged();
}

void    TextField::onMouseDownOutside(void)
{
    setSelected(false, false);
    setClick(false, false);

    onStateChanged();
}

void    TextField::onMouseUp(const int x, const int y)
{
    (void) x;
    (void) y;

    // ...
}

void    TextField::onMouseUpOutside(void)
{
    // ...
}

void    TextField::onMouseHover(const int x, const int y)
{
    (void) x;
    (void) y;
    
    if (!isClicked())
        setHover(true);
}

void    TextField::onMouseHoverOutside(void)
{
    setHover(false);
}

void    TextField::onButtonDown(const int key)
{
    (void) key;

    // ...
}
