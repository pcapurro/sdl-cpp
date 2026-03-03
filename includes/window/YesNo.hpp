#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"

# include "Text.hpp"
# include "Shape.hpp"
# include "Image.hpp"
# include "TextButton.hpp"

class YesNo final : public Window
{
	private:
		vector<unique_ptr<Element>>		_elements;

		void							addLogo(const int cursorX, const int cursorY, const string& logoPath, \
											const int logoWidth, const int logoHeight);

		void							addTitleText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);
		void							addTitleLimit(const int cursorX, const int cursorY, const int width);

		void							addText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);

		void							addButtons(const string& fontPath, const string& leftButtonText, \
											const string& rightButtonText);

	public:
		YesNo(void) = delete;
		YesNo(const string& name, const int width = 400, const int height = 200, \
    		const string& fontPath = "", const bool darkMode = false, const string& titleText = "", \
			const bool titleLimit = true, const string& text = "", const string& leftbuttonText = "yes", \
			const string& rightButtonText = "no", const string& logoPath = "", \
			const int logoWidth = LOGO_WIDTH, const int logoHeight = LOGO_HEIGHT);

		~YesNo(void) = default;

		virtual int						routine(void);
		virtual int						waitForEvent(void);

		virtual	void					refreshDisplay(void);
		
		virtual void					render(void);

		virtual void					reactEvent(SDL_Event* event, \
											const int x = 0, const int y = 0);
};

#endif
