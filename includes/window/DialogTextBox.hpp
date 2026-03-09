#ifndef DIALOGTEXTBOX_HPP
# define DIALOGTEXTBOX_HPP

# include "Window.hpp"

# include "Text.hpp"
# include "Shape.hpp"
# include "Image.hpp"

# include "TextButton.hpp"
# include "TextField.hpp"

class DialogTextBox final : public Window
{
	private:
		vector<unique_ptr<Element>>		_elements;
		vector<unique_ptr<Element>>		_buttons;

		size_t							_tabCursor = 0;

		string							_fontPath;

		string							_finalAnswer;

		void							addLogo(const int cursorX, const int cursorY, const string& logoPath, \
											const int logoWidth, const int logoHeight, const bool centered = false);

		void							addTitleText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);
		void							addTitleLimit(const int cursorX, const int cursorY, const int width);

		void							addText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);

		void							addTextField(const int cursorX, const string& fontPath, \
											const int maxText);

		void							addErrorText(const int cursorX, const string& fontPath);

	public:
		DialogTextBox(void) = delete;
		DialogTextBox(const string& name, const int width = 400, const int height = 170, \
    		const string& fontPath = "", const int displayMode = LIGHT_MODE, const string& titleText = "", \
			const bool titleLimit = LIMIT_ON, const string& text = "", const int maxText = 30, \
			const string& logoPath = "", const int logoWidth = 75, const int logoHeight = 75, \
			const bool logoCentered = false);

		~DialogTextBox(void) = default;

		virtual int						routine(void);
		virtual int						waitForEvent(void);
		
		virtual void					render(void);

		void 							reactMouseMotion(const int x, const int y);
		int								reactMouseButtonUp(const int x, const int y);
		void 							reactMouseButtonDown(const int x, const int y, const int clicks);

		int								reactKeyButtonDown(const int key);
		void 							reactCharactersDown(const char* text);

		virtual int						reactEvent(SDL_Event* event, \
											const int x = 0, const int y = 0);

		string							getFinalAnswer(void) const;
};

#endif
