#include "DialogTextBox.hpp"

void	DialogTextBox::reactMouseMotion(const int x, const int y)
{
	bool		isAbove = false;
	Element*	element = nullptr;

	for (auto& button : _buttons)
	{
		element = button.get();

		if (element->isAbove(x, y))
		{
			element->onMouseHover();
			SDL_SetCursor(getCursor(element->getHoverCursor()));

			isAbove = true;
		}
		else
			element->onMouseHoverOutside(getRenderer());
	}

    if (!isAbove)
        SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

int		DialogTextBox::reactMouseButtonUp(const int x, const int y)
{
	Element*		element = nullptr;
	SDL_Renderer*	renderer = getRenderer();

	for (auto& button : _buttons)
	{
		element = button.get();

		if (element->isAbove(x, y))
		{
			element->onMouseUp(x, y, renderer);

			TextField*	textField = dynamic_cast \
				<TextField*>(element);

			if (!textField)
				return RETURN;
		}
		else
			element->onMouseUpOutside(renderer);
	}

	return OK;
}

void	DialogTextBox::reactMouseButtonDown(const int x, const int y, \
	const int clicks)
{
	Element*	element = nullptr;

	for (auto& button : _buttons)
	{
		element = button.get();

		if (element->isAbove(x, y))
		{
			if (clicks > 1)
				element->onMouseDownDouble();
			else
				element->onMouseDown(x, y);
		}
		else
			element->onMouseDownOutside(getRenderer());
	}
}

int		DialogTextBox::reactKeyButtonDown(const int key)
{
	TextField*		textField = dynamic_cast<TextField*> \
		(_buttons.front().get());

	textField->onButtonDown(key, getRenderer());

	if (key == SDLK_TAB)
	{
		_buttons[_tabCursor]->setClick(false);
		_buttons[_tabCursor]->setSelected(false);
		_buttons[_tabCursor]->setHover(false);

		if (_tabCursor < _buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		_buttons[_tabCursor]->setHover(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		_buttons[_tabCursor]->onMouseDown();

		TextButton*	textButton = dynamic_cast \
			<TextButton*>(_buttons[_tabCursor].get());

		if (textButton)
			return RETURN;
	}

	return OK;
}

void	DialogTextBox::reactCharactersDown(const char* text)
{
	TextField*		textField = dynamic_cast<TextField*> \
		(_buttons.front().get());
	SDL_Renderer*	renderer = getRenderer();

	if (!textField->isClicked())
		return;

	textField->add(text, renderer);

	string	error = textField->getLastError();

	if (error.size() > 0)
	{
		Text*	errorText = dynamic_cast<Text*> \
			(_elements.back().get());

		int		limitX = getWidth() * LIMIT_RATIO;
		int		maxWidth = getWidth() - (limitX * 2);

		errorText->update(error, maxWidth, false, renderer);
		_elements.back()->setVisibility(true);
	}
	else if (_elements.back()->isVisible())
		_elements.back()->setVisibility(false);
}

int		DialogTextBox::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);

	else if (event->type == SDL_MOUSEBUTTONDOWN \
		&& event->button.button == SDL_BUTTON_LEFT)
		reactMouseButtonDown(x, y, event->button.clicks);

	else if (event->type == SDL_MOUSEBUTTONUP \
		&& event->button.button == SDL_BUTTON_LEFT)
		value = reactMouseButtonUp(x, y);

	else if (event->type == SDL_KEYDOWN)
		value = reactKeyButtonDown(event->key.keysym.sym);

	else if (event->type == SDL_TEXTINPUT)
		reactCharactersDown(event->text.text);

	refreshDisplay();

	return value;
}
