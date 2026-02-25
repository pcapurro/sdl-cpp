#include "ImageViewer.hpp"

ImageViewer::ImageViewer(const string& name, const int width, \
	const int height, const string& imagePath, const int zoom, \
	const bool scaleProp, const int imageWidth, const int imageHeight) : \
	Window(name, width, height)
{
	Config			imageFrameConfig;

	imageFrameConfig.x = 0;
	imageFrameConfig.y = 0;

	imageFrameConfig.w = width;
    imageFrameConfig.h = height;
	
    imageFrameConfig.type = IMAGE;

	Layout			imageLayout;

	int zoomValue = zoom;

	if (zoom > 100 || zoom < 1)
		zoomValue = 100;

	imageLayout.widthPercent = zoomValue;
	imageLayout.heightPercent = zoomValue;

	imageLayout.xPercent = 50;
	imageLayout.yPercent = 50;

	imageLayout.xCentered = true;
	imageLayout.yCentered = true;

	if (scaleProp)
	{
    	imageLayout.scaleProportionally = true;
    	imageLayout.originalWidth = imageWidth;
    	imageLayout.originalHeight = imageHeight;
	}

	Element			element(imageFrameConfig);

	element.addWidget(std::make_unique<Image>(imagePath.c_str(), getRenderer(), imageLayout));
	_elements.push_back(std::move(element));
}

int     ImageViewer::routine(void)
{
    int     value = OK;

	render();
	refreshDisplay();

    while (true)
    {
        value = waitForEvent();

        if (value != OK)
            return value;
    }

    return OK;
}

int     ImageViewer::waitForEvent(void)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	if (SDL_WaitEvent(&event) == 0)
		throw std::runtime_error("SDL failed listening to events: " + string(SDL_GetError()));

	if (event.type == SDL_QUIT \
		|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		return END;

	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN \
		|| event.key.keysym.sym == SDLK_KP_ENTER))
		return ENTER;

	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN \
		|| event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.type == SDL_MOUSEMOTION)
			x = event.motion.x, y = event.motion.y;
		else if (event.type == SDL_MOUSEBUTTONDOWN \
			|| event.type == SDL_MOUSEBUTTONUP)
			x = event.button.x, y = event.button.y;

		if (x < 0 || x > getWidth() || y < 0 || y > getHeight())
			return OK;
		else
			setX(x), setY(y);

		// cout << event.button.x << " ; " << event.button.y << endl;
		// cout << x << " ; " << y << endl;

		reactEvent(&event, x, y);
	}
	else
		reactEvent(&event);

	return OK;
}

void	ImageViewer::refreshDisplay(void)
{
	clear();
	render();

	display();
}

void	ImageViewer::render(void)
{
	SDL_Renderer*	renderer = getRenderer();

    renderBackground();

	if (renderer)
	{
		for (auto& element : _elements)
			element.render(renderer);
	}
}

void	ImageViewer::reactEvent(SDL_Event* event, \
	const int x, const int y)
{
    if (event->type == SDL_KEYDOWN && event->type == SDL_KEYUP \
		&& event->button.button == SDLK_TAB)
	{
		;
	}

	if (event->type == SDL_MOUSEMOTION)
	{
		for (auto& element : _elements)
		{
			if (element.isAbove(x, y) == true)
				{ display(); return; }
		}
	}
}
