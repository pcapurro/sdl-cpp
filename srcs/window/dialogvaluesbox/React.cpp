#include "DialogValuesBox.hpp"

void	DialogValuesBox::reactError(void)
{
	ValueField*		downField = dynamic_cast<ValueField*>(_downField.get());

	vector<Text*>	errorsPtr;
	vector<string>	errorsText;

	errorsPtr.emplace_back(_downError.get());
	errorsText.emplace_back(downField->getLastError());

	if (_upField)
	{
		ValueField*		upField = dynamic_cast<ValueField*>(_upField.get());

		errorsPtr.emplace_back(_upError.get());
		errorsText.emplace_back(upField->getLastError());
	}

	int		limitX = getWidth() * LIMIT_RATIO;
	int		maxWidth = getWidth() - (limitX * 2);

	for (size_t i = 0; i < errorsPtr.size(); i++)
	{
		if (!errorsPtr[i])
			continue;

		if (errorsText[i].size() > 0)
		{
			errorsPtr[i]->update(errorsText[i], maxWidth, false, getRenderer());
			errorsPtr[i]->setVisibility(true);
		}
		else
			errorsPtr[i]->setVisibility(false);
	}
}

void	DialogValuesBox::reactMouseMotion(const int x, const int y)
{
	bool				isAbove = false;
	SDL_Renderer*		renderer = getRenderer();
	vector<Element*>	buttons = \
		{ _okButton.get(), _downField.get() };

	if (_upField)
		buttons.push_back(_upField.get());

	for (auto& button : buttons)
	{
		if (button->isAbove(x, y))
		{
			button->onMouseHover(x, y, renderer);
			SDL_SetCursor(getCursor(button->getHoverCursor()));

			isAbove = true;
		}
		else
			button->onMouseHoverOutside(renderer);
	}

    if (!isAbove)
        SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

int		DialogValuesBox::reactMouseButtonUp(const int x, const int y)
{
	SDL_Renderer*		renderer = getRenderer();
	vector<Element*>	buttons = \
		{ _okButton.get(), _downField.get() };

	if (_upField)
		buttons.push_back(_upField.get());

	for (auto& button : buttons)
	{
		if (button->isAbove(x, y))
		{
			button->onMouseUp(x, y, renderer);

			ValueField*	textField = dynamic_cast \
				<ValueField*>(button);

			if (!textField)
				return RETURN;
		}
		else
			button->onMouseUpOutside(renderer);
	}

	return OK;
}

void	DialogValuesBox::reactMouseButtonDown(const int x, const int y, \
	const int clicks)
{
	SDL_Renderer*		renderer = getRenderer();
	vector<Element*>	buttons = \
		{ _okButton.get(), _downField.get() };

	if (_upField)
		buttons.push_back(_upField.get());

	for (auto& button : buttons)
	{
		if (button->isAbove(x, y))
		{
			if (clicks > 1)
				button->onMouseDownDouble(x, y, renderer);
			else
				button->onMouseDown(x, y, renderer);
		}
		else
			button->onMouseDownOutside(renderer);
	}
}

int		DialogValuesBox::reactKeyButtonDown(const int key)
{
	vector<Element*>	buttons = \
		{ _okButton.get(), _downField.get() };

	if (_upField)
		buttons.push_back(_upField.get());

	for (const auto& button : buttons)
		button->onButtonDown(key, getRenderer());

	if (key == SDLK_TAB)
	{
		buttons[_tabCursor]->setClick(false);
		buttons[_tabCursor]->setSelected(false);
		buttons[_tabCursor]->setHover(false);

		if (_tabCursor < buttons.size() - 1)
			_tabCursor++;
		else
			_tabCursor = 0;

		buttons[_tabCursor]->setHover(true);
	}
	else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
	{
		buttons[_tabCursor]->onMouseDown();

		TextButton*	textButton = dynamic_cast \
			<TextButton*>(buttons[_tabCursor]);

		if (textButton)
			return RETURN;
	}
	
	reactError();

	return OK;
}

void	DialogValuesBox::reactCharactersDown(const char* text)
{
	SDL_Renderer*		renderer = getRenderer();
	ValueField*			downField = dynamic_cast<ValueField*>(_downField.get());

	if (_upField)
	{
		ValueField*	upField = dynamic_cast<ValueField*>(_upField.get());

		if (upField && upField->isClicked())
			upField->add(text, renderer);
	}

	if (downField && _downField->isClicked())
		downField->add(text, renderer);

	reactError();
}

int		DialogValuesBox::reactEvent(SDL_Event* event, const int x, const int y)
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
