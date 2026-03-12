#ifndef DIALOGVALUESBOX_HPP
# define DIALOGVALUESBOX_HPP

# include "Window.hpp"

# include "Text.hpp"
# include "Shape.hpp"
# include "Image.hpp"

# include "TextButton.hpp"
# include "ValueField.hpp"

class DialogValuesBox final : public Window
{
	private:
		vector<unique_ptr<Element>>		_elements;

		unique_ptr<Element>				_okButton;

		unique_ptr<ValueField>			_upField;
		unique_ptr<Text>				_upError;

		unique_ptr<ValueField>			_downField;
		unique_ptr<Text>				_downError;

		size_t							_tabCursor = 1;

		string							_fontPath;

		vector<string>					_titles;
		vector<string>					_units;
		vector<int>						_minValues;
		vector<int>						_maxValues;

		bool							_error = false;
		vector<int>						_finalValues;

		void							addLogo(const int cursorX, const int cursorY, const string& logoPath, \
											const int logoWidth, const int logoHeight, const bool centered = false);

		void							addTitleText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);
		void							addTitleLimit(const int cursorX, const int cursorY, const int width);

		void							addText(const int cursorX, const int cursorY, const string& text, \
											const string& fontPath, const int maxWidth);

		void							addFieldsTitles(const string& fontPath);
		void							addFields(const string& fontPath, const int maxText);
		void							addFieldsUnits(const string& fontPath);
		void							addFieldsErrors(const string& fontPath);

		void							addButton(const string& fontPath);

	public:
		DialogValuesBox(void) = delete;
		DialogValuesBox(const string& name, const string& fontPath, const int width = 400, \
			const int height = 170, const int displayMode = LIGHT_MODE, const string& titleText = "[Title]", \
			const bool titleLimit = false, const string& text = "[Description]", const int maxText = 6, \
			const vector<string>& titles = {"length"}, const vector<string>& units = {"px"}, \
			const vector<int>& minValues = {0}, const vector<int>& maxValues = {999}, const string& logoPath = "", \
			const int logoWidth = 75, const int logoHeight = 75, const bool logoCentered = false);

		~DialogValuesBox(void) = default;

		virtual int						routine(void);
		virtual int						waitForEvent(void);
		
		virtual void					render(void);

		void							reactError(void);

		void 							reactMouseMotion(const int x, const int y);
		int								reactMouseButtonUp(const int x, const int y);
		void 							reactMouseButtonDown(const int x, const int y, const int clicks);

		int								reactKeyButtonDown(const int key);
		void 							reactCharactersDown(const char* text);

		virtual int						reactEvent(SDL_Event* event, \
											const int x = 0, const int y = 0);

        vector<int>                     getFinalValues(void) const;
};

#endif
