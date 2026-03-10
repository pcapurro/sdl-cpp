#include "ValueField.hpp"

void	ValueField::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};

    if (_mainText.has_value())
    {
        _mainText->update(_mainText->getTextStr(), \
            properties.width, false, renderer);
    }

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background->setWidth(properties.width, renderer);
    _background->setHeight(properties.height, renderer);

    _background->setBorderThickness(limit);

    _cursor->setHeight(properties.height, renderer);
}

void	ValueField::onPositionChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};
    int         cursorX = (getWidth() / 2) * LIMIT_RATIO;

    if (_mainText.has_value())
    {
        _mainText->setX(properties.x + cursorX, renderer);

        _mainText->setY(properties.y + \
            (properties.height / 2 - _mainText->getHeight() / 2), renderer);
    }

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursor->setX(properties.x + cursorX);
    _cursor->setY(properties.y);

    _background->setX(properties.x);
    _background->setY(properties.y);
}

void	ValueField::onStyleChanged(void)
{
    Text*       text = _mainText.has_value() ? \
        &_mainText.value() : nullptr;

    if (text)
        text->setSelectColor(getSelectColor());
}

void	ValueField::onSettingsChanged(void)
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
        {
            text->enableSelect();
            text->setSelectType(getSelectType());
        }
        else
            text->disableSelect();

        if (isHoverPossible())
            text->enableHover();
        else
            text->disableHover();
    }
}

void	ValueField::onStateChanged(void)
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

void    ValueField::onButtonDown(const int key, SDL_Renderer* renderer)
{
    if (!isClicked())
        return;

    if (key == SDLK_LEFT)
        moveCursorBackward(renderer);
    else if (key == SDLK_RIGHT)
        moveCursorForward(renderer);
    else if (key == SDLK_BACKSPACE || key == SDLK_DELETE)
    {
        if (isSelected())
            clear(renderer);
        else
        {
            if (key == SDLK_DELETE)
                removeAfter(renderer);
            else
                removeBefore(renderer);
        }
    }
}

void    ValueField::onMouseDown(const int x, const int y, SDL_Renderer* renderer)
{
    setClick(true, false);
    setHover(false, false);

    if (isSelected())
        setSelected(false, false);

    onStateChanged();

    (void) x;
    (void) y;

    (void) renderer;
}

void    ValueField::onMouseDownDouble(const int x, const int y, SDL_Renderer* renderer)
{
    setClick(true, false);

    if (_mainText.has_value())
        setSelected(true, false);

    onStateChanged();

    (void) x;
    (void) y;

    (void) renderer;
}

void    ValueField::onMouseDownOutside(SDL_Renderer* renderer)
{
    setSelected(false, false);
    setClick(false, false);

    onStateChanged();

    (void) renderer;
}

void    ValueField::onMouseUp(const int x, const int y, SDL_Renderer* renderer)
{
    updateCursor(x, y, renderer);
}

void    ValueField::onMouseHover(const int x, const int y, SDL_Renderer* renderer)
{
    if (!isClicked())
        setHover(true);

    (void) x;
    (void) y;

    (void) renderer;
}

void    ValueField::onMouseHoverOutside(SDL_Renderer* renderer)
{
    setHover(false);

    (void) renderer;
}
