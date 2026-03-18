#include "TextField.hpp"

void    TextField::render(SDL_Renderer* renderer)
{
    if (_background)
        _background->render(renderer);

    if (_mainText)
        _mainText->render(renderer);

    if (isClicked() && !isHover() && !isSelected())
        _cursor->render(renderer);
}
