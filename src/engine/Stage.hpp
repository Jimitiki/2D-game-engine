#ifndef STAGE_HPP_
#define STAGE_HPP_

struct SDL_Renderer;
struct PointD;

namespace Stage
{
	PointD bounds();
	PointD player_position();
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
}

#endif