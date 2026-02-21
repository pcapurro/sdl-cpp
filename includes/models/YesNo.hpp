#ifndef YESNO_HPP
# define YESNO_HPP

# include "Window.hpp"
# include "Text.hpp"

# define YES 1
# define NO 2

class YesNo final : public Window
{
	public:
		YesNo(void) = delete;
		~YesNo(void) = default;
};

#endif
