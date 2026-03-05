#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Properties.hpp"
# include "Style.hpp"
# include "State.hpp"
# include "Settings.hpp"
# include "Render.hpp"

class Element
{
	private:
		Properties		_properties;
		Style			_style;

		Settings		_settings;
		State			_state;

	protected:
		virtual void	onPropertiesChanged(SDL_Renderer* renderer) { (void) renderer; };
		virtual void	onStyleChanged(void) {};

		virtual void	onSettingsChanged(void) {};
		virtual void	onStateChanged(void) {};

	public:
		Element(void) = delete;
		Element(const Properties& properties, const Style& style = Style{}, \
			const Settings& settings = Settings{}, const State& state = State{}) noexcept;

		virtual ~Element(void) = default;

		virtual void	render(SDL_Renderer* renderer) = 0;

		bool			isAbove(const int mouseX, const int mouseY) const noexcept;

		void			setX(const int x, SDL_Renderer* renderer) noexcept;
		void			setY(const int y, SDL_Renderer* renderer) noexcept;

		void			setWidth(const int width, SDL_Renderer* renderer) noexcept;
		void			setHeight(const int height, SDL_Renderer* renderer) noexcept;

		void			setMainColor(const Color& color) noexcept;
		void			setSelectColor(const Color& color) noexcept;

		void			setClick(const bool click) noexcept;

		void			setSelected(const bool select) noexcept;
		void			setSelectType(const int selectType) noexcept;

		void			setHighlight(const bool highlight) noexcept;
		void			setFocus(const bool focus) noexcept;

		void			setHover(const bool hover) noexcept;
		void			setHoverCursor(const int cursor) noexcept;

		void			setVisibility(const bool visibility) noexcept;

		void			enableSelect(void) noexcept;
		void			disableSelect(void) noexcept;

		void			enableHover(void) noexcept;
		void			disableHover(void) noexcept;

		void			enableHighlight(void) noexcept;
		void			disableHighlight(void) noexcept;

		void			enableFocus(void) noexcept;
		void			disableFocus(void) noexcept;

		int				getX(void) const noexcept;
		int				getY(void) const noexcept;

		int				getWidth(void) const noexcept;
		int				getHeight(void) const noexcept;

		Color			getMainColor(void) const noexcept;
		Color			getSelectColor(void) const noexcept;

		bool			isClicked(void) const noexcept;

		bool			isSelectPossible(void) const noexcept;
		bool			isSelected(void) const noexcept;
		int				getSelectType(void) const noexcept;

		bool			isHighlightPossible(void) const noexcept;
		bool			isHighlighted(void) const noexcept;

		bool			isFocusPossible(void) const noexcept;
		bool			isFocused(void) const noexcept;

		bool			isHoverPossible(void) const noexcept;
		bool			isHover(void) const noexcept;
		int				getHoverCursor(void) const noexcept;

		bool			getVisibility(void) const noexcept;
};

#endif
