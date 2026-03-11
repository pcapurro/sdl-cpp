#include "ValueField.hpp"

string  ValueField::getLastError(void)
{
    return _lastError;
}

int     ValueField::getValue(void) const
{
    int value = 0;

    if (_mainText.has_value())
        value = std::atoi(_mainText->getTextStr().c_str());

    return value;
}
