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
        int                     _lineHeight = 0;

        vector<Point>           _charEnds;

        void                    createNormalLine(const string& text, \
                                    SDL_Renderer* renderer);

        void                    createWrappedLines(const string& text, \
                                    const int maxWidth, SDL_Renderer* renderer);

    public:
        Text(void) = delete;

        Text(const int x, const int y, const string& text, \
            const int size, const string& fontPath, const Color& color, \
            SDL_Renderer* renderer, const int maxWidth = 0, const bool wrapping = false);

        void                    render(SDL_Renderer* renderer);

        void                    setColor(Color color) noexcept;

        string                  getTextStr(void) const noexcept;
        int                     getLinesNb(void) const noexcept;

        int                     getCharX(const int cursor) const noexcept;
        int                     getCharY(const int cursor) const noexcept;

        int                     getClosestCharX(const int x, const int y) const noexcept;
        int                     getLineY(const int y) const noexcept;

        int                     getCharPos(const int x, const int y);

        void                    update(const string& text, const int maxWidth, \
                                    const bool wrapping, SDL_Renderer* renderer);
};

#endif
