#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "Global.hpp"

class Settings
{
    public:
        bool    select = false;
        int     selectType = State::None;

        bool    hover = false;
        int     hoverCursor = SDL_SYSTEM_CURSOR_ARROW;

        bool    highlight = false;
        bool    focus = false;
};

#endif
