#ifndef TEXT_HPP
# define TEXT_HPP

# include "Font.hpp"
# include "TextTexture.hpp"
# include "Element.hpp"

class Text final : public Element
{
    private:
        string                  _textStr;
        Color                   _writeColor;

        Font                    _font;
        vector<TextTexture>     _lines;
        int                     _lineHeight;
        bool                    _wrapping;

        int                     _maxWidth;
        vector<Point>           _charEnds;

        bool                    _free;

        void                    createWrappedLines(const string& text, const int maxWidth, \
                                    vector<string>& lines);

    public:
        Text(void) = delete;

        Text(const int x, const int y, const string& text, \
            const int size, const Color& color, const string& fontPath, \
            SDL_Renderer* renderer, const int maxWidth = 0, const bool wrapping = false);

        void                    render(SDL_Renderer* renderer);

        void                    setColor(Color color) noexcept;

        string                  getTextStr(void) const noexcept;
        bool                    isWrapped(void) const noexcept;
        int                     getLinesNb(void) const noexcept;

        void                    update(const string& text, const int maxWidth, \
                                    const bool wrapping, SDL_Renderer* renderer);
};

#endif
