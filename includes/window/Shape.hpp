#ifndef SHAPE_HPP
# define SHAPE_HPP

# include "Element.hpp"

class Shape final : public Element
{
    public:
        Shape(void) = delete;
        Shape(const Config& frameConfig);

        ~Shape(void) = default;

        void        render(SDL_Renderer* renderer);
};

#endif
