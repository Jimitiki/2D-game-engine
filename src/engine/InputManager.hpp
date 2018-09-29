#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <functional>
#include <vector>

#include "Entity.hpp"
#include "EngineCore.hpp"
#include "geometry.hpp"


namespace Input
{
	void init();
	void update(int delta_t, const std::vector<Entity*>* entities);
}

#endif