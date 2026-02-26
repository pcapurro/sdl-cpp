#include "Engine.hpp"

Engine::Engine(const bool video, const bool antialiasing, \
    const bool ttf, const bool events, const bool audio)
{
    if (video)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("SDL failed to init video: " + string(SDL_GetError()));

        if (antialiasing)
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        if (ttf)
            _ttf.emplace();
    }

    if (events && SDL_Init(SDL_INIT_EVENTS) != 0)
        throw std::runtime_error("SDL failed to init events: " + string(SDL_GetError()));

    if (audio && SDL_Init(SDL_INIT_AUDIO) != 0)
        throw std::runtime_error("SDL failed to init audio: " + string(SDL_GetError()));
}

Engine::~Engine(void)
{
    SDL_Quit();
}
