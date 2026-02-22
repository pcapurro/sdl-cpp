#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"

# include "Config.hpp"

class Element
{
	private:
		Config			_config;

		bool			_selected;
		bool			_highlighted;

	public:
		Element(void) = default;
		Element(const Config& config);
		~Element(void) = default;

		int				getX(void) const { return _config.x; };
		int				getY(void) const { return _config.y; };

		int				getWidth(void) const { return _config.w; };
		int				getHeight(void) const { return _config.h; };

		void			setX(const int x) { _config.x = x; };
		void			setY(const int y) { _config.y = y; };

		void			setWidth(const int w) { _config.w = w; };
		void			setHeight(const int h) { _config.h = h; };

		void			select(void) { _selected = true; };
		void			unSelect(void) { _selected = false; };

		void			highlight(void) { _highlighted = true; };
		void			unHighlight(void) { _highlighted = false; };

		SDL_Texture*	getTexture(void) const { return _config.texture; };
		Color			getColor(void) const { return _config.color; };

		int				getType(void) const { return _config.type; };

		int				getHighlightCursor(void) const { return _config.highlightCursor; };
		int				getNormalCursor(void) const { return _config.normalCursor; };

		void			setTexture(SDL_Texture* texture) { _config.texture = texture; };
		void			setVisibility(const bool value) { _config.visibility = value; };
		void			setColor(const Color color) { _config.color = color; };
		void			setOpacity(const int opacity) { _config.color.a = opacity; };

		bool			isAbove(const int x, const int y) const;
		bool			isSelected(void) const { return _selected; };

		void			draw(SDL_Renderer* renderer);
};

#endif
