#include "Cursor.hpp"
#include "geometry.hpp"
#include "GameCore.hpp"
#include "AssetManager.hpp"

Cursor::Cursor(std::string *image_name, SDL_Rect *src_rect, PointF *dimensions)
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
	texture = SDL_CreateTextureFromSurface(Game::get_renderer(), surface);
	if (texture == nullptr)
	{
		print_sdl_error();
	}
}

void Cursor::update(int delta_time)
{
	int mouse_x;
	int mouse_y;

	Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
	dest_rect->x = mouse_x;
	dest_rect->y = mouse_y;
}

void Cursor::draw(SDL_Renderer *renderer)
{
	SDL_Rect dest = *dest_rect;
	if (texture != nullptr)
	{
		SDL_RenderCopy(renderer, texture, src_rect, &dest);
	}
}

