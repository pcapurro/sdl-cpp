#ifndef TEST_WINDOW_HPP
# define TEST_WINDOW_HPP

# include "Window.hpp"
# include "Image.hpp"

class ImageViewer : public Window
{
    private:
        vector<unique_ptr<Element>>		_elements;

    public:
        ImageViewer(const string& name, const int width, const int height, \
			const string& logoPath = "", const int zoom = 100, const bool scaleProp = true, \
			const int logoWidth = LOGO_WIDTH, const int logoHeight = LOGO_HEIGHT);
        ~ImageViewer(void) = default;

		virtual int						routine(void);
		virtual int						waitForEvent(void);

		virtual	void					refreshDisplay(void);
		
		virtual void					render(void);

		virtual void					reactEvent(SDL_Event* event, \
											const int x = 0, const int y = 0);
};

#endif
