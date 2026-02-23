#include "Element.hpp"

Element::Element(const Config& config) noexcept : _config(config) {}

Element::Element(Element&& original) noexcept : _config(original._config)
{
	_texture = original._texture;
}

void	Element::draw(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = _config.x, obj.y = _config.y;
	obj.w = _config.w, obj.h = _config.h;

	if (_config.visibility == true)
	{
		SDL_SetRenderDrawColor(renderer, _config.color.r, \
			_config.color.g, _config.color.b, _config.color.a);

		if (_texture.getTexture())
			SDL_RenderCopy(renderer, _texture.getTexture(), nullptr, &obj);
		else
			SDL_RenderFillRect(renderer, &obj);

		if (_selected == true)
		{
			SDL_SetRenderDrawColor(renderer, 32, 129, 1, 150);
			SDL_RenderFillRect(renderer, &obj);
		}
	}
	
	if (_config.highlight == true && _highlighted == true)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 121);
		SDL_RenderFillRect(renderer, &obj);
	}
}

bool	Element::isAbove(const int x, const int y) const
{
	if (_config.highlight == false)
		return false;

	if (x >= _config.x && x <= _config.x + _config.w)
	{
		if (y >= _config.y && y <= _config.y + _config.h)
			return true;
	}

	return false;
}
