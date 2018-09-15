#ifndef CONTROLMANAGER_HPP_
#define CONTROLMANAGER_HPP_

#include <vector>
#include <functional>

#include "Entity.hpp"

namespace Control
{
	typedef std::function<void()> DigitalAction;
	typedef std::function<void(uint16_t)> AnalogAction;

	void update(int delta_t, const std::vector<Entity*>* entities);
};

#endif