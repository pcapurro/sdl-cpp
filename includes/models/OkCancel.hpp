#ifndef OKCANCEL_HPP
# define OKCANCEL_HPP

# include "Window.hpp"

# define OK 1
# define CANCEL 2

class OkCancel final : public Window
{
	public:
		OkCancel(const string& name, const int width = 400, const int height = 200, \
					const string& text = "", const string& fontPath = "");
		~OkCancel(void) = default;

		int		routine(void);
		int		waitForEvent(void);

		void	setText(const string& newText);
		void	setFontPath(const string& newFontPath);

		void	draw(void);
		void	loadImages(void) {};
		void	reactEvent(SDL_Event* event);
		void	generateElements(void);

		void	loadFont(void);

	private:
		string				_fontPath;
		TTF_Font*			_font;

		string				_text;
		vector<Element>		_elements;

		int					_state;

};

#endif
