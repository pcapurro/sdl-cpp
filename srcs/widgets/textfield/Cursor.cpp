#include "TextField.hpp"

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
