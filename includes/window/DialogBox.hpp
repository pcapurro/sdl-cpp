#ifndef DIALOGBOX_HPP
# define DIALOGBOX_HPP

# include "Window.hpp"

# include "Text.hpp"
# include "Shape.hpp"
# include "Image.hpp"
# include "TextButton.hpp"

class DialogBox final : public Window
{
	private:
		vector<unique_ptr<Element>>		_elements;
		vector<unique_ptr<TextButton>>	_buttons;

		size_t							_tabCursor;

		const vector<string>			_textButtons;

		void							addLogo(const int cursorX, const int cursorY, const string& logoPath, \
											const int logoWidth, const int logoHeight, const bool centered = false);

		void							addTitleText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);
		void							addTitleLimit(const int cursorX, const int cursorY, const int width);

		void							addText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);

		void							addButtons(const string& fontPath, const vector<string>& buttonsTexts);

	public:
		DialogBox(void) = delete;
		DialogBox(const string& name, const int width = 400, const int height = 170, \
    		const string& fontPath = "", const bool darkMode = false, const string& titleText = "", \
			const bool titleLimit = true, const string& text = "", const vector<string>& buttonsTexts = {"yes", "no"}, \
			const string& logoPath = "", const int logoWidth = LOGO_WIDTH, const int logoHeight = LOGO_HEIGHT, \
			const bool logoCentered = false);

		~DialogBox(void) = default;

		virtual int						routine(void);
		virtual int						waitForEvent(void);
		
		virtual void					render(void);

		void 							reactMouseMotion(const int x, const int y);
		int								reactMouseButtonUp(const int x, const int y);
		void 							reactMouseButtonDown(const int x, const int y);

		int								reactKeyButtonDown(const int key);

		virtual int						reactEvent(SDL_Event* event, \
											const int x = 0, const int y = 0);
};

#endif
