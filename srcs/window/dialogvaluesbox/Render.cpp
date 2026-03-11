#include "DialogValuesBox.hpp"

void	DialogValuesBox::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (!renderer)
		return;

	for (auto& element : _elements)
		element->render(renderer);

	_okButton->render(renderer);

	if (_upField)
	{
		_upField->render(renderer);
		_upError->render(renderer);
	}

	_downField->render(renderer);
	_downError->render(renderer);
}
