#ifndef DIALOGTEXTBOXPREVIEW_HPP
# define DIALOGTEXTBOXPREVIEW_HPP

# include "Software.hpp"

# include "DialogTextBox.hpp"

class DialogTextBoxPreview : public Software
{
    private:
        optional<DialogTextBox>     _window;

        string                      _text;

    public:
        DialogTextBoxPreview(const string& windowTitle, const string& font, \
            const int windowWidth = 400, const int windowHeight = 170, const int colorTheme = Window::DarkMode, \
            const string& title = "[Title]", const bool limit = true, const string& text = "[Text]", \
            const int maxChars = 30, const string& logoPath = "", const int logoWidth = 55, const int logoHeight = 55, \
            const bool logoCentering = false);

        ~DialogTextBoxPreview(void) = default;

        string                      getText(void) const;

        int                         routine(void);
};

#endif
