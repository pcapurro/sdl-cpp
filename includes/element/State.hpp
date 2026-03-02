#ifndef STATE_HPP
# define STATE_HPP

# include "Global.hpp"

class State
{
    public:
		bool		click = false;

		bool		select = false;
		int			selectType = NONE;

		bool		hover = false;
		int			hoverCursor = SDL_SYSTEM_CURSOR_ARROW;

		bool		highlight = false;

		bool		visibility = true;
};

#endif
