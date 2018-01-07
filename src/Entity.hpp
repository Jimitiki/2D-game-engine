#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include "geometry.hpp"

struct SDL_Renderer;
class Sprite;

class Entity
{
	public:
		void update(int delta_time);
		void draw(SDL_Renderer *renderer);

	private:
		PointF position;
		std::vector <Sprite *> sprites;
};

#endif