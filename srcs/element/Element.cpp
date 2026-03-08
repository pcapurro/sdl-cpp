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

void	Element::setSettings(const bool select, const int selectType, \
    const bool hover, const int hoverCursor, const bool highlight, const bool focus) noexcept
{
    select ? enableSelect() : disableSelect();
    if (select && selectType != DEFAULT && selectType != NONE)
        setSelectType(selectType);

    hover ? enableHover() : disableHover();
    if (hover && hoverCursor != DEFAULT && hoverCursor != NONE)
        setHoverCursor(hoverCursor);

    highlight ? enableHighlight() : disableHighlight();
    focus ? enableFocus() : disableFocus();
}

bool	Element::isAbove(const int mouseX, const int mouseY) const noexcept
{
	return _properties.isAbove(mouseX, mouseY);
}

void	Element::setX(const int x, SDL_Renderer* renderer, const bool propagation) noexcept
{
	_properties.x = x;

	if (propagation && renderer)
		onPropertiesChanged(renderer);
}

void	Element::setY(const int y, SDL_Renderer* renderer, const bool propagation) noexcept
{
	_properties.y = y;

	if (propagation && renderer)
		onPropertiesChanged(renderer);
}

void	Element::setWidth(const int width, SDL_Renderer* renderer, const bool propagation) noexcept
{
	_properties.width = width;

	if (propagation && renderer)
		onPropertiesChanged(renderer);
}

void	Element::setHeight(const int height, SDL_Renderer* renderer, const bool propagation) noexcept
{
	_properties.height = height;

	if (propagation && renderer)
		onPropertiesChanged(renderer);
}

void	Element::setMainColor(const Color& color, const bool propagation) noexcept
{
	_style.mainColor = color;

	if (propagation)
		onStyleChanged();
}

void	Element::setSelectColor(const Color& color, const bool propagation) noexcept
{
	if (!isSelectPossible())
		return;

	_style.selectColor = color;

	if (propagation)
		onStyleChanged();
}

void	Element::setClick(const bool click, const bool propagation) noexcept
{
	_state.click = click;

	if (propagation)
		onStateChanged();
}

void	Element::setSelected(const bool select, const bool propagation) noexcept
{
	if (!isSelectPossible())
		return;

	_state.select = select;

	if (propagation)
		onStateChanged();
}

void	Element::setSelectType(const int selectType, const bool propagation) noexcept
{
	if (!isSelectPossible())
		return;

	_settings.selectType = selectType;

	if (propagation)
		onSettingsChanged();
}

void	Element::setHighlight(const bool highlight, const bool propagation) noexcept
{
	if (!isHighlightPossible())
		return;

	_state.highlight = highlight;

	if (propagation)
		onStateChanged();
}

void	Element::setFocus(const bool focus, const bool propagation) noexcept
{
	if (!isFocusPossible())
		return;

	_state.focus = focus;

	if (propagation)
		onStateChanged();
}

void	Element::setHover(const bool hover, const bool propagation) noexcept
{
	if (!isHoverPossible())
		return;

	_state.hover = hover;

	if (propagation)
		onStateChanged();
}

void	Element::setHoverCursor(const int cursor, const bool propagation) noexcept
{
	if (!isHoverPossible())
		return;

	_settings.hoverCursor = cursor;

	if (propagation)
		onSettingsChanged();
}

void	Element::setVisibility(const bool visibility, const bool propagation) noexcept
{
	_state.visibility = visibility;

	if (propagation)
		onStateChanged();
}

void	Element::enableSelect(const bool propagation) noexcept
{
	_settings.select = true;

	if (propagation)
		onSettingsChanged();
}

void	Element::disableSelect(const bool propagation) noexcept
{
	_settings.select = false;

	if (propagation)
		onSettingsChanged();
}

void	Element::enableHover(const bool propagation) noexcept
{
	_settings.hover = true;

	if (propagation)
		onSettingsChanged();
}

void	Element::disableHover(const bool propagation) noexcept
{
	_settings.hover = false;

	if (propagation)
		onSettingsChanged();
}

void	Element::enableHighlight(const bool propagation) noexcept
{
	_settings.highlight = true;

	if (propagation)
		onSettingsChanged();
}

void	Element::disableHighlight(const bool propagation) noexcept
{
	_settings.highlight = false;

	if (propagation)
		onSettingsChanged();
}

void	Element::enableFocus(const bool propagation) noexcept
{
	_settings.focus = true;

	if (propagation)
		onSettingsChanged();
}

void	Element::disableFocus(const bool propagation) noexcept
{
	_settings.focus = false;

	if (propagation)
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

Color		Element::getMainColor(void) const noexcept
{
	return _style.mainColor;
}

Color		Element::getSelectColor(void) const noexcept
{
	return _style.selectColor;
}

bool	Element::isClicked(void) const noexcept
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

bool	Element::isVisible(void) const noexcept
{
	return _state.visibility;
}
