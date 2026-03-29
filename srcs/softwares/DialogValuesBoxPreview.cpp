#include "DialogValuesBoxPreview.hpp"

DialogValuesBoxPreview::DialogValuesBoxPreview(const string& windowTitle, const string& font, \
    const int windowWidth, const int windowHeight, const int colorTheme, const string& title, \
    const bool limit, const string& text, const int maxChars, const vector<string>& fieldsTitles, \
    const vector<string>& fieldsUnits, const vector<int>& fieldsMinimums, const vector<int>& fieldsMaximums)
{
    _window.emplace(windowTitle, font, windowWidth, windowHeight, colorTheme, title, \
        limit, text, maxChars, fieldsTitles, fieldsUnits, fieldsMinimums, fieldsMaximums);
}

vector<int>		DialogValuesBoxPreview::getValues(void) const
{
	return _values;
}

int     DialogValuesBoxPreview::routine(void)
{
	int			        value = State::Ok;
	SDL_Event	        lastEvent;

	while (value == State::Ok)
	{
		while (SDL_PollEvent(&lastEvent))
		{
			value = _window->reactEvent(&lastEvent);

			if (value == State::Return)
			{
				if (!_window->error())
					_values = _window->getFinalValues();
				else
					value = State::Ok;
			}
		}

		_window->render();
		_window->refreshDisplay();

		SDL_Delay(16);
	}

    return value;
}
