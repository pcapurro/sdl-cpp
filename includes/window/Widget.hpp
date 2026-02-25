#ifndef WIDGET_HPP
# define WIDGET_HPP

# include "Config.hpp"
# include "Layout.hpp"

class Widget
{
    private:
        Layout          _layout;

    public:
        Widget(void) = default;
        virtual ~Widget(void) = default;

        virtual void    render(SDL_Renderer* renderer, \
            const Config& frameConfig) = 0;

        Layout          getLayout(void) const { return _layout; }
};

#endif
