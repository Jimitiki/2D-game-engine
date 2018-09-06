#ifndef GRAPHICSMANAGER_HPP_
#define GRAPHICSMANAGER_HPP_

#include <vector>

#include "Entity.hpp"
#include "EngineCore.hpp"

namespace Graphics
{
	void init(SDL_Renderer* renderer);
	void draw(const std::vector<Entity*>* entities);
}

#endif