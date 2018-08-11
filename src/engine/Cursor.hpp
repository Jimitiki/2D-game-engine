#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include <string>

#include "RectD.hpp"
#include "EngineCore.hpp"

namespace Cursor
{
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
	void init_cursor(std::string *image_name, SDL_Rect *src_rect, PointD *dimensions);
	void disable_cursor();
	void enable_cursor();
	void disable_hardware_cursor();
	void enable_hardware_cursor();
}

#endif