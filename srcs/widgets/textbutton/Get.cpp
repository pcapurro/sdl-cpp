#include "TextButton.hpp"

string  TextButton::getText(void) const
{
    if (!_mainText)
        return "";

    return _mainText->getTextStr();
}
