#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Config.hpp"
# include "Render.hpp"

class Element
{
	private:
		Config					_config;
		unique_ptr<Render>		_render;

	public:
		Element(void) = default;
		Element(const Config& config) noexcept : _config(config) {}
		Element(Element&& original) noexcept : _config(std::move(original._config)), \
			_render(std::move(original._render)) {}

		~Element(void) = default;

		void			draw(SDL_Renderer* renderer);
		bool			isAbove(const int x, const int y) const;

		void			setRender(unique_ptr<Render>&& render);

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
