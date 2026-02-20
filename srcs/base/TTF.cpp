#include "TTF.hpp"

TTF::TTF(void)
{
    if (TTF_Init() == -1)
        throw std::runtime_error("SDL failed to init TTF.");
}

TTF::~TTF(void)
{
    TTF_Quit();
}
