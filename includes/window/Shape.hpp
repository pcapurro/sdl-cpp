#ifndef SHAPE_HPP
# define SHAPE_HPP

# include "Widget.hpp"

class Shape final : public Widget
{
    public:
        Shape(void) = default;
        ~Shape(void) = default;

        void        render(SDL_Renderer* renderer, const Config& frameConfig);
};

#endif
