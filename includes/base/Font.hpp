#ifndef FONT_HPP
# define FONT_HPP

# include "Global.hpp"

class Font
{
    private:
        TTF_Font*   _font = nullptr;

    public:
        Font(void) = delete;
        Font(const string& path);
        Font(const Font& original) = delete;
        Font(Font&& original) noexcept;

        Font&	    operator=(const Font& original) noexcept = delete;
        Font&       operator=(Font&& original) noexcept;

        ~Font(void) noexcept;

        void    setPath(const string& newPath);
};

#endif
