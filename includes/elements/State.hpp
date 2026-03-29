#ifndef STATE_HPP
# define STATE_HPP

# include "Global.hpp"

class State
{
    public:
		bool					click = false;

		bool					select = false;
		bool					hover = false;
		bool					highlight = false;
		bool					focus = false;

		bool					visibility = true;

	    static constexpr int    None = 0;
        static constexpr int    Ok = 42;
        static constexpr int    End = 84;
        static constexpr int    Return = 168;
};

#endif
