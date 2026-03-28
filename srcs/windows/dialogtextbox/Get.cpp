#include "DialogTextBox.hpp"

bool	DialogTextBox::error(void) const noexcept
{
	return _error;
}

string  DialogTextBox::getFinalAnswer(void)
{
	_finalAnswer.clear();

	TextField*  textField = dynamic_cast<TextField*> \
		(_buttons.front().get());

	_finalAnswer = textField->getText();

	return _finalAnswer;
}
