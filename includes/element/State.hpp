#ifndef STATE_HPP
# define STATE_HPP

# include "Global.hpp"

class State
{
    public:
		bool		click = false;

		bool		select = false;
		bool		hover = false;
		bool		highlight = false;

		bool		visibility = true;
};

#endif
