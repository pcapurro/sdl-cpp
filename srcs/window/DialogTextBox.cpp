#include "DialogTextBox.hpp"

DialogTextBox::DialogTextBox(const string& name, const int width, const int height, \
	const string& fontPath, const int displayMode, const string& titleText, \
	const bool titleLimit, const string& text, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool logoCentered) : \
		Window(name, width, height), \
		_tabCursor(0), \
		_fontPath(fontPath)
{
	int		limitX = width * LIMIT_RATIO;
	int		limitY = height * LIMIT_RATIO;

	int		cursorX = limitX;
	int		cursorY = limitY;

	int		maxWidth = width - (limitX * 2);

	if (displayMode == DARK_MODE)
		setWriteColor(WHITE), setBackgroundColor(BLACK);
	else
		setWriteColor(BLACK), setBackgroundColor(WHITE);

	_elements.reserve(6);

	if (logoPath.size() > 0)
	{
		addLogo(cursorX, cursorY, logoPath, logoWidth, \
			logoHeight, logoCentered);

		if (titleText.size() == 0 || logoCentered)
			cursorY += _elements.back().get()->getHeight() + limitY;
	}

	if (titleText.size() > 0)
	{
		if (_elements.size() > 0 && !logoCentered)
			cursorX += _elements.back().get()->getWidth() + limitX;

		maxWidth = width - cursorX - limitX;

		addTitleText(cursorX, cursorY, titleText, fontPath, maxWidth);

		cursorY += _elements.back().get()->getHeight() + limitY;
	}

	if (titleLimit)
	{
		addTitleLimit(cursorX, cursorY, maxWidth);
		cursorY += _elements.back().get()->getHeight() + limitY;
	}

	if (logoPath.size() > 0)
	{
		int		logoBottomY = _elements.front()->getHeight() + limitY;

		cursorY = std::max(logoBottomY, cursorY);
		cursorY += limitY;
	}
	
	cursorX = limitX;

	maxWidth = width - (limitX * 2);

	addText(cursorX, cursorY, text, fontPath, maxWidth);

    addTextField(cursorX, fontPath);

	addErrorText(cursorX, fontPath);
}

void	DialogTextBox::addLogo(const int cursorX, const int cursorY, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool centered)
{
	Properties		logoProperties;

	if (!centered)
		logoProperties.x = cursorX;

	logoProperties.y = cursorY;

	logoProperties.width = logoWidth;
	logoProperties.height = logoHeight;

	auto	image = std::make_unique<Image>(logoProperties, \
		logoPath.c_str(), getRenderer());

	if (centered)
		image.get()->setX(getWidth() / 2 - (image.get()->getWidth() / 2), getRenderer());

	_elements.emplace_back(std::move(image));
}

