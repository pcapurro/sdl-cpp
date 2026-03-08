#include "TextField.hpp"

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
