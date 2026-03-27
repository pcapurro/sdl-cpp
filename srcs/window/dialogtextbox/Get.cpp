#include "DialogTextBox.hpp"

string  DialogTextBox::getFinalAnswer(void)
{
	_finalAnswer.clear();

	TextField*  textField = dynamic_cast<TextField*> \
		(_buttons.front().get());

	_finalAnswer = textField->getText();

	return _finalAnswer;
}
