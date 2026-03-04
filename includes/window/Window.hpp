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
		int						_width;
		int						_height;

		int						_x;
		int						_y;

		const string			_name;

		Color					_writeColor;
		Color					_backgroundColor;

		SDL_Window*				_mainWindow;
		SDL_Renderer*			_mainRenderer;

		optional<Cursor>		_normalCursor;
		optional<Cursor>		_textCursor;
		optional<Cursor>		_loadingCursor;
		optional<Cursor>		_crossHairCursor;
		optional<Cursor>		_interactCursor;
		optional<Cursor>		_waitCursor;
		optional<Cursor>		_noCursor;

	public:
		Window(const string& name, const int width, const int height);
		virtual					~Window(void);

		virtual int				routine(void) = 0;
		virtual int				waitForEvent(void) = 0;

		virtual void			render(void) = 0;
		virtual int				reactEvent(SDL_Event* event, \
									const int x = 0, const int y = 0) = 0;

		virtual void			refreshDisplay(void) = 0;

		void					renderBackground(void);
	
		void					display(void);
		void					clear(void);

		void					setTitle(const std::string& title);

		void					setWriteColor(const Color& color);
		void					setBackgroundColor(const Color& color);

		Color					getWriteColor(void) const;
		Color					getBackgroundColor(void) const;

		SDL_Cursor*				getCursor(const int value) const;
		SDL_Renderer*			getRenderer(void) const;

		int						getWidth(void) const;
		int						getHeight(void) const;

		int						getX(void) const;
		int						getY(void) const;

		void					setX(const int x);
		void					setY(const int y);
};

#endif
