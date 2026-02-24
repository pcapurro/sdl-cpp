#ifndef TEXT_HPP
# define TEXT_HPP

# include "Font.hpp"
# include "Texture.hpp"
# include "Render.hpp"

class Text final : public Render
{
    private:
        int         _realWidth;
        int         _realHeight;

        Font        _font;
        Texture     _text;

    public:
        Text(void) = delete;
        Text(const string& text, const int size, const Color& color, \
            const string& fontPath, SDL_Renderer* renderer, const int maxWidth);

        void        render(SDL_Renderer* renderer, const Config& config);

        int         getRealWidth(void) const;
        int         getRealHeight(void) const;
};

#endif
