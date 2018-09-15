#include "ControlManager.hpp"

#include "ControlComponent.hpp"

void Control::update(int delta_t, const std::vector<Entity*>* entities)
{
	for (Entity* entity : *entities)
	{
		if (entity->get_type_id() & Component::Type::CONTROL)
		{
			ControlComponent* component = (ControlComponent*) entity->get_component(Component::Type::CONTROL);
			component->update(delta_t);
		}
	}
}