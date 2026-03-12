#include "DialogValuesBox.hpp"

int     DialogValuesBox::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value == OK \
            || (value == RETURN && _error))
            continue;

        _finalValues.push_back(_upField ? _upField->getValue() : 0);
        _finalValues.push_back(_downField ? _downField->getValue() : 0);

        return value;
    }

    return OK;
}
