#include "Font.hpp"

Font::Font(const string& path, const int size)
{
	_font = TTF_OpenFont(path.c_str(), size);

	if (_font == nullptr)
		throw std::runtime_error("SDL failed to load a font: " + string(SDL_GetError()));
    }

Font::Font(Font&& original) noexcept
{
    _font = original._font;
    original._font = nullptr;
}

Font&     Font::operator=(Font&& original) noexcept
{
    if (this == &original)
        return *this;

    if (_font)
        TTF_CloseFont(_font);

    _font = original._font;
    original._font = nullptr;

    return *this;
}

Font::~Font(void) noexcept
{
    if (_font)
        TTF_CloseFont(_font);
}

TTF_Font*   Font::getFont(void) const noexcept
{
    return _font;
}
