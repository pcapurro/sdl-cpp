#include "DialogBox.hpp"

void	DialogBox::reactMouseMotion(const int x, const int y)
{
	bool	isAbove = false;

	for (auto& button : _buttons)
	{
		if (button.get()->isAbove(x, y) == true)
		{
			isAbove = true;

			button.get()->onMouseHover();
			SDL_SetCursor(getCursor(button.get()->getHoverCursor()));
		}
		else
			button.get()->onMouseHoverOutside();
	}

	if (!isAbove)
		SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

int		DialogBox::reactMouseButtonUp(const int x, const int y)
{
	for (auto& button : _buttons)
	{
		if (button->isAbove(x, y) && button->isFocused())
		{
			for (size_t i = 0; i < _textButtons.size(); i++)
			{
				if (_textButtons[i] == button->getText())
					return i + 1;
			}
		}
		else
			button->onMouseUpOutside();
	}

	return OK;
}

void	DialogBox::reactMouseButtonDown(const int x, const int y)
{
	for (auto& button : _buttons)
		button->onMouseDown(x, y);
}

int		DialogBox::reactKeyButtonDown(const int key)
{
	if (key == SDLK_TAB)
	{
		_buttons[_tabCursor].get()->setHighlight(false);

		if (_tabCursor < _buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		_buttons[_tabCursor].get()->setHighlight(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
		return _tabCursor + 1;

	return OK;
}

int		DialogBox::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);

	else if (event->type == SDL_MOUSEBUTTONDOWN \
		&& event->button.button == SDL_BUTTON_LEFT)
		reactMouseButtonDown(x, y);

	else if (event->type == SDL_MOUSEBUTTONUP \
		&& event->button.button == SDL_BUTTON_LEFT)
		value = reactMouseButtonUp(x, y);

	else if (event->type == SDL_KEYDOWN)
		value = reactKeyButtonDown(event->key.keysym.sym);

	refreshDisplay();

	return value;
}
