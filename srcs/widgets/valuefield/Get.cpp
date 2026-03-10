#include "ValueField.hpp"

string  ValueField::getLastError(void)
{
    return std::move(_lastError);
}

string  ValueField::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText->getTextStr();
}
