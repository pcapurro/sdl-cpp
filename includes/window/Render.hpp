#ifndef RENDER_HPP
# define RENDER_HPP

# include "Config.hpp"

class Render
{
    public:
        Render(void) = default;
        virtual ~Render(void) = default;

        virtual void    render(SDL_Renderer* renderer, \
            const Config& config) = 0;
};

#endif
