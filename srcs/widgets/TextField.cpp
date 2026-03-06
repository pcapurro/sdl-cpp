#include "TextField.hpp"

TextField::TextField(const Properties& properties, const Color& backColor, \
    const Color& frameColor) : \
        Element(properties)
{
    int     limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursorPos = 0;

    _cursor.emplace(Properties{properties.x, properties.y, \
        CURSOR_WIDTH, getHeight()}, frameColor);

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

    _cursor.emplace(Properties{properties.x, properties.y, \
        CURSOR_WIDTH, getHeight()}, frameColor);

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
}

void    TextField::clear(void)
{
    _mainText.reset();

    _cursorPos = 0;
    _cursor.value().setX(getX());
}

void    TextField::update(const string& text, const string& fontPath, \
    const Color& textColor, const int maxWidth, const bool wrapping, SDL_Renderer* renderer)
{
    if (_mainText.has_value())
    {
        _cursorPos += text.size() - \
            _mainText.value().getTextStr().size();

        _mainText.value().update(text, maxWidth, \
            wrapping, renderer);
    }
    else
    {
        int     cursorX = (getWidth() / 2) * LIMIT_RATIO;
        int     textRatio = getHeight() / 4;

        _mainText.emplace(getX() + cursorX, 0, text, getHeight() - textRatio, \
            textColor, fontPath, renderer, maxWidth);

        onPropertiesChanged(renderer);
        onStateChanged();

        onSettingsChanged();
        onStyleChanged();

        _cursorPos = text.size() - 1;
    }

    setCursor(_mainText.value().getX() + \
        _mainText.value().getWidth(), renderer);
}

string  TextField::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText.value().getTextStr();
}

void    TextField::setCursor(const int x, SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    int newX = _mainText.value().getClosestCharX(x);

    _cursor.value().setX(newX, renderer);
}

void    TextField::moveCursorForward(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || \
        _cursorPos >= _mainText.value().getTextStr().size())
        return;

    int nextWidth = _mainText.value().getNextCharWidth(_cursorPos);

    _cursorPos++;

    _cursor.value().setX(_cursor.value().getX() \
        + nextWidth, renderer);
}

void    TextField::moveCursorBackward(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || _cursorPos <= 0)
        return;

    int prevWidth = _mainText.value().getPreviousCharWidth(_cursorPos);

    _cursorPos--;

    _cursor.value().setX(_cursor.value().getX() \
        - prevWidth, renderer);
}

void	TextField::onPropertiesChanged(SDL_Renderer* renderer)
{
    Properties  properties = {getX(), getY(), getWidth(), getHeight()};
    int         cursorX = (getWidth() / 2) * LIMIT_RATIO;

    if (_mainText.has_value())
    {
        _mainText.value().update(_mainText.value().getTextStr(), \
            properties.width, _mainText.value().isWrapped(), renderer);

        _mainText.value().setX(properties.x + cursorX, renderer);

        _mainText.value().setY(properties.y + \
            (properties.height / 2 - _mainText.value().getHeight() / 2), renderer);
    }

    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _background.value().update(properties.x, properties.y, \
        properties.width, properties.height, limit, renderer);

    _cursor.value().update(properties.x + cursorX, properties.y, \
        CURSOR_WIDTH, properties.height, 0, renderer);
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

void    TextField::onMouseDown(const int x, const int y)
{
    (void) x;
    (void) y;

    setClick(true, false);
    setHover(false, false);

    onStateChanged();
}

void    TextField::onMouseDownDouble(const int x, const int y)
{
    (void) x;
    (void) y;

    setClick(true, false);
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

void    TextField::render(SDL_Renderer* renderer)
{
    Shape*      back = _background.has_value() ? \
        &_background.value() : nullptr;
    Text*       text = _mainText.has_value() ? \
        &_mainText.value() : nullptr;

    if (back)
        back->render(renderer);

    if (text)
        text->render(renderer);

    if (isClicked() && !isSelected())
        _cursor.value().render(renderer);
}
