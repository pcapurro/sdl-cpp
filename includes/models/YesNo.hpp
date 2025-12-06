#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"

# define YES 1
# define NO 2

class YesNo final : public Window
{
	public:
		YesNo(const std::string name, const std::string text);
		~YesNo(void) = default;

		int		routine(void);
		int		waitForEvent(void);

		void	draw(void);
		void	loadImages(void) {};
		void	reactEvent(SDL_Event* event);
		void	generateElements(void);

		void	loadFont(void);

	private:
		TTF_Font*				_font;

		std::string				_text;
		std::vector<Element>	_elements;

		int						_state;

};

#endif
