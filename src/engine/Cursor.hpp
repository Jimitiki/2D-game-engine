#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include <string>

#include "RectD.hpp"
#include "EngineCore.hpp"

class Cursor
{
public:
	Cursor(std::string *image_name, SDL_Rect *src_rect, PointD *dimensions);
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);

private:
	SDL_Texture *texture = nullptr;
	SDL_Rect *src_rect = nullptr;
	SDL_Rect *dest_rect = nullptr;
};

namespace Engine
{
	void set_cursor(Cursor *cursor);
	void disable_cursor();
	void enable_cursor();
	bool is_cursor_enabled();
}

#endif