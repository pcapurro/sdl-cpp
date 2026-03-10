#include "ValueField.hpp"

bool    ValueField::validateValue(const string& text)
{
    _lastError.clear();

    if (text.size() > _maxChar
        || (_mainText.has_value() && _mainText->getTextStr().size() + text.size() > _maxChar))
    {
        _lastError = "Value has reached the limit (" \
            + std::to_string(_maxChar) + string(").");
    }

    for (size_t i = 0; i < text.size() && _lastError.size() == 0; i++)
    {
        if (text[i] == '-')
        {
            if (_mainText.has_value() || i > 0)
                _lastError = "Invalid value.";
        }
        else if (!std::isdigit(text[i]))
            _lastError = "Invalid value.";
    }

    if (_lastError.size() > 0)
        return false;
    
    return true;
}
