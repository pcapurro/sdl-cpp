#ifndef SHAPE_HPP
# define SHAPE_HPP

# include "Element.hpp"

class Shape final : public Element
{
    private:
        Color           _color;

        bool            _border;
        int             _borderThickness;
        Color           _borderColor;

    public:
        Shape(void) = delete;

        Shape(const int x, const int y, const int w, const int h, \
            const Color& color, const bool border, \
            const int borderThickness, const Color& borderColor);

        Shape(const Properties& properties, const Color& color, const bool border, \
            const int borderThickness, const Color& borderColor);

        ~Shape(void) = default;

        void                    render(SDL_Renderer* renderer);
};

#endif
