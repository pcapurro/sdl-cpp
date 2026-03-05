#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "Global.hpp"

# include "TTF.hpp"

class Engine
{
    private:
        optional<TTF>       _ttf;

    public:
        Engine(const bool video = true, const bool antialiasing = false, \
            const bool ttf = false, const bool events = true, const bool textInput = false, \
            const bool audio = false);

        ~Engine(void);
};

#endif
