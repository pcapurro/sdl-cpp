#ifndef DIALOGVALUESPREVIEW_HPP
# define DIALOGVALUESPREVIEW_HPP

# include "Software.hpp"

# include "DialogValuesBox.hpp"

class DialogValuesBoxPreview : public Software
{
    private:
        optional<DialogValuesBox>       _window;

        vector<int>                     _values;

    public:
        DialogValuesBoxPreview(const string& windowTitle, const string& font, \
            const int windowWidth = 400, const int windowHeight = 170, const int colorTheme = Window::DarkMode, \
            const string& title = "[Title]", const bool limit = true, const string& text = "[Text]", \
            const int maxChars = 4, const vector<string>& fieldsTitles = {"[title]"}, \
            const vector<string>& fieldsUnits = {"[unit]"}, const vector<int>& fieldsMinimums = {0}, \
            const vector<int>& fieldsMaximums = {999});

        ~DialogValuesBoxPreview(void) = default;

        vector<int>                     getValues(void) const;

        int                             routine(void);
};

#endif
