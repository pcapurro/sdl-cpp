#ifndef TEXT_HPP
# define TEXT_HPP

# include "Element.hpp"
# include "Font.hpp"
# include "Config.hpp"
# include "Texture.hpp"

class Text final : public Element
{
    private:
        string                      _text;
        int                         _size;

        Font                        _font;
        Texture                     _texture;

    public:
        Text(void) = default;
        Text(const Config& config, const string& text, const int size, \
            const Color& color, const string& fontPath, SDL_Renderer* renderer, const int maxWidth);

        Text(const Text& original) = delete;
        Text(Text&& original) = default;

        Text&   operator=(const Text& original) = delete;
        Text&   operator=(Text&& original) = default;

        ~Text(void) = default;
};

#endif
