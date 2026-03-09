#include "TextField.hpp"

string  TextField::getLastError(void)
{
    return std::move(_lastError);
}

string  TextField::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText->getTextStr();
}
