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
			element->onMouseHoverOutside();
	}

    if (!isAbove)
        SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

int		DialogTextBox::reactMouseButtonUp(const int x, const int y)
{
	Element*	element = nullptr;

	for (auto& button : _buttons)
	{
		element = button.get();

		if (element->isAbove(x, y))
		{
			element->onMouseUp();

			TextField*	textField = dynamic_cast \
				<TextField*>(element);

			if (!textField)
				return RETURN;
			else
				textField->updateCursor(x, y, getRenderer());
		}
		else
			element->onMouseUpOutside();
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
			element->onMouseDownOutside();
	}
}

int		DialogTextBox::reactKeyButtonDown(const int key)
{
	if (key == SDLK_BACKSPACE || key  == SDLK_DELETE)
	{
		TextField*	textField = dynamic_cast<TextField*> \
			(_buttons.front().get());

		if (!textField->isClicked())
			return OK;

		SDL_Renderer*	renderer = getRenderer();
		string			text = textField->getText();

		if (textField->isSelected())
			textField->clear(renderer);
		else
		{
			if (key == SDLK_DELETE)
				textField->removeAfter(renderer);
			else
				textField->removeBefore(renderer);
		}
	}
	else if (key == SDLK_TAB)
	{
		_buttons[_tabCursor].get()->setHover(false);

		if (_tabCursor < _buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		_buttons[_tabCursor].get()->setHover(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		_buttons[_tabCursor].get()->onMouseDown();

		TextButton*	textButton = dynamic_cast \
			<TextButton*>(_buttons[_tabCursor].get());

		if (textButton)
			return RETURN;
	}
	else if (key == SDLK_LEFT || key == SDLK_RIGHT)
	{
		TextField*	textField = dynamic_cast<TextField*> \
			(_buttons.front().get());

		if (!textField->isClicked())
			return OK;

		if (key == SDLK_LEFT)
			textField->moveCursorBackward(getRenderer());
		else
			textField->moveCursorForward(getRenderer());
	}

	return OK;
}

void	DialogTextBox::reactCharactersDown(const char* text)
{
	TextField*	textField = dynamic_cast<TextField*> \
		(_buttons.front().get());

	if (!textField->isClicked())
		return;

	textField->add(text, getRenderer());

	textField->setSelected(false);
	textField->setHover(false);

	string	error = textField->getLastError();

	if (error.size() > 0)
	{
		Text*	errorText = dynamic_cast<Text*> \
			(_elements.back().get());

		int		limitX = getWidth() * LIMIT_RATIO;
		int		maxWidth = getWidth() - (limitX * 2);

		errorText->update(error, maxWidth, false, getRenderer());
		_elements.back().get()->setVisibility(true);
	}
	else if (_elements.back().get()->isVisible())
		_elements.back().get()->setVisibility(false);
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
