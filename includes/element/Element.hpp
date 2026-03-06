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
		virtual void	onPropertiesChanged(SDL_Renderer* renderer)
							{ (void) renderer; };
		virtual void	onStyleChanged(void) {};

		virtual void	onSettingsChanged(void) {};
		virtual void	onStateChanged(void) {};

	public:
		Element(void) = delete;
		Element(const Properties& properties, const Style& style = Style{}, \
			const Settings& settings = Settings{}, const State& state = State{}) noexcept;

		virtual ~Element(void) = default;

		virtual void	render(SDL_Renderer* renderer) = 0;

		virtual void	onMouseDown(const int x = 0, const int y = 0) {};
		virtual void	onMouseDownDouble(const int x = 0, const int y = 0) {};
		virtual void	onMouseDownOutside(void) {};

		virtual void	onMouseUp(const int x = 0, const int y = 0) {};
		virtual void	onMouseUpOutside(void) {};

		virtual void	onMouseHover(const int x = 0, const int y = 0) {};
		virtual void	onMouseHoverOutside(void) {};

		virtual void	onButtonDown(const int key) {};

		void			setSettings(const bool select, const int selectType, const bool hover, \
			const int hoverCursor, const bool highlight, const bool focus) noexcept;

		bool			isAbove(const int mouseX, const int mouseY) const noexcept;

		void			setX(const int x, SDL_Renderer* renderer = nullptr, \
							const bool propagation = true) noexcept;
		void			setY(const int y, SDL_Renderer* renderer = nullptr, \
							const bool propagation = true) noexcept;

		void			setWidth(const int width, SDL_Renderer* renderer = nullptr, \
							const bool propagation = true) noexcept;
		void			setHeight(const int height, SDL_Renderer* renderer = nullptr, \
							const bool propagation = true) noexcept;

		void			setMainColor(const Color& color, \
							const bool propagation = true) noexcept;
		void			setSelectColor(const Color& color, \
							const bool propagation = true) noexcept;

		void			setClick(const bool click, \
							const bool propagation = true) noexcept;

		void			setSelected(const bool select, \
							const bool propagation = true) noexcept;
		void			setSelectType(const int selectType, \
							const bool propagation = true) noexcept;

		void			setHighlight(const bool highlight, \
							const bool propagation = true) noexcept;
		void			setFocus(const bool focus, \
							const bool propagation = true) noexcept;

		void			setHover(const bool hover, \
							const bool propagation = true) noexcept;
		void			setHoverCursor(const int cursor, \
							const bool propagation = true) noexcept;

		void			setVisibility(const bool visibility, \
							const bool propagation = true) noexcept;

		void			enableSelect(const bool propagation = true) noexcept;
		void			disableSelect(const bool propagation = true) noexcept;

		void			enableHover(const bool propagation = true) noexcept;
		void			disableHover(const bool propagation = true) noexcept;

		void			enableHighlight(const bool propagation = true) noexcept;
		void			disableHighlight(const bool propagation = true) noexcept;

		void			enableFocus(const bool propagation = true) noexcept;
		void			disableFocus(const bool propagation = true) noexcept;

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
