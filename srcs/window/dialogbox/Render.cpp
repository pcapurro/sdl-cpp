#include "DialogBox.hpp"

void	DialogBox::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	for (auto& element : _elements)
		element->render(renderer);

	for (auto& button : _buttons)
		button->render(renderer);
}
