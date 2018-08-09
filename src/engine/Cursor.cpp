#include "Cursor.hpp"

#include "AssetManager.hpp"

Cursor::Cursor(std::string *image_name, SDL_Rect *src_rect, PointD *dimensions)
{
	dest_rect = new SDL_Rect;
	if (src_rect != nullptr)
	{
		this->src_rect = new SDL_Rect;
		*(this->src_rect) = *src_rect;
	}
	dest_rect->w = dimensions->x;
	dest_rect->h = dimensions->y;

	SDL_Surface *surface;
	Asset::image(image_name, &surface);
	texture = SDL_CreateTextureFromSurface(Engine::get_renderer(), surface);
	if (texture == nullptr)
	{
		print_sdl_error();
	}
}

void Cursor::update(int delta_time)
{
	SDL_GetMouseState(&dest_rect->x, &dest_rect->y);
}

void Cursor::draw(SDL_Renderer *renderer)
{
	SDL_Rect dest = *dest_rect;
	if (texture != nullptr)
	{
		SDL_RenderCopy(renderer, texture, src_rect, &dest);
	}
}

