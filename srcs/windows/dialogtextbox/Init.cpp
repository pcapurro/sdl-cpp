#include "DialogTextBox.hpp"

#include "DialogTextBox.hpp"

DialogTextBox::DialogTextBox(const string& name, const string& fontPath, const int width, \
	const int height, const int displayMode, const string& titleText, \
	const bool titleLimit, const string& text, const int maxText, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool logoCentered) : \
		Window(name, width, height), \
		_fontPath(fontPath)
{
	int		limitX = width * Render::LimitRatio;
	int		limitY = height * Render::LimitRatio;

	int		cursorX = limitX;
	int		cursorY = limitY;

	int		maxWidth = width - (limitX * 2);

	if (displayMode == Window::DarkMode)
		setWriteColor(Color::White), setBackgroundColor(Color::Black);
	else
		setWriteColor(Color::Black), setBackgroundColor(Color::White);

	_elements.reserve(7);

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

    addTextField(cursorX, fontPath, maxText);
	addErrorText(cursorX, fontPath);
}
