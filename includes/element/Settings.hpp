#ifndef SETTINGS_HPP
# define SETTINGS_HPP

# include "Global.hpp"

class Settings
{
    public:
        bool    select = false;
        int     selectType = NONE;

        bool    hover = false;
        int     hoverCursor = SDL_SYSTEM_CURSOR_ARROW;

        bool    highlight = false;
};

#endif
