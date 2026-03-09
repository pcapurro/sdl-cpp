#ifndef SHAPE_HPP
# define SHAPE_HPP

# include "Element.hpp"

class Shape final : public Element
{
    private:
        bool        _border = false;

        int         _borderThickness = 4;
        Color       _borderColor;

    public:
        Shape(void) = delete;

        Shape(const int x, const int y, const int width, const int height, \
            const Color& color, const bool border = false, \
            const int borderThickness = 4, const Color& borderColor = Color{});

        Shape(const Properties& properties, const Color& color, const bool border = false, \
            const int borderThickness = 4, const Color& borderColor = Color{});

        ~Shape(void) = default;

        void        render(SDL_Renderer* renderer);

        void	    setBorderThickness(const int thickness) noexcept;
        void	    setBorderColor(Color color) noexcept;
};

#endif
