#include "ValueField.hpp"

void    ValueField::clear(SDL_Renderer* renderer)
{
    _cursorPos = 0;
    updateCursor(renderer);

    _lastError.clear();

    _mainText.reset();

    setWidth(_originalWidth);
    setHeight(_originalHeight);
}

void    ValueField::removeBefore(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || _cursorPos == 0)
        return;

    string  text = _mainText->getTextStr();

    _cursorPos--;
    updateCursor(renderer);

    text.erase(_cursorPos, 1);

    if (text.empty())
    {
        _mainText.reset();
        _lastError.clear();
    }
    else
    {
        int     limitX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText->update(text, getWidth() - (limitX * 2), \
            false, renderer);
    }

    validateValue();
}

void    ValueField::removeAfter(SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    string  text = _mainText->getTextStr();

    if (_cursorPos >= text.size())
        return;

    text.erase(_cursorPos, 1);

    if (text.empty())
    {
        _mainText.reset();
        _lastError.clear();
    }
    else
    {
        int     limitX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText->update(text, getWidth() - (limitX * 2), \
            false, renderer);
    }

    validateValue();
}

void    ValueField::joinValue(const string& text, SDL_Renderer* renderer)
{
    int     limitX = (getWidth() / 2) * LIMIT_RATIO;
    string  oldText = _mainText->getTextStr();

    if (oldText.size() >= _maxChar
        || oldText.size() + text.size() > _maxChar)
        return;

    string  newText;

    if (_cursorPos < oldText.size())
    {
        newText = oldText.substr(0, _cursorPos) \
            + text + (oldText.substr(_cursorPos));
    }
    else
        newText = oldText + text;

    _mainText->update(newText, getWidth() - (limitX * 2), \
        false, renderer);

    if (_mainText->getTextStr().size() > oldText.size())
        _cursorPos++;
}

void    ValueField::createValue(const string& text, SDL_Renderer* renderer)
{
    int     textRatio = getHeight() / 4;
    int     limitX = (getWidth() / 2) * LIMIT_RATIO;

    if (text.size() > _maxChar)
        return;

    _mainText.emplace(getX() + limitX, getY(), text, getHeight() - textRatio, \
        _fontPath, _textColor, getWidth() - (limitX * 2), false, renderer);

    _cursorPos += text.size();

    _originalWidth = getWidth();
    _originalHeight = getHeight();

    onSettingsChanged();
    onStyleChanged();
}

void    ValueField::add(const string& text, SDL_Renderer* renderer)
{
    if (_mainText.has_value())
        joinValue(text, renderer);
    else
        createValue(text, renderer);

    validateValue();

    updateCursor(renderer);
}

void    ValueField::increase(void)
{
    ;
}

void    ValueField::decrease(void)
{
    ;
}
