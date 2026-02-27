#ifndef CURSOR_HPP
# define CURSOR_HPP

# include "Global.hpp"

class Cursor
{
    private:
        const SDL_SystemCursor      _value;
        SDL_Cursor*                 _cursor = nullptr;

    public:
        Cursor(void) = delete;

        Cursor(const SDL_SystemCursor value);
        Cursor(const Cursor& original) = delete;

        Cursor(Cursor&& original) noexcept;

        Cursor&	    operator=(const Cursor& original) noexcept = delete;
        Cursor&     operator=(Cursor&& original) noexcept;

        ~Cursor(void) noexcept;

        SDL_Cursor*                 getCursor(void) const noexcept;
};

#endif
