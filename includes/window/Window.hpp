#ifndef WINDOW_HPP
# define WINDOW_HPP

# include "Global.hpp"

# include "Element.hpp"
# include "Color.hpp"
# include "Texture.hpp"

class Window
{
	private:
		int						_width;
		int						_height;

		int						_x;
		int						_y;

		string					_name;

		SDL_Window*				_mainWindow;
		SDL_Renderer*			_mainRenderer;

		SDL_Cursor*				_normalCursor;
		SDL_Cursor*				_interactCursor;
		SDL_Cursor*				_crossHairCursor;
		SDL_Cursor*				_textCursor;

	public:
		Window(const string& name, const int width, const int height);
		virtual					~Window(void);

		virtual int				routine(void) = 0;
		virtual int				waitForEvent(void) = 0;
		
		virtual void			draw(void) = 0;

		virtual void			loadImages(void) = 0;

		virtual void			reactEvent(SDL_Event* event) = 0;

		virtual void			generateElements(void) = 0;

		void					setTitle(const std::string& title);

		void					drawBackground(Color color);
		void					drawElements(vector<Element>& elements);
	
		void					blur(void);
		void					render(void);
		void					clear(void);

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
