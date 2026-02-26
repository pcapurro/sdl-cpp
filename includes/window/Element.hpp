#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Config.hpp"

class Element
{
	protected:
		Config			_frameConfig;

	public:
		Element(void) = delete;
		Element(const Config& frameConfig) : _frameConfig(frameConfig) {}
		Element(Element&& original) : _frameConfig(std::move(original._frameConfig)) {}

		virtual ~Element(void) = default;

		virtual void	render(SDL_Renderer* renderer) = 0;
		bool			isAbove(const int x, const int y) const;

		void			setX(const int x);
		void			setY(const int y);
		void			setWidth(const int w);
		void			setHeight(const int h);
		void			setVisibility(const bool value);
		void			setColor(const Color color);
		void			setOpacity(const int opacity);

		Color			getColor(void) const;
		int				getType(void) const;
		int				getHighlightCursor(void) const;
		int				getNormalCursor(void) const;
		int				getX(void) const;
		int				getY(void) const;
		int				getWidth(void) const;
		int				getHeight(void) const;
};

#endif
