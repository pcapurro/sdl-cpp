#include "DialogBoxPreview.hpp"

DialogBoxPreview::DialogBoxPreview(const string& windowTitle, const string& font, const int windowWidth, \
    const int windowHeight, const int colorTheme, const string& title, const bool limit, \
    const string& text, const vector<string>& answers, const string& logoPath, \
    const int logoWidth, const int logoHeight, const bool logoCentering)
{
    _window.emplace(windowTitle, font, windowWidth, windowHeight, colorTheme, title, \
        limit, text, answers, logoPath, logoWidth, logoHeight, logoCentering);
}

int     DialogBoxPreview::routine(void)
{
	int			        value = OK;
	SDL_Event	        lastEvent;

	while (value == OK)
	{
		while (SDL_PollEvent(&lastEvent))
			value = _window->reactEvent(&lastEvent);

		_window->render();
		_window->refreshDisplay();

		SDL_Delay(16);
	}

    return value;
}
