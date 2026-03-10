#include "ValueField.hpp"

void    ValueField::updateCursor(SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;
        
    int newX = _mainText->getCharX(_cursorPos);
    int newY = _mainText->getCharY(_cursorPos);

    _cursor->setX(newX, renderer);
    _cursor->setY(newY, renderer);
}

void    ValueField::updateCursor(const int x, const int y, SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    int newY = _mainText->getLineY(y);
    int newX = _mainText->getClosestCharX(x, newY);

    _cursor->setX(newX, renderer);
    _cursor->setY(newY, renderer);
}

void    ValueField::moveCursorForward(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || \
        _cursorPos >= _mainText->getTextStr().size())
    {
        _lastError.clear();
        return;
    }

    _cursorPos++;

    updateCursor(renderer);
}

void    ValueField::moveCursorBackward(SDL_Renderer* renderer)
{
    if (!_mainText.has_value() || _cursorPos <= 0)
    {
        _lastError.clear();
        return;
    }

    _cursorPos--;

    updateCursor(renderer);
}
