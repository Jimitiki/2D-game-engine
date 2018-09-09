#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include <map>

#include "Component.hpp"

class Entity
{
public:
	~Entity();
	uint64_t get_type_id() const;
	Component* get_component(Component::Type component_type);
	void add_entity(Entity* entity);
	void add_component(Component* component);
	void remove_component(Component::Type component_type);

private:

	uint64_t type_id;
	std::vector<Entity*> entities;
	std::map<Component::Type, Component*> components;
};

#endif