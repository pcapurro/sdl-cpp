#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Global.hpp"

# include "Color.hpp"
# include "Texture.hpp"

class Config
{
    public:
        int             x = 0;
        int             y = 0;

        int             w = 0;
        int             h = 0;

        Color           color = WHITE;

        int             type = NONE;

        bool            selected = false;

        bool            highlight = false;
        bool            highlighted = false;

        int             highlightCursor = 1;
        int             normalCursor = 1;

        bool            visibility = true;
};

#endif
