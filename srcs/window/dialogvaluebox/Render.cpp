#include "DialogValueBox.hpp"

void	DialogValueBox::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	for (auto& element : _elements)
		element->render(renderer);

	_okButton->render(renderer);

	_upField->render(renderer);
	_downField->render(renderer);
}
