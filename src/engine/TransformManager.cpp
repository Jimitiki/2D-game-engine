#include "TransformManager.hpp"

#include "TransformComponent.hpp"
#include "MovementComponent.hpp"

void Transform::update(int delta_t, const std::vector<Entity*>* entities)
{
	for (Entity* entity : *entities)
	{
		if (entity->get_type_id() & Component::Type::TRANSFORM && entity->get_type_id() & Component::Type::MOVEMENT)
		{
			TransformComponent* component = (TransformComponent*) entity->get_component(Component::Type::TRANSFORM);
			MovementComponent* m_component = (MovementComponent*) entity->get_component(Component::Type::MOVEMENT);
			component->update(delta_t);
			component->position.x += m_component->velocity.x / 1000 * delta_t;
			component->position.y += m_component->velocity.y / 1000 * delta_t;
		}
	}
}