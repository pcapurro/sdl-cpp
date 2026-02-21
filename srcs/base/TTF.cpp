#include "TTF.hpp"

TTF::TTF(void)
{
    if (TTF_Init() == -1)
        throw std::runtime_error("SDL failed to init TTF: " + string(SDL_GetError()));
}

TTF::~TTF(void)
{
    TTF_Quit();
}
