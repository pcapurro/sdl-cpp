#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "Global.hpp"

# include "TTF.hpp"

class Engine
{
    private:
        optional<TTF>           _ttf;

    public:
        Engine(const bool video = true, const bool antialiasing = false, \
            const bool ttf = false, const bool events = true, \
            const bool textInput = false, const bool audio = false);

        ~Engine(void);

        static constexpr int    None = 128;
        static constexpr int    Ok = 256;
        static constexpr int    End = 512;
        static constexpr int    Return = 1024;
};

#endif
