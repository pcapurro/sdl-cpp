#ifndef SHAPE_HPP
# define SHAPE_HPP

# include "Element.hpp"

class Shape final : public Element
{
    private:
        Color       _color;

        uint8_t     _borderOpacity;

        bool        _border;
        int         _borderThickness;
        Color       _borderColor;

    public:
        Shape(void) = delete;

        Shape(const int x, const int y, const int w, const int h, \
            const Color& color, const bool border = false, \
            const int borderThickness = 4, const Color& borderColor = Color{});

        Shape(const Properties& properties, const Color& color, const bool border = false, \
            const int borderThickness = 4, const Color& borderColor = Color{});

        ~Shape(void) = default;

        void        render(SDL_Renderer* renderer);

        void        setColor(Color color) noexcept;
        void        setBorderColor(Color color) noexcept;
};

#endif
