#include "DialogBox.hpp"

void	DialogBox::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (renderer)
	{
		for (auto& element : _elements)
			element.get()->render(renderer);

		for (auto& button : _buttons)
			button.get()->render(renderer);
	}
}
