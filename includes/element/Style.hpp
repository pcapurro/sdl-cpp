#ifndef STYLE_HPP
# define STYLE_HPP

# include "Global.hpp"

# include "Color.hpp"

class Style
{
    public:
        uint8_t     globalOpacity = 255;

        Color       mainColor;
        Color       borderColor;

        Color       selectColor;
};

#endif
