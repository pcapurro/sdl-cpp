#include "Render.hpp"

void    Render::renderBorderSelect(const int x, const int y, const int width, \
    const int height, const Color& color, SDL_Renderer* renderer)
{
    SDL_Rect    shapes[4];
    int         limit = width < height ? width : height;

    limit = limit * LIMIT_RATIO;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, \
	    color.b, color.a);

    shapes[0] = {x, y, limit, height};
    shapes[1] = {x + width - limit, y, limit, height};

    shapes[2] = {x + limit, y, width - 2 * limit, limit};
    shapes[3] = {x + limit, y + height - limit, width - 2 * limit, limit};

    for (const auto& shape : shapes)
        SDL_RenderFillRect(renderer, &shape);
}

void    Render::renderCornerSelect(const int x, const int y, const int width, \
    const int height, const Color& color, SDL_Renderer* renderer)
{
    SDL_Rect    shapes[8];
    int         limit = width < height ? width : height;

    limit = limit * LIMIT_RATIO;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, \
	    color.b, color.a);

    shapes[0] = {x, y, limit * 4, limit};
    shapes[1] = {x + width - (limit * 4), y + height - limit, limit * 4, limit};

    shapes[2] = {x, y + limit, limit, limit * 4};
    shapes[3] = {x + width - limit, y + height - (limit * 4) - limit, limit, limit * 4};

    shapes[4] = {x + width - (limit * 4), y, limit * 4, limit};
    shapes[5] = {x, y + height - limit, limit * 4, limit};

    shapes[6] = {x + width - limit, y, limit, limit * 4};
    shapes[7] = {x, y + height - (limit * 4), limit, limit * 4};

    for (const auto& shape : shapes)
        SDL_RenderFillRect(renderer, &shape);
}

void    Render::renderCenterSelectCross(const int x, const int y, const int width, \
    const int height, const Color& color, SDL_Renderer* renderer)
{
    int     size = width < height ? width : height;
    int     thickness = size * LIMIT_RATIO;

    float   centerX = x + (width - size) / 2.0f;
    float   centerY = y + (height - size) / 2.0f;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < thickness; i++)
    {
        SDL_RenderDrawLine(renderer, centerX + i - thickness / 2.0f, centerY, \
            centerX + size + i - thickness / 2.0f, centerY + size);

        SDL_RenderDrawLine(renderer, centerX + i - thickness / 2.0f, centerY + size, \
            centerX + size + i - thickness / 2.0f, centerY);
    }
}

void    Render::renderSelect(const int value, const int x, const int y, const int width, \
    const int height, const Color& color, SDL_Renderer* renderer)
{
    if (value == BORDER_SELECT)
        renderBorderSelect(x, y, width, height, color, renderer);

    else if (value == CORNER_SELECT)
        renderCornerSelect(x, y, width, height, color, renderer);

    else if (value == CENTER_SELECT_X)
        renderCenterSelectCross(x, y, width, height, color, renderer);

    else if (value == HIGHLIGHT_SELECT)
        renderHighlight(x, y, width, height, color, renderer);
}

void    Render::renderHighlight(const int x, const int y, const int width, \
    const int height, const Color& color, SDL_Renderer* renderer)
{
    SDL_Rect    highlight = {x, y, width, height};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, \
        color.b, color.a);

    SDL_RenderFillRect(renderer, &highlight);
}
