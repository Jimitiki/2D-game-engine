#include "Cursor.hpp"

#include "AssetManager.hpp"

namespace Cursor
{
	typedef struct
	{
		SDL_Texture *texture;
		SDL_Rect *src_rect;
		SDL_Rect *dest_rect;
	} Cursor;

	bool cursor_enabled = false;
	Cursor cursor = {nullptr, nullptr, nullptr};
}

void Cursor::init_cursor(std::string *image_name, SDL_Rect *src_rect, PointD *dimensions)
{
	cursor.dest_rect = new SDL_Rect;
	if (src_rect != nullptr)
	{
		cursor.src_rect = new SDL_Rect;
		*(cursor.src_rect) = *src_rect;
	}
	cursor.dest_rect->w = dimensions->x;
	cursor.dest_rect->h = dimensions->y;

	SDL_Surface *surface;
	Asset::image(image_name, &surface);
	cursor.texture = SDL_CreateTextureFromSurface(Engine::get_renderer(), surface);
	if (cursor.texture == nullptr)
	{
		print_sdl_error();
	}
}

void Cursor::update(int delta_time)
{
	SDL_GetMouseState(&cursor.dest_rect->x, &cursor.dest_rect->y);
}

void Cursor::draw(SDL_Renderer *renderer)
{
	if (!cursor_enabled)
	{
		return;
	}
	SDL_Rect dest = *cursor.dest_rect;
	if (cursor.texture != nullptr)
	{
		SDL_RenderCopy(renderer, cursor.texture, cursor.src_rect, &dest);
	}
}

void Cursor::disable_cursor()
{
	cursor_enabled = false;
}

void Cursor::enable_cursor()
{
	cursor_enabled = true;
}

void Cursor::disable_hardware_cursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void Cursor::enable_hardware_cursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}