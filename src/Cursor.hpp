#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include <string>
#include "geometry.hpp"
#include "GameCore.hpp"

class Cursor
{
public:
	Cursor(std::string *image_name, SDL_Rect *src_rect, PointF *dimensions);
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);

private:
	SDL_Texture *texture = nullptr;
	SDL_Rect *src_rect = nullptr;
	SDL_Rect *dest_rect = nullptr;
};

namespace Game
{
	void set_cursor(Cursor *cursor);
	void disable_cursor();
	void enable_cursor();
	bool is_cursor_enabled();
}

#endif