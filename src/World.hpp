#ifndef WORLD_HPP_
#define WORLD_HPP_

struct SDL_Renderer;
struct PointF;

namespace World
{
	PointF bounds();
	PointF player_position();
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
}

#endif