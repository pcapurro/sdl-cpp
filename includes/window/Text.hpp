#ifndef TEXT_HPP
# define TEXT_HPP

# include "Font.hpp"
# include "Texture.hpp"
# include "Element.hpp"

class Text final : public Element
{
    private:
        Color                   _writeColor;

        Font                    _font;
        Texture                 _text;

    public:
        Text(void) = delete;

        Text(const Properties& properties, const string& text, \
            const int size, const Color& color, const string& fontPath, \
            SDL_Renderer* renderer, const int maxWidth = 0);

        Text(const int x, const int y, const int w, const int h, \
            const string& text, const int size, const Color& color, \
            const string& fontPath, SDL_Renderer* renderer, const int maxWidth = 0);

        void	                render(SDL_Renderer* renderer);
};

#endif
