#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Properties.hpp"

class Element
{
	protected:
		Properties		_properties;

		uint8_t			_opacity;
		bool			_highlight;

		bool			_visibility;

	public:
		Element(void) = delete;
		Element(const Properties& properties) noexcept;

		virtual ~Element(void) = default;

		virtual void	render(SDL_Renderer* renderer) = 0;
		bool			isAbove(const int x, const int y) const noexcept;

		void			setX(const int x) noexcept;
		void			setY(const int y) noexcept;

		void			setWidth(const int w) noexcept;
		void			setHeight(const int h) noexcept;

		void			setOpacity(const uint8_t opacity) noexcept;
		void			setHighlight(const bool highlight) noexcept;

		void			setVisibility(const bool visibility) noexcept;

		int				getX(void) const noexcept;
		int				getY(void) const noexcept;

		int				getWidth(void) const noexcept;
		int				getHeight(void) const noexcept;

		uint8_t			getOpacity(void) const noexcept;
		bool			getHighlight(void) const noexcept;

		bool			getVisibility(void) const noexcept;
};

#endif
