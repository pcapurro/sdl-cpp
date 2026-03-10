#include "ValueField.hpp"

void    ValueField::clear(SDL_Renderer* renderer)
{
    _cursorPos = 0;
    updateCursor(renderer);

    _mainText.reset();

    setWidth(_originalWidth);
    setHeight(_originalHeight);
}

void    ValueField::removeBefore(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || _cursorPos == 0)
    {
        _lastError.clear();
        return;
    }

    string  text = _mainText->getTextStr();

    _cursorPos--;
    updateCursor(renderer);

    text.erase(_cursorPos, 1);

    if (text.empty())
        _mainText.reset();
    else
    {
        int     limitX = (getWidth() / 2) * LIMIT_RATIO;

        _mainText->update(text, getWidth() - (limitX * 2), \
            false, renderer);
    }

    _lastError.clear();
}

void    ValueField::removeAfter(SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    string  text = _mainText->getTextStr();

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

        _mainText->update(text, getWidth() - (limitX * 2), \
            false, renderer);
    }

    _lastError.clear();
}

void    ValueField::joinText(const string& text, SDL_Renderer* renderer)
{
    int     limitX = (getWidth() / 2) * LIMIT_RATIO;
    string  oldText = _mainText->getTextStr();

    if (oldText.size() >= _maxChar
        || oldText.size() + text.size() > _maxChar)
    {
        _lastError = "Text has reached the limit (" \
            + std::to_string(_maxChar) + string(").");

        return;
    }

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

    _lastError.clear();
}

void    ValueField::createText(const string& text, SDL_Renderer* renderer)
{
    if (text.size() > _maxChar)
    {
        _lastError = "Text has reached the limit (" \
            + std::to_string(_maxChar) + string(").");

        return;
    }

    int     textRatio = getHeight() / 4;
    int     limitX = (getWidth() / 2) * LIMIT_RATIO;

    _mainText.emplace(getX() + limitX, getY(), text, getHeight() - textRatio, \
        _fontPath, _textColor, getWidth() - (limitX * 2), false, renderer);

    _cursorPos += text.size();

    _originalWidth = getWidth();
    _originalHeight = getHeight();

    onPropertiesChanged(renderer);
    onStateChanged();

    onSettingsChanged();
    onStyleChanged();

    _lastError.clear();
}

void    ValueField::add(const string& text, SDL_Renderer* renderer)
{
    if (_mainText.has_value())
        joinText(text, renderer);
    else
        createText(text, renderer);

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
