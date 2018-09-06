#include "Entity.hpp"

#include "Component.hpp"
#include "EngineCore.hpp"

uint64_t Entity::get_type_id() const
{
	return type_id;
}

std::vector<Component*>* Entity::get_components_by_type(Component::Type component_type)
{
	std::map<Component::Type, std::vector<Component*>>::iterator it = components.find(component_type);
	if (it == components.end())
	{
		return nullptr;
	}
	return &(it->second);
}

void Entity::add_entity(Entity* entity)
{
	entities.push_back(entity);
}

void Entity::add_component(Component* component)
{
	std::pair<std::map<Component::Type, std::vector<Component*>>::iterator, bool> location;
	location = components.insert(std::pair<Component::Type, std::vector<Component*>>(component->component_type, std::vector<Component*>()));
	this->type_id |= component->component_type;
	location.first->second.push_back(component);
}