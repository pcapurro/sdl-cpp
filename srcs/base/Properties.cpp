#include "Properties.hpp"

bool    Properties::isAbove(const int mouseX, const int mouseY) const noexcept
{
	if (mouseX >= x && mouseX <= x + width)
	{
		if (mouseY >= y && mouseY <= y + height)
			return true;
	}

	return false;
}

bool    Properties::isInside(const int elementX, const int elementY, \
    const int elementWidth, const int elementHeight) const noexcept
{
    if (elementX >= x && elementX + elementWidth <= x + width)
    {
        if (elementY >= y && elementY + elementHeight <= y + height)
            return true;
    }

    return false;
}
