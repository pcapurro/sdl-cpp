#include "Element.hpp"

Element::Element(const Properties& properties, const Style& style, \
	const Settings& settings, const State& state) noexcept : \
		_properties(properties), \
		_style(style), \
		_settings(settings), \
		_state(state)
{
	;
}

bool	Element::isAbove(const int mouseX, const int mouseY) const noexcept
{
	return _properties.isAbove(mouseX, mouseY);
}

void	Element::setX(const int x, SDL_Renderer* renderer) noexcept
{
	_properties.x = x;

	onPropertiesChanged(renderer);
}

void	Element::setY(const int y, SDL_Renderer* renderer) noexcept
{
	_properties.y = y;

	onPropertiesChanged(renderer);
}

void	Element::setWidth(const int width, SDL_Renderer* renderer) noexcept
{
	_properties.width = width;

	onPropertiesChanged(renderer);
}

void	Element::setHeight(const int height, SDL_Renderer* renderer) noexcept
{
	_properties.height = height;

	onPropertiesChanged(renderer);
}

void	Element::setOpacity(const uint8_t opacity) noexcept
{
	_style.globalOpacity = opacity;

	_style.mainColor.a = opacity;
	_style.selectColor.a = opacity;

	onStyleChanged();
}

void	Element::setMainColor(const Color& color) noexcept
{
	_style.mainColor.r = color.r;
	_style.mainColor.g = color.g;
	_style.mainColor.b = color.b;

	onStyleChanged();
}

void	Element::setSelectColor(const Color& color) noexcept
{
	if (!isSelectPossible())
		return;

	_style.selectColor.r = color.r;
	_style.selectColor.g = color.g;
	_style.selectColor.b = color.b;

	onStyleChanged();
}

void	Element::setClick(const bool click) noexcept
{
	_state.click = click;

	onStateChanged();
}

void	Element::setSelected(const bool select) noexcept
{
	if (!isSelectPossible())
		return;

	_state.select = select;

	onStateChanged();
}

void	Element::setSelectType(const int selectType) noexcept
{
	if (!isSelectPossible())
		return;

	_settings.selectType = selectType;

	onSettingsChanged();
}

void	Element::setHighlight(const bool highlight) noexcept
{
	if (!isHighlightPossible())
		return;

	_state.highlight = highlight;

	onStateChanged();
}

void	Element::setFocus(const bool focus) noexcept
{
	if (!isFocusPossible())
		return;

	_state.focus = focus;

	onStateChanged();
}

void	Element::setHover(const bool hover) noexcept
{
	if (!isHoverPossible())
		return;

	_state.hover = hover;

	onStateChanged();
}

void	Element::setHoverCursor(const int cursor) noexcept
{
	if (!isHoverPossible())
		return;

	_settings.hoverCursor = cursor;

	onSettingsChanged();
}

void	Element::setVisibility(const bool visibility) noexcept
{
	_state.visibility = visibility;

	onStateChanged();
}

void	Element::enableSelect(void) noexcept
{
	_settings.select = true;

	onSettingsChanged();
}

void	Element::disableSelect(void) noexcept
{
	_settings.select = false;

	onSettingsChanged();
}

void	Element::enableHover(void) noexcept
{
	_settings.hover = true;

	onSettingsChanged();
}

void	Element::disableHover(void) noexcept
{
	_settings.hover = false;

	onSettingsChanged();
}

void	Element::enableHighlight(void) noexcept
{
	_settings.highlight = true;

	onSettingsChanged();
}

void	Element::disableHighlight(void) noexcept
{
	_settings.highlight = false;

	onSettingsChanged();
}

void	Element::enableFocus(void) noexcept
{
	_settings.focus = true;

	onSettingsChanged();
}

void	Element::disableFocus(void) noexcept
{
	_settings.focus = false;

	onSettingsChanged();
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

Color		Element::getMainColor(void) const noexcept
{
	return _style.mainColor;
}

Color		Element::getSelectColor(void) const noexcept
{
	return _style.selectColor;
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

bool	Element::isHighlightPossible(void) const noexcept
{
	return _settings.highlight;
}

bool	Element::isHighlighted(void) const noexcept
{
	return _state.highlight;
}

bool	Element::isFocusPossible(void) const noexcept
{
	return _settings.focus;
}

bool	Element::isFocused(void) const noexcept
{
	return _state.focus;
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
