#ifndef FORM_HPP
# define FORM_HPP

# include "Render.hpp"

class Form final : public Render
{
    private:
        Texture     _image;

    public:
        Form(void) = default;

        void        render(SDL_Renderer* renderer, const Config& config);
};

#endif
