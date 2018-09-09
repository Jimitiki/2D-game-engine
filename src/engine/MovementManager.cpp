#include "MovementManager.hpp"

#include "MovementComponent.hpp"
#include <math.h>

void Movement::update(int delta_t, const std::vector<Entity*>* entities)
{
	for (Entity* entity : *entities)
	{
		if (entity->get_type_id() & (Component::Type::GRAPHICS | Component::Type::MOVEMENT))
		{
			MovementComponent* component = (MovementComponent*) entity->get_component(Component::Type::MOVEMENT);
			component->update(delta_t);
		}
	}
}