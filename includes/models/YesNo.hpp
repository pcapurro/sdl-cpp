#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"

# include "Text.hpp"
# include "Form.hpp"
# include "Image.hpp"

class YesNo final : public Window
{
	private:
		vector<Element>			_elements;

		void					addLogo(Config& globalConfig, const string& logoPath, \
									const int logoWidth, const int logoHeight);

		void					addTitleText(Config& globalConfig, const string& text, \
									const string& fontPath, const bool logo, const int logoWidth);
		void					addTitleLimit(Config& globalConfig, const bool logo, \
									const int logoWidth);

		void					addText(Config& globalConfig, const string& text, \
									const string& fontPath);

	public:
		YesNo(void) = delete;
		YesNo(const string& name, const int width = 400, const int height = 200, \
    		const string& fontPath = "", const bool darkMode = false, const string& title = "", \
			const bool titleLimit = true, const string& text = "", const string& logoPath = "", \
			const int logoWidth = LOGO_WIDTH, const int logoHeight = LOGO_HEIGHT);

		~YesNo(void) = default;

		virtual int				routine(void);
		virtual int				waitForEvent(void);

		virtual	void			refreshDisplay(void);
		
		virtual void			render(void);

		virtual void			reactEvent(SDL_Event* event, \
									const int x = 0, const int y = 0);
};

#endif
