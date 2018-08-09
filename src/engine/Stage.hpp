#ifndef STAGE_HPP_
#define STAGE_HPP_

#include "EngineCore.hpp"
#include "RectD.hpp"

namespace Stage
{
	PointD bounds();
	PointD player_position();
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
}

#endif