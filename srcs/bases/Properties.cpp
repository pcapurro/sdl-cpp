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
