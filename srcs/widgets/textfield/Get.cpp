#include "TextField.hpp"

bool    TextField::empty(void) const
{
    if (_mainText)
        return false;

    return true;
}

string  TextField::getLastError(void)
{
    return std::move(_lastError);
}

string  TextField::getText(void) const
{
    if (!_mainText)
        return "";

    return _mainText->getTextStr();
}
