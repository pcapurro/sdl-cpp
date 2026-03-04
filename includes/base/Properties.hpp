#ifndef PROPERTIES_HPP
# define PROPERTIES_HPP

# include "Global.hpp"

class Properties
{
    public:
        int         x = 0;
        int         y = 0;

        int         width = 0;
        int         height = 0;

        bool        isAbove(const int mouseX, const int mouseY) const noexcept;
};

#endif
