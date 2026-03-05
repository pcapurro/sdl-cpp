#include "DialogTextBox.hpp"

DialogTextBox::DialogTextBox(const string& name, const int width, const int height, \
	const string& fontPath, const int displayMode, const string& titleText, \
	const bool titleLimit, const string& text, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool logoCentered) : \
		Window(name, width, height), \
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

    auto textField = std::make_unique<TextField>(Properties{cursorX, 0, 0, \
		((textSize * 2) / 10) * 10}, getBackgroundColor(), getWriteColor());

	auto mainButton = std::make_unique<TextButton>(Properties{cursorX, 0, ((textSize * 5) / 10) * 10, \
		((textSize * 2) / 10) * 10}, getBackgroundColor(), "OK", textSize, \
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

	if (event.type == SDL_QUIT \
		|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		return END;

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
	bool	isAbove = false;

	for (auto& button : _buttons)
	{
		if (button.get()->isAbove(x, y) == true)
		{
			isAbove = true;

			button.get()->setHover(true);

			SDL_SetCursor(getCursor(button.get()->getHoverCursor()));
		}
		else
			button.get()->setHover(false);
	}

    if (!isAbove)
        SDL_SetCursor(getCursor(SDL_SYSTEM_CURSOR_ARROW));
}

void	DialogTextBox::reactMouseButtonDown(const int x, const int y)
{
	bool	isAbove = false;

	for (auto& button : _buttons)
	{
		if (button.get()->isAbove(x, y))
		{
			button.get()->setClick(true);
			button.get()->setSelected(true);

			isAbove = true;
		}
	}

    if (!isAbove)
    {
		for (auto& button : _buttons)
			button.get()->setClick(false), button.get()->setSelected(false);
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

		string	text = textField->getText();

		if (textField->isSelected() || text.size() <= 1)
			textField->clear();
		else if (key != SDLK_DELETE)
		{
			text.pop_back();

			textField->update(text, _fontPath, \
				getWriteColor(), getRenderer());
		}
	}

    else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
		return DEFAULT;

	return OK;
}

void	DialogTextBox::reactCharactersDown(const char* text)
{
	TextField*	textField = dynamic_cast<TextField*> \
		(_buttons.front().get());

	if (!textField->isClicked())
		return;

	string		newText;

	if (!textField->isSelected())
		newText += textField->getText();

	newText += text;

	textField->update(newText, _fontPath, \
		getWriteColor(), getRenderer());

	textField->setSelected(false);
}

int		DialogTextBox::reactEvent(SDL_Event* event, const int x, const int y)
{
	int		value = OK;

	if (event->type == SDL_MOUSEMOTION)
		reactMouseMotion(x, y);

	else if (event->type == SDL_MOUSEBUTTONDOWN)
		reactMouseButtonDown(x, y);

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
