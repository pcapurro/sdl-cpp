#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"
# include "Text.hpp"

class YesNo final : public Window
{
	private:
		vector<Element>			_elements;
		vector<Text>			_texts;

	public:
		YesNo(void) = delete;
		YesNo(const string& name, const int width = 400, const int height = 200, \
    		const string& fontPath = "", const bool darkMode = false, const string& title = "", \
			const bool titleLimit = true, const string& text = "", const string& logoPath = "");

		~YesNo(void) = default;

		virtual int				routine(void);
		virtual int				waitForEvent(void);
		
		virtual void			draw(void);
		virtual void			reactEvent(SDL_Event* event);
};

#endif
