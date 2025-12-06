#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"

# define YES 1
# define NO 2

class YesNo final : public Window
{
	public:
		YesNo(const string& name, const int width = 400, const int height = 200, \
				const string& text = "", const string& fontPath = "");
		~YesNo(void) = default;

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
