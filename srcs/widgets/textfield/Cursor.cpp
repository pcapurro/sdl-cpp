#include "TextField.hpp"

void    TextField::updateCursor(SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;
        
    int newX = _mainText->getCharX(_cursorPos);
    int newY = _mainText->getCharY(_cursorPos);

    _cursor->setX(newX, renderer);
    _cursor->setY(newY, renderer);
}

void    TextField::updateCursor(const int x, const int y, SDL_Renderer* renderer)
{
    if (!_mainText.has_value())
        return;

    int newY = _mainText->getLineY(y);
    int newX = _mainText->getClosestCharX(x, newY);

    _cursor->setX(newX, renderer);
    _cursor->setY(newY, renderer);
}

void    TextField::moveCursorForward(SDL_Renderer* renderer)
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
