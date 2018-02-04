#ifndef WORLD_HPP_
#define WORLD_HPP_

struct SDL_Renderer;
struct point_d;

namespace World
{
	point_d bounds();
	point_d player_position();
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
}

#endif