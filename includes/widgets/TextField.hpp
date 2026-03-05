#ifndef TEXTFIELD_HPP
# define TEXTFIELD_HPP

# include "Text.hpp"
# include "Shape.hpp"
# include "Element.hpp"

class TextField : public Element
{
    private:
        optional<Text>      _mainText;
        optional<Text>      _placeholder;

        optional<Shape>     _textBack;
        optional<Shape>     _background;
    
    public:
        TextField(void) = delete;

        TextField(const Properties& properties, const Color& backColor, \
            const string& text, const string& placeholder, const int size, \
            const Color& textColor, const string& fontPath, SDL_Renderer* renderer);

        TextField(const int x, const int y, const int width, const int height, \
            const Color& backColor, const string& text, const string& placeholder, \
            const int size, const Color& textColor, const string& fontPath, SDL_Renderer* renderer);

        ~TextField(void) = default;

        void                    setSettings(const bool select, const int selectType, \
            const bool hover, const int hoverCursor, const bool highlight, const bool focus) noexcept;

        void                    addChar(const char c);

        void                    updateText(const string& text);
        void                    updatePlaceholder(const string& placeholder);

        string                  getText(void) const;

        void                    render(SDL_Renderer* renderer);

};

#endif
