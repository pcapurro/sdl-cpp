#ifndef RENDER_HPP
# define RENDER_HPP

# include "Global.hpp"

# include "Color.hpp"

class Render
{
    public:
        static void                 renderBorderSelect(const int x, const int y, const int width, \
            const int height, const Color& color, SDL_Renderer* renderer);

        static void                 renderCornerSelect(const int x, const int y, const int width, \
            const int height, const Color& color, SDL_Renderer* renderer);

        static void                 renderCenterSelect(const int x, const int y, const int width, \
            const int height, const Color& color, SDL_Renderer* renderer);

        static void                 renderCenterSelectCross(const int x, const int y, const int width, \
            const int height, const Color& color, SDL_Renderer* renderer);

        static void                 renderSelect(const int value, const int x, const int y, const int width, \
            const int height, const Color& color, SDL_Renderer* renderer);

        static void                 renderHighlight(const int x, const int y, const int width, \
            const int height, const Color& color, SDL_Renderer* renderer);

        static constexpr float      LimitRatio = 0.05f;
		static constexpr float      TitleRatio = 0.10f;
		static constexpr float      TextRatio = 0.08f;

        static constexpr int        BorderSelect = 21;
        static constexpr int        CornerSelect = 22;
        static constexpr int        CenterSelect = 23;
        static constexpr int        CenterSelectX = 24;
        static constexpr int        HighlightSelect = 25;

        static constexpr uint8_t    HiglihtOpacity = 100;
        static constexpr uint8_t    FocusOpacity = 200;
};

#endif
