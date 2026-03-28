#include "DialogValuesBox.hpp"

bool    DialogValuesBox::error(void) const noexcept
{
    return _error;
}

vector<int>  DialogValuesBox::getFinalValues(void)
{
    _finalValues.clear();

    int     upValue = 0;
    int     downValue = 0;

    if (_upField)
        upValue = _upField->getValue();

    if (_downField)
        downValue = _downField->getValue();

    _finalValues.push_back(upValue);
    _finalValues.push_back(downValue);

    return _finalValues;
}
