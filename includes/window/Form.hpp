#ifndef FORM_HPP
# define FORM_HPP

# include "Widget.hpp"

class Form final : public Widget
{
    public:
        Form(void) = default;
        ~Form(void) = default;

        void        render(SDL_Renderer* renderer, const Config& frameConfig);
};

#endif
