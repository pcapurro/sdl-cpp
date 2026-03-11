#include "DialogValuesBox.hpp"

DialogValuesBox::DialogValuesBox(const string& name, const string& fontPath, const int width, \
	const int height, const int displayMode, const string& titleText, const bool titleLimit, \
	const string& text, const int maxText, const vector<string>& titles, const vector<string>& units, \
	const vector<int>& minValues, const vector<int>& maxValues, const string& logoPath, \
	const int logoWidth, const int logoHeight, const bool logoCentered) : \
		Window(name, width, height), \
		_fontPath(fontPath), \
		_titles(titles), \
		_units(units), \
		_minValues(minValues), \
		_maxValues(maxValues)
{
	if (_titles.size() == 0 || _units.size() == 0 || _minValues.size() == 0 || _maxValues.size() == 0)
		throw std::runtime_error("Invalid fields number (min: 1)");

	if (_titles.size() > 2 || _units.size() > 2 || _minValues.size() > 2 || _maxValues.size() > 2)
		throw std::runtime_error("Invalid fields number (max: 2)");

	if (_titles.size() != _units.size() || _units.size() != minValues.size() || minValues.size() != maxValues.size())
		throw std::runtime_error("Paramaters vectors size mismatch");

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
