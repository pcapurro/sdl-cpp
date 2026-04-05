#include "DialogBox.hpp"

void	DialogBox::reactMouseMotion(const int x, const int y)
{
	bool	isAbove = false;

	for (auto& button : _buttons)
	{
		if (button->isAbove(x, y))
		{
			isAbove = true;

			button->onMouseHover();
			SDL_SetCursor(getCursor(button->getHoverCursor()));
		}
		else
			button->onMouseHoverOutside();
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
			button->onMouseUpOutside(getRenderer());
	}

	return State::Ok;
}

void	DialogBox::reactMouseButtonDown(const int x, const int y)
{
	for (auto& button : _buttons)
		button->onMouseDown(false, x, y);
}

int		DialogBox::reactKeyButtonDown(const int key)
{
	if (key == SDLK_TAB)
	{
		_buttons[_tabCursor]->setHighlight(false);

		if (_tabCursor < _buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		_buttons[_tabCursor]->setHighlight(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
		return _tabCursor + 1;

	return State::Ok;
}

int		DialogBox::reactEvent(SDL_Event* event)
{
	int		value = State::Ok;

	int		x = 0;
	int		y = 0;

	if (event->type == SDL_QUIT \
		|| (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE))
		return State::End;

	if (event->type == SDL_MOUSEMOTION)
		x = event->motion.x, y = event->motion.y;
	else if (event->type == SDL_MOUSEBUTTONDOWN \
		|| event->type == SDL_MOUSEBUTTONUP)
		x = event->button.x, y = event->button.y;

	if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
		return State::Ok;
	else
		setCursorX(x), setCursorY(y);

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

	return value;
}
