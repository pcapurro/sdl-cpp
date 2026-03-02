#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Properties.hpp"
# include "Style.hpp"
# include "State.hpp"
# include "Render.hpp"

class Element
{
	private:
		Properties		_properties;
		Style			_style;

		State			_state;

	public:
		Element(void) = delete;
		Element(const Properties& properties, const Style& style = Style{}, \
			const State& state = State{}) noexcept;

		virtual ~Element(void) = default;

		virtual void	render(SDL_Renderer* renderer) = 0;

		bool			isAbove(const int mouseX, const int mouseY) const noexcept;
		bool			isInside(const int elementX, const int elementY, \
    						const int elementWidth, const int elementHeight) const noexcept;

		void			setX(const int x) noexcept;
		void			setY(const int y) noexcept;

		void			setWidth(const int width) noexcept;
		void			setHeight(const int height) noexcept;

		void			setOpacity(const uint8_t opacity) noexcept;

		void			setClick(const bool click) noexcept;

		void			setSelected(const bool select) noexcept;
		void			setSelectType(const int selectType) noexcept;
		void			setSelectColor(const Color& color) noexcept;

		void			setHighlight(const bool highlight) noexcept;

		void			setVisibility(const bool visibility) noexcept;

		int				getX(void) const noexcept;
		int				getY(void) const noexcept;

		int				getWidth(void) const noexcept;
		int				getHeight(void) const noexcept;

		uint8_t			getOpacity(void) const noexcept;

		bool			getClick(void) const noexcept;

		bool			isSelected(void) const noexcept;
		int				getSelectType(void) const noexcept;
		Color			getSelectColor(void) const noexcept;

		bool			isHighlighted(void) const noexcept;

		bool			getVisibility(void) const noexcept;
};

#endif
