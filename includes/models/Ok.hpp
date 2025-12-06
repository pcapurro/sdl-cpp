#ifndef OK_HPP
# define OK_HPP

# include "Window.hpp"

class Ok final : public Window
{
	public:
		Ok(const std::string name, const std::string text);
		~Ok(void) = default;

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
