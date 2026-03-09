#include "Cursor.hpp"

Cursor::Cursor(const SDL_SystemCursor value) : _value(value)
{
    _cursor = SDL_CreateSystemCursor(_value);

    if (_cursor == nullptr)
    {
        throw std::runtime_error("SDL failed to create a cursor: " \
            + string(SDL_GetError()));
    }
}

Cursor::Cursor(Cursor&& original) noexcept : _value(original._value)
{
    _cursor = original._cursor;
    original._cursor = nullptr;
}

Cursor&     Cursor::operator=(Cursor&& original) noexcept
{
    if (this == &original)
        return *this;

    if (_cursor)
        SDL_FreeCursor(_cursor);

    _cursor = original._cursor;
    original._cursor = nullptr;

    return *this;
}

Cursor::~Cursor(void) noexcept
{
    if (_cursor)
        SDL_FreeCursor(_cursor);
}

SDL_Cursor*    Cursor::getCursor(void) const noexcept
{
    return _cursor;
}
