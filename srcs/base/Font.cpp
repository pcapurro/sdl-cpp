#include "Font.hpp"

Font::Font(const string& path)
{
	_font = TTF_OpenFont(path.c_str(), 24);

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

void	Font::setPath(const string& newPath)
{
	if (_font)
		TTF_CloseFont(_font);

	_font = TTF_OpenFont(newPath.c_str(), 24);

	if (_font == nullptr)
		throw std::runtime_error("SDL failed to load a new font: " + string(SDL_GetError()));
}
