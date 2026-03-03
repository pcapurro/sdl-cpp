#include "Element.hpp"

Element::Element(const Properties& properties, const Style& style, \
	const Settings& settings, const State& state) noexcept : \
		_properties(properties), _style(style), _state(state)
{
	;
}

bool	Element::isAbove(const int mouseX, const int mouseY) const noexcept
{
	return _properties.isAbove(mouseX, mouseY);
}

bool	Element::isInside(const int elementX, const int elementY, \
	const int elementWidth, const int elementHeight) const noexcept
{
	return _properties.isInside(elementX, elementY, \
		elementWidth, elementHeight);
}

void	Element::setX(const int x) noexcept
{
	_properties.x = x;
}

void	Element::setY(const int y) noexcept
{
	_properties.y = y;
}

void	Element::setWidth(const int width) noexcept
{
	_properties.width = width;
}

void	Element::setHeight(const int height) noexcept
{
	_properties.height = height;
}

void	Element::setOpacity(const uint8_t opacity) noexcept
{
	_style.globalOpacity = opacity;

	_style.mainColor.a = opacity;
	_style.borderColor.a = opacity;
	_style.selectColor.a = opacity;
}

void	Element::setClick(const bool click) noexcept
{
	_state.click = click;
}

void	Element::setSelected(const bool select) noexcept
{
	if (!isSelectPossible())
		return;

	_state.select = select;
}

void	Element::setSelectType(const int selectType) noexcept
{
	if (!isSelectPossible())
		return;

	_settings.selectType = selectType;
}

void	Element::setSelectColor(const Color& color) noexcept
{
	if (!isSelectPossible())
		return;

	_style.selectColor = color;
}

void	Element::setHighlight(const bool highlight) noexcept
{
	if (!isHighlightPossible())
		return;

	_state.highlight = highlight;
}

void	Element::setHover(const bool hover) noexcept
{
	if (!isHoverPossible())
		return;

	_state.hover = hover;
}

void	Element::setHoverCursor(const int cursor) noexcept
{
	if (!isHoverPossible())
		return;

	_settings.hoverCursor = cursor;
}

void	Element::setVisibility(const bool visibility) noexcept
{
	_state.visibility = visibility;
}

void	Element::enableSelect(void) noexcept
{
	_settings.select = true;
}

void	Element::disableSelect(void) noexcept
{
	_settings.select = false;
}

void	Element::enableHover(void) noexcept
{
	_settings.hover = true;
}

void	Element::disableHover(void) noexcept
{
	_settings.hover = false;
}

void	Element::enableHighlight(void) noexcept
{
	_settings.highlight = true;
}

void	Element::disableHighlight(void) noexcept
{
	_settings.highlight = false;
}

int		Element::getX(void) const noexcept
{
	return _properties.x;
}

int		Element::getY(void) const noexcept
{
	return _properties.y;
}

int		Element::getWidth(void) const noexcept
{
	return _properties.width;
}

int		Element::getHeight(void) const noexcept
{
	return _properties.height;
}

uint8_t		Element::getOpacity(void) const noexcept
{
	return _style.globalOpacity;
}

bool	Element::getClick(void) const noexcept
{
	return _state.click;
}

bool	Element::isSelectPossible(void) const noexcept
{
	return _settings.select;
}

bool	Element::isSelected(void) const noexcept
{
	return _state.select;
}

int		Element::getSelectType(void) const noexcept
{
	return _settings.selectType;
}

Color	Element::getSelectColor(void) const noexcept
{
	return _style.selectColor;
}

bool	Element::isHighlightPossible(void) const noexcept
{
	return _settings.highlight;
}

bool	Element::isHighlighted(void) const noexcept
{
	return _state.highlight;
}

bool	Element::isHoverPossible(void) const noexcept
{
	return _settings.hover;
}

bool	Element::isHover(void) const noexcept
{
	return _state.hover;
}

int		Element::getHoverCursor(void) const noexcept
{
	return _settings.hoverCursor;
}

bool	Element::getVisibility(void) const noexcept
{
	return _state.visibility;
}
