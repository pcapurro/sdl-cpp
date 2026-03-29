#include "ValueField.hpp"

bool    ValueField::empty(void) const
{
    if (_mainText)
        return false;

    return true;
}

string  ValueField::getLastError(void)
{
    return _lastError;
}

int     ValueField::getValue(void) const
{
    int value = 0;

    if (_mainText)
        value = std::atoi(_mainText->getTextStr().c_str());

    return value;
}
