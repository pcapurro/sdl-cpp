#ifndef WINDOW_HPP
# define WINDOW_HPP

# include "Global.hpp"

# include "Element.hpp"
# include "Color.hpp"
# include "TextTexture.hpp"
# include "ImageTexture.hpp"
# include "Cursor.hpp"

class Window
{
	private:
		int						_width = MIN_WINDOW_W;
		int						_height = MIN_WINDOW_H;

		int						_x = 0;
		int						_y = 0;

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

		void					refreshDisplay(void);

		void					renderBackground(void);
	
		void					display(void);
		void					clear(void);

		void					setTitle(const std::string& title);

		void					setWriteColor(const Color& color) noexcept;
		void					setBackgroundColor(const Color& color) noexcept;

		Color					getWriteColor(void) const noexcept;
		Color					getBackgroundColor(void) const noexcept;

		SDL_Cursor*				getCursor(const int value) const noexcept;
		SDL_Renderer*			getRenderer(void) const noexcept;

		int						getWidth(void) const noexcept;
		int						getHeight(void) const noexcept;

		int						getX(void) const noexcept;
		int						getY(void) const noexcept;

		void					setX(const int x) noexcept;
		void					setY(const int y) noexcept;
};

#endif
