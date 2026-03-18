#include "TextButton.hpp"

void    TextButton::render(SDL_Renderer* renderer)
{
    _background->render(renderer);
    _mainText->render(renderer);
}
