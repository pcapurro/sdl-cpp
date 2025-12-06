#ifndef TEXT_HPP
# define TEXT_HPP

# include "Element.hpp"

class Text final : public Element
{
    public:
        Text(void) = default;
        ~Text(void) = default;

        void    setText(const string& text, const int size, const string& fontPath, \
            const int x, const int y, const int w, const int h, Color* color = NULL, \
            SDL_Texture* texture = NULL, const int type = 0, const bool highlight = false, \
            const int highlightCursor = 1, const int normalCursor = 1, const bool visibility = true);

		void	setMainText(const string& newText);
		void	setFontPath(const string& newFontPath);
		void	loadFont(void);

    private:
		string				_fontPath;
		TTF_Font*			_font;

        int                 _size;
		string				_text;
};

#endif
