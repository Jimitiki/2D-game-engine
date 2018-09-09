#include "Entity.hpp"

#include "Component.hpp"
#include "EngineCore.hpp"

Entity::~Entity()
{
	std::map<Component::Type, Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
	{
		delete it->second;
	}
}

uint64_t Entity::get_type_id() const
{
	return type_id;
}

Component* Entity::get_component(Component::Type component_type)
{
	std::map<Component::Type, Component*>::iterator it = components.find(component_type);
	if (it == components.end())
	{
		return nullptr;
	}
	return it->second;
}

void Entity::add_entity(Entity* entity)
{
	entities.push_back(entity);
}

void Entity::add_component(Component* component)
{
	std::pair<std::map<Component::Type, Component*>::iterator, bool> location;
	location = components.insert(std::pair<Component::Type, Component*>(component->component_type, component));
	this->type_id |= component->component_type;
}

void Entity::remove_component(Component::Type component_type)
{

}