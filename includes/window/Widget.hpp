#ifndef WIDGET_HPP
# define WIDGET_HPP

# include "Config.hpp"
# include "Layout.hpp"

class Widget
{
    private:
        int             _type;
        Layout          _layout;

    public:
        Widget(const int type = NONE, Layout layout = Layout{}) : \
            _type(type), _layout(layout) {}
        virtual ~Widget(void) = default;

        virtual void    render(SDL_Renderer* renderer, \
            const Config& frameConfig) = 0;

        int             getType(void) const { return _type; }
        Layout          getLayout(void) const { return _layout; }
};

#endif
