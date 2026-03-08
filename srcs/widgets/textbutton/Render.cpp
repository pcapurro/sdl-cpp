#include "TextButton.hpp"

void    TextButton::render(SDL_Renderer* renderer)
{
    Shape*      back = &_background.value();
    Text*       text = &_mainText.value();

    back->render(renderer);
    text->render(renderer);
}
