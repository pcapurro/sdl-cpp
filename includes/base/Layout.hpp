#ifndef LAYOUT_HPP
# define LAYOUT_HPP

class Layout
{
    public:
        int     xPercent = 0;
        int     yPercent = 0;

        int     widthPercent = 50;
        int     heightPercent = 50;

        bool    xCentered = true;
        bool    yCentered = true;

        bool    scaleProportionally = false;
        int     originalWidth = 100;
        int     originalHeight = 100;
};

#endif
