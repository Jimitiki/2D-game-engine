#ifndef MOVEMENTMANAGER_HPP_
#define MOVEMENTMANAGER_HPP_

#include <vector>

#include "Entity.hpp"

namespace Movement
{
	void update(int delta_t, const std::vector<Entity*>* entities);
}

#endif