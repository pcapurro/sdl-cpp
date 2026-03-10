#include "DialogValuesBox.hpp"

DialogValuesBox::DialogValuesBox(const string& name, const string& fontPath, const int width, \
	const int height, const int displayMode, const string& titleText, \
	const bool titleLimit, const string& text, const int maxText, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool logoCentered) : \
		Window(name, width, height), \
		_fontPath(fontPath)
{
	int		limitX = width * LIMIT_RATIO;
	int		limitY = height * LIMIT_RATIO;

	int		cursorX = limitX;
	int		cursorY = limitY;

	int		maxWidth = width - (limitX * 2);

	if (displayMode == DARK_MODE)
		setWriteColor(WHITE), setBackgroundColor(BLACK);
	else
		setWriteColor(BLACK), setBackgroundColor(WHITE);

	_elements.reserve(10);
	_finalValues.reserve(2);

	if (logoPath.size() > 0)
	{
		addLogo(cursorX, cursorY, logoPath, logoWidth, \
			logoHeight, logoCentered);

		if (titleText.size() == 0 || logoCentered)
			cursorY += _elements.back()->getHeight() + limitY;
	}

	if (titleText.size() > 0)
	{
		if (_elements.size() > 0 && !logoCentered)
			cursorX += _elements.back()->getWidth() + limitX;

		maxWidth = width - cursorX - limitX;

		addTitleText(cursorX, cursorY, titleText, fontPath, maxWidth);

		cursorY += _elements.back()->getHeight() + limitY;
	}

	if (titleLimit)
	{
		addTitleLimit(cursorX, cursorY, maxWidth);
		cursorY += _elements.back()->getHeight() + limitY;
	}

	if (logoPath.size() > 0)
	{
		int		logoBottomY = _elements.front()->getHeight() + limitY;

		cursorY = std::max(logoBottomY, cursorY);
		cursorY += limitY;
	}
	
	cursorX = limitX;

	maxWidth = width - (limitX * 2);

	addText(cursorX, cursorY, text, fontPath, maxWidth);

	addFieldsTitles(fontPath);
	addFields(fontPath, maxText);
	addFieldsUnits(fontPath);
	addFieldsErrors(fontPath);

	addButton(fontPath);
}
