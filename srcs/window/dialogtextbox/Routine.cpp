#include "DialogTextBox.hpp"

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
