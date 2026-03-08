#include "TextField.hpp"

TextField::TextField(const Properties& properties, const Color& backColor, \
    const Color& frameColor, const string& fontPath, const Color& textColor, \
    const int maxChar, const bool wrapping) : \
        Element(properties), \
        _maxChar(maxChar), \
        _fontPath(fontPath), \
        _textColor(textColor), \
        _wrapping(wrapping)
{
    int     limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursorPos = 0;

    _cursor.emplace(Properties{properties.x, properties.y + limit, \
        CURSOR_WIDTH, properties.height - (limit * 2)}, frameColor);

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
}

TextField::TextField(const int x, const int y, const int width, const int height, \
    const Color& backColor, const Color& frameColor, const string& fontPath, \
    const Color& textColor, const int maxChar, \
    const bool wrapping) : \
        Element({x, y, width, height}), \
        _maxChar(maxChar), \
        _fontPath(fontPath), \
        _textColor(textColor), \
        _wrapping(wrapping)
{
    Properties  properties = {x, y, width, height};
    int         limit = properties.width < properties.height \
        ? properties.width : properties.height;

    limit = limit * LIMIT_RATIO;

    _cursor.emplace(Properties{properties.x, properties.y + limit, \
        CURSOR_WIDTH, properties.height - (limit * 2)}, frameColor);

    _background.emplace(properties, backColor, \
        true, limit, frameColor);
}

string  TextField::getLastError(void)
{
    return std::move(_lastError);
}

void    TextField::clear(SDL_Renderer* renderer)
{
    _cursorPos = 0;
    updateCursor(renderer);

    _mainText.reset();
}

void    TextField::removeBefore(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || _cursorPos == 0)
    {
        _lastError.clear();
        return;
    }

    string  text = _mainText.value().getTextStr();

    _cursorPos--;
    updateCursor(renderer);

    text.erase(_cursorPos, 1);

    if (text.empty())
        _mainText.reset();
    else
    {
        int     limitX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText.value().update(text, getWidth() - (limitX * 2), \
            _wrapping, renderer);
    }

    _lastError.clear();
}

void    TextField::removeAfter(SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    string  text = _mainText.value().getTextStr();

    if (_cursorPos >= text.size())
    {
        _lastError.clear();
        return;
    }

    text.erase(_cursorPos, 1);

    if (text.empty())
        _mainText.reset();
    else
    {
        int     limitX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText.value().update(text, getWidth() - (limitX * 2), \
            _wrapping, renderer);
    }

    _lastError.clear();
}

void    TextField::add(const string& text, SDL_Renderer* renderer)
{
    int     oldLinesNb = _mainText.has_value() ? \
        _mainText.value().getLinesNb() : 1;
    int     limitX = (getWidth() / 2) * LIMIT_RATIO;

    if (_mainText.has_value())
    {
        string  oldText = _mainText.value().getTextStr();
        string  newText;

        if (oldText.size() >= _maxChar)
        {
            _lastError = "Text has reached the limit (" \
                + std::to_string(_maxChar) + string(").");

            return;
        }

        if (_cursorPos < oldText.size())
        {
            newText = oldText.substr(0, _cursorPos) \
                + text + (oldText.substr(_cursorPos));
        }
        else
            newText = oldText + text;

        _mainText.value().update(newText, getWidth() - (limitX * 2), \
            _wrapping, renderer);

        if (_mainText.value().getTextStr().size() > oldText.size())
            _cursorPos++;
    }
    else
    {
        int     textRatio = getHeight() / 4;

        _mainText.emplace(getX() + limitX, getY(), text, getHeight() - textRatio, \
            _textColor, _fontPath, renderer, getWidth() - (limitX * 2), _wrapping);

        _cursorPos += text.size();

        onPropertiesChanged(renderer);
        onStateChanged();

        onSettingsChanged();
        onStyleChanged();

        _originalHeight = _mainText.value().getHeight();
    }

    if (_wrapping && oldLinesNb < _mainText.value().getLinesNb())
    {
        setHeight(getHeight() + _originalHeight, renderer, false);
        _background.value().setHeight(getHeight(), renderer);
    }

    updateCursor(renderer);

    _lastError.clear();
}

string  TextField::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText.value().getTextStr();
}

void    TextField::updateCursor(SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;
        
    int newX = _mainText.value().getCharX(_cursorPos);
    int newY = _mainText.value().getCharY(_cursorPos);

    _cursor.value().setX(newX, renderer);
    _cursor.value().setY(newY, renderer);
}

void    TextField::updateCursor(const int x, const int y, SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    int newY = _mainText.value().getLineY(y);
    int newX = _mainText.value().getClosestCharX(x, newY);

    _cursor.value().setX(newX, renderer);
    _cursor.value().setY(newY, renderer);
}

void    TextField::setWrapping(const bool wrapping) noexcept
{
    _wrapping = wrapping;
}

void    TextField::moveCursorForward(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || \
        _cursorPos >= _mainText.value().getTextStr().size())
    {
        _lastError.clear();
        return;
    }

    _cursorPos++;

    updateCursor(renderer);
}

void    TextField::moveCursorBackward(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || _cursorPos <= 0)
    {
        _lastError.clear();
        return;
    }

    _cursorPos--;

    updateCursor(renderer);
}

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

    if (isClicked() && !isHover() && !isSelected())
        _cursor.value().render(renderer);
}
