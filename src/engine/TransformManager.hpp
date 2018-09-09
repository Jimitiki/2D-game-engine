#ifndef TRANSFORMMANAGER_HPP_
#define TRANSFORMMANAGER_HPP_

#include <vector>

#include "Entity.hpp"

namespace Transform
{
	void update(int delta_t, const std::vector<Entity*>* entities);
};

#endif