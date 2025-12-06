#include "Ok.hpp"
#include "OkCancel.hpp"
#include "YesNo.hpp"

int main(void)
{
    try
    {
	    if (SDL_Init(SDL_INIT_VIDEO) != 0)
		    throw std::runtime_error("SDL failed to init video.");
        
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        TTF_Init();

        Ok  window("test", 400, 200, "test", "materials/fonts/OpenSans.ttf");

        window.routine();

        TTF_Quit();
        SDL_Quit();
    }
    catch (std::exception& e)
    {
        cerr << "Error!" << endl;
        cerr << e.what() << endl;

        return 1;
    }

    return 0;
}
