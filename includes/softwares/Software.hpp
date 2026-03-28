#ifndef SOFTWARE_HPP
# define SOFTWARE_HPP

# include "Global.hpp"

# include "Window.hpp"

class Software
{
    public:
        Software(void) = default;
        ~Software(void) = default;

        virtual int         routine(void) = 0;
};

#endif
