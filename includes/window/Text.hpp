#ifndef TEXT_HPP
# define TEXT_HPP

# include "Element.hpp"
# include "Font.hpp"

class Text final : public Element
{
    private:
		Font            _font;

        int             _size;
		string          _text;

    public:
        Text(void) = default;
        Text(const string& text, const int size, const string& fontPath, \
            const int x, const int y, const int w, const int h, Color* color = nullptr, \
            SDL_Texture* texture = nullptr, const int type = 0, const bool highlight = false, \
            const int highlightCursor = 1, const int normalCursor = 1, const bool visibility = true);

        ~Text(void) = default;

        void    setText(const string& text, const int size, const string& fontPath, \
            const int x, const int y, const int w, const int h, Color* color = nullptr, \
            SDL_Texture* texture = nullptr, const int type = 0, const bool highlight   = false, \
            const int highlightCursor = 1, const int normalCursor = 1, const bool visibility = true);

		void            setMainText(const string& newText);
		void            setFontPath(const string& newFontPath);
};

#endif
