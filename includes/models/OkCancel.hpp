#ifndef OKCANCEL_HPP
# define OKCANCEL_HPP

# include "Window.hpp"

# define OK 1
# define CANCEL 2

class OkCancel final : public Window
{
	public:
		OkCancel(const std::string name, const std::string text);
		~OkCancel(void) = default;

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
