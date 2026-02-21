#ifndef ELEMENT_HPP
# define ELEMENT_HPP

# include "Global.hpp"
# include "Color.hpp"

class Element
{
	private:
		int 			_x;
		int 			_y;

		int 			_w;
		int 			_h;

		int				_type;

		int				_highlightCursor;
		int				_normalCursor;

		bool			_highlighted;
		bool			_selected;

		bool			_visibility;
		bool			_highlight;

		SDL_Texture*	_texture;
		Color			_color;

	public:
		Element(void) = default;
		Element(const int x, const int y, const int w, const int h, \
					Color* color = nullptr, SDL_Texture* texture = nullptr, const int type = 0, \
					const bool highlight = false, const int highlightCursor = 1, \
					const int normalCursor = 1, const bool visibility = true);
		~Element(void) = default;

		void			setElement(const int x, const int y, const int w, const int h, \
							Color* color = nullptr, SDL_Texture* texture = nullptr, const int type = 0, \
							const bool highlight = false, const int highlightCursor = 1, \
							const int normalCursor = 1, const bool visibility = true);

		int				getX(void) const { return (_x); };
		int				getY(void) const { return (_y); };

		int				getW(void) const { return (_w); };
		int				getH(void) const { return (_h); };

		void			setX(const int x) { _x = x; };
		void			setY(const int y) { _y = y; };

		void			setW(const int w) { _w = w; };
		void			setH(const int h) { _h = h; };

		void			select(void) { _selected = true; };
		void			unSelect(void) { _selected = false; };

		void			highlight(void) { _highlighted = true; };
		void			unHighlight(void) { _highlighted = false; };

		SDL_Texture*	getTexture(void) const { return (_texture); };
		Color			getColor(void) const { return (_color); };

		int				getType(void) const { return (_type); };

		int				getHighlightCursor(void) const { return (_highlightCursor); };
		int				getNormalCursor(void) const { return (_normalCursor); };

		void			setTexture(SDL_Texture* texture) { _texture = texture; };
		void			setVisibility(const bool value) { _visibility = value; };
		void			setColor(Color color) { _color = color; };
		void			setOpacity(const int opacity) { _color.a = opacity; };

		bool			isAbove(const int x, const int y) const;
		bool			isSelected(void) const { return (_selected); };

		void			draw(SDL_Renderer* renderer);
};

#endif
