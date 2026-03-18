#include "ImageButton.hpp"

void    ImageButton::render(SDL_Renderer* renderer)
{
    _background->render(renderer);
    _mainImage->render(renderer);

    if (_border)
        _border->render(renderer);
}