void	DialogTextBox::addTitleText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		titleSize = getHeight() * TITLE_RATIO;

	unique_ptr<Text>	textElement = std::make_unique<Text>(cursorX, cursorY, \
		text.c_str(), titleSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void	DialogTextBox::addTitleLimit(const int cursorX, const int cursorY, const int width)
{
	Properties		limitFrame;

	limitFrame.x = cursorX;
	limitFrame.y = cursorY;

	limitFrame.width = width;
	limitFrame.height = LIMIT_HEIGHT;

	auto	shapeElement = std::make_unique<Shape>(limitFrame, getWriteColor());

	_elements.emplace_back(std::move(shapeElement));
}

void	DialogTextBox::addText(const int cursorX, const int cursorY, const string& text, \
	const string& fontPath, const int maxWidth)
{
	int		textSize = getHeight() * TEXT_RATIO;

	auto	textElement = std::make_unique<Text>(cursorX, cursorY, text.c_str(), \
		textSize, getWriteColor(), fontPath, getRenderer(), maxWidth);

	_elements.emplace_back(std::move(textElement));
}

void    DialogTextBox::addTextField(const int cursorX, const string& fontPath)
{
    int		textSize = getHeight() * TEXT_RATIO;
	int		limitX = getWidth() * LIMIT_RATIO;
	int		limitY = getHeight() * LIMIT_RATIO;

	int		globalWidth = ((textSize * 5) / 10) * 10;
	int		globalHeight = ((textSize * 2) / 10) * 10;

	int		textLimit = 30;

    auto textField = std::make_unique<TextField>(Properties{cursorX, 0, 0, globalHeight}, \
		getBackgroundColor(), getWriteColor(), _fontPath, getWriteColor(), textLimit);

	auto mainButton = std::make_unique<TextButton>(Properties{cursorX, 0, globalWidth, \
		globalHeight}, getBackgroundColor(), "OK", textSize, \
		getWriteColor(), fontPath, getRenderer());

	TextField*	text = textField.get();
	TextButton*	button = mainButton.get();

	text->setWidth(getWidth() - (limitX * 3) - button->getWidth(), getRenderer());
	text->setY(getHeight() - limitY - button->getHeight(), getRenderer());

	button->setX(text->getX() + text->getWidth() + limitX, getRenderer());
	button->setY(getHeight() - limitY - button->getHeight(), getRenderer());

	button->setSettings(false, NONE, true, SDL_SYSTEM_CURSOR_HAND, true, true);
	text->setSettings(true, HIGHLIGHT_SELECT, true, SDL_SYSTEM_CURSOR_IBEAM, false, false);

	Color	color = BLUE;

	color.a = HIGHLIGHT_OPACITY;
	text->setSelectColor(color);

	_buttons.emplace_back(std::move(textField));
	_buttons.emplace_back(std::move(mainButton));
}

void	DialogTextBox::addErrorText(const int cursorX, const string& fontPath)
{
	int		limitY = getHeight() * LIMIT_RATIO;
	int		textSize = getHeight() * TEXT_RATIO;

	Color	errorColor = RED;

	auto	textElement = std::make_unique<Text>(cursorX, 0, "No error", \
		textSize, errorColor, fontPath, getRenderer());

	int		y = _buttons.front().get()->getY() - (limitY / 2);

	textElement.get()->setY(y - textElement.get()->getHeight(), getRenderer());
	textElement.get()->setVisibility(false);

	_elements.emplace_back(std::move(textElement));
}

int     DialogTextBox::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value != OK)
		{
			TextField*	textField = dynamic_cast<TextField*> \
				(_buttons.front().get());

			_finalAnswer = textField->getText();
			
            return value;
		}
    }

    return OK;
}

int     DialogTextBox::waitForEvent(void)
{
	int			value = OK;
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_WaitEvent(&event) == 0)
	{
		throw std::runtime_error("SDL failed listening to events: " + \
			string(SDL_GetError()));
	}

	if (event.type == SDL_QUIT)
		return END;

	if (event.type == SDL_KEYDOWN)
	{
		int	key = event.key.keysym.sym;

		if (key == SDLK_ESCAPE)
			return END;
	}

	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN \
		|| event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.type == SDL_MOUSEMOTION)
			x = event.motion.x, y = event.motion.y;
		else if (event.type == SDL_MOUSEBUTTONDOWN \
			|| event.type == SDL_MOUSEBUTTONUP)
			x = event.button.x, y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return OK;
		else
			setX(x), setY(y);

		value = reactEvent(&event, x, y);
	}
	else
		value = reactEvent(&event);

	return value;
}

void	DialogTextBox::render(void)
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

void	DialogTextBox::reactMouseMotion(const int x, const int y)
{
	bool		isAbove = false;
	Element*	element = nullptr;

	for (auto& button : _buttons)
	{
		element = button.get();

		if (element->isAbove(x, y) == true)
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

		if (element->isAbove(x, y) == true)
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
	bool	isAbove = false;

	Element*	element = nullptr;

	for (auto& button : _buttons)
	{
		element = button.get();

		if (element->isAbove(x, y) == true)
		{
			if (clicks > 1)
				element->onMouseDownDouble();
			else
				element->onMouseDown(x, y);
			
			isAbove = true;
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
	else if (_elements.back().get()->isVisible() == true)
		_elements.back().get()->setVisibility(false);
}

void	DialogTextBox::reactTextFieldErrors(void)
{
	;
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

string  DialogTextBox::getFinalAnswer(void) const
{
    return _finalAnswer;
}
