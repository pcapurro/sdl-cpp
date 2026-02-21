#ifndef WINDOW_HPP
# define WINDOW_HPP

# include "Global.hpp"

# include "Element.hpp"
# include "Color.hpp"
# include "Texture.hpp"
# include "Cursor.hpp"

class Window
{
	private:
		const int				_width;
		const int				_height;

		int						_x;
		int						_y;

		const string			_name;

		SDL_Window*				_mainWindow;
		SDL_Renderer*			_mainRenderer;

		std::optional<Cursor>	_normalCursor;
		std::optional<Cursor>	_interactCursor;
		std::optional<Cursor>	_crossHairCursor;
		std::optional<Cursor>	_textCursor;

	public:
		Window(const string& name, const int width, const int height);
		virtual					~Window(void);

		virtual int				routine(void) = 0;
		virtual int				waitForEvent(void) = 0;
		
		virtual void			draw(void) = 0;
		virtual void			loadImages(void) = 0;
		virtual void			reactEvent(SDL_Event* event) = 0;
		virtual void			generateElements(void) = 0;

		void					drawBackground(const Color color);
		void					drawElements(vector<Element>& elements);
	
		void					blur(const uint8_t blurA = 127);
		void					render(void);
		void					clear(void);

		void					setTitle(const std::string& title);

		SDL_Cursor*				getCursor(const uint8_t value) const;
		SDL_Renderer*			getRenderer(void) const;

		int						getWidth(void) const;
		int						getHeight(void) const;

		int						getX(void) const;
		int						getY(void) const;

		void					setX(const int x);
		void					setY(const int y);
};

#endif
