#include "DialogTextBoxPreview.hpp"

DialogTextBoxPreview::DialogTextBoxPreview(const string& windowTitle, const string& font, \
    const int windowWidth, const int windowHeight, const int colorTheme, const string& title, \
    const bool limit, const string& text, const int maxChars, const string& logoPath, \
    const int logoWidth, const int logoHeight, const bool logoCentering)
{
    _window.emplace(windowTitle, font, windowWidth, windowHeight, colorTheme, title, \
        limit, text, maxChars, logoPath, logoWidth, logoHeight, logoCentering);
}

string	DialogTextBoxPreview::getText(void) const
{
	return _text;
}

int     DialogTextBoxPreview::routine(void)
{
	int			        value = OK;
	SDL_Event	        lastEvent;

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			value = _window->reactEvent(&lastEvent);

			if (value == RETURN)
			{
				if (!_window->error())
					_text = _window->getFinalAnswer();
				else
					value = OK;
			}
		}

		_window->render();
		_window->refreshDisplay();

		SDL_Delay(16);
	}

    return value;
}
