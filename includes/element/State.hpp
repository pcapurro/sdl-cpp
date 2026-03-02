#ifndef STATE_HPP
# define STATE_HPP

# include "Global.hpp"

class State
{
    public:
		bool		click = false;

		bool		select = false;
		int			selectType = NONE;

		bool		highlight = false;

		bool		visibility = true;
};

#endif
