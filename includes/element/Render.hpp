#ifndef RENDER_HPP
# define RENDER_HPP

# include "Global.hpp"

# include "Color.hpp"

class Render
{
    public:
        static void     renderBorderSelect(const int x, const int y, const int width, const int height, \
                            const Color& color, SDL_Renderer* renderer);

        static void     renderCornerSelect(const int x, const int y, const int width, const int height, \
                            const Color& color, SDL_Renderer* renderer);

        static void     renderCenterSelectCross(const int x, const int y, const int width, const int height, \
                            const Color& color, SDL_Renderer* renderer);

        static void     renderSelect(const int value, const int x, const int y, const int width, const int height, \
                            const Color& color, SDL_Renderer* renderer);

        static void     renderHighlight(const int x, const int y, const int width, const int height, \
                            const Color& color, SDL_Renderer* renderer);
};

#endif
