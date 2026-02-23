#include "Element.hpp"

Element::Element(Config config) noexcept : _config(std::move(config)) {}

Element::Element(Element&& original) noexcept : _config(std::move(original._config)) {}

void	Element::draw(SDL_Renderer* renderer)
{
	SDL_Rect	obj;

	obj.x = _config.x, obj.y = _config.y;
	obj.w = _config.w, obj.h = _config.h;

	if (_config.visibility == true)
	{
		SDL_SetRenderDrawColor(renderer, _config.color.r, \
			_config.color.g, _config.color.b, _config.color.a);

		if (_config.texture.getTexture())
			SDL_RenderCopy(renderer, _config.texture.getTexture(), nullptr, &obj);
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
