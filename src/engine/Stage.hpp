#ifndef STAGE_HPP_
#define STAGE_HPP_

#include "EngineCore.hpp"
#include "geometry.hpp"
#include "IScene.hpp"

namespace Stage
{
	Vec2D get_bounds();
	void play_scene(IScene *scene);
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
}

#endif