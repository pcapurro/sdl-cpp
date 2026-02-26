#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Properties.hpp"

class Element
{
	protected:
		Properties			_properties;

	public:
		Element(void) = delete;
		Element(const Properties& properties) : _properties(properties) {}

		virtual ~Element(void) = default;

		virtual void		render(SDL_Renderer* renderer) = 0;
		bool				isAbove(const int x, const int y) const;

		void				setX(const int x);
		void				setY(const int y);

		void				setWidth(const int w);
		void				setHeight(const int h);

		int					getX(void) const;
		int					getY(void) const;

		int					getWidth(void) const;
		int					getHeight(void) const;
};

#endif
