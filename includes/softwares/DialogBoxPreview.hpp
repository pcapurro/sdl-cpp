#ifndef DIALOGBOXPREVIEW_HPP
# define DIALOGBOXPREVIEW_HPP

# include "Software.hpp"

# include "DialogBox.hpp"

class DialogBoxPreview : public Software
{
    private:
        optional<DialogBox>     _window;

    public:
        DialogBoxPreview(const string& windowTitle, const string& font, \
            const int windowWidth = 400, const int windowHeight = 170, const int colorTheme = DARK_MODE, \
            const string& title = "[Title]", const bool limit = true, const string& text = "[Text]", \
            const vector<string>& answers = {"OK"}, const string& logoPath = "", const int logoWidth = 55, \
            const int logoHeight = 55, const bool logoCentering = false);

        ~DialogBoxPreview(void) = default;

        int                     routine(void);
};

#endif
