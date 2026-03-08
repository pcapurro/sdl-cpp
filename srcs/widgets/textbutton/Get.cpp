#include "TextButton.hpp"

string  TextButton::getText(void) const
{
    if (!_mainText.has_value())
        return "";

    return _mainText.value().getTextStr();
}
