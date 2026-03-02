#ifndef TEXT_HPP
# define TEXT_HPP

# include "Font.hpp"
# include "Texture.hpp"
# include "Element.hpp"

class Text final : public Element
{
    private:
        Color               _writeColor;

        Font                _font;
        optional<Texture>   _text;

        bool                _free;

    public:
        Text(void) = delete;

        Text(const int x, const int y, const string& text, \
            const int size, const Color& color, const string& fontPath, \
            SDL_Renderer* renderer, const int maxWidth = 0);

        Text(const Properties& properties, const string& text, const int size, \
            const Color& color, const string& fontPath, SDL_Renderer* renderer, \
            const int maxWidth = 0);

        void        render(SDL_Renderer* renderer);

        void        setColor(Color color) noexcept;

        void        updateText(const string& text, const int maxWidth, \
                        SDL_Renderer* renderer) noexcept;
};

#endif
