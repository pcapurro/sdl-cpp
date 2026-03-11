#include "ValueField.hpp"

void    ValueField::validateValue(void)
{
    if (!_mainText.has_value())
        return;

    string  text = _mainText->getTextStr();

    for (size_t i = 0; i < text.size(); i++)
    {
        if (text[i] == '-')
        {
            if (i > 0)
            {
                _lastError = "invalid value";
                return;
            }
        }
        else if (!std::isdigit(text[i]))
        {
            _lastError = "invalid value";
            return;
        }
    }

    int value = std::atoi(_mainText.value(). \
        getTextStr().c_str());

    if (value > _maxValue)
    {
        _lastError = "max value is " + std::to_string(_maxValue);
        return;
    }
    else if (value < _minValue)
    {
        _lastError = "min value is " + std::to_string(_minValue);
        return;
    }

    _lastError.clear();
}
