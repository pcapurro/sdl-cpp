#ifndef TEXTBUTTON_HPP
# define TEXTBUTTON_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class TextButton : public Element
{
    private:
        optional<Text>          _mainText;
        optional<Shape>         _background;

    public:
        TextButton(void) = delete;

        TextButton(const Properties& properties, const Color& backColor, \
            const string& text, const int size, const Color& textColor, \
            const string& fontPath, SDL_Renderer* renderer);

        TextButton(const int x, const int y, const int width, const int height, \
            const Color& backColor, const string& text, const int size, \
            const Color& textColor, const string& fontPath, SDL_Renderer* renderer);

        ~TextButton(void) = default;

        void                    setSettings(const bool select, const int selectType, \
            const bool hover, const int hoverCursor, const bool highlight, const bool focus) noexcept;

        void                    render(SDL_Renderer* renderer);
};

#endif
