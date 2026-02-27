#include "Element.hpp"

Element::Element(const Properties& properties, const Style& style, \
	const State& state) noexcept : \
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
}

void	Element::setClick(const bool click) noexcept
{
	_state.click = click;
}

void	Element::setSelect(const bool select) noexcept
{
	_state.select = select;
}

void	Element::setSelectType(const int selectType) noexcept
{
	_state.selectType = selectType;
}

void	Element::setHighlight(const bool highlight) noexcept
{
	_state.highlight = highlight;
}

void	Element::setVisibility(const bool visibility) noexcept
{
	_state.visibility = visibility;
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

bool	Element::getSelect(void) const noexcept
{
	return _state.select;
}

int		Element::getSelectType(void) const noexcept
{
	return _state.selectType;
}

bool	Element::getHighlight(void) const noexcept
{
	return _state.highlight;
}

bool	Element::getVisibility(void) const noexcept
{
	return _state.visibility;
}
