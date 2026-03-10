#include "DialogValuesBox.hpp"

int     DialogValuesBox::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value != OK)
		{
			ValueField*	upField = dynamic_cast<ValueField*> \
				(_upField.get());

            ValueField*	downField = dynamic_cast<ValueField*> \
				(_downField.get());

            _finalValues.push_back(upField->getValue());
            _finalValues.push_back(downField->getValue());

            return value;
		}
    }

    return OK;
}
