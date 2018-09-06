#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include <map>

#include "Component.hpp"

class Entity
{
public:
	uint64_t get_type_id() const;
	std::vector<Component*>* get_components_by_type(Component::Type component_type);
	void add_entity(Entity* entity);
	void add_component(Component* component);

private:

	uint64_t type_id;
	std::vector<Entity*> entities;
	std::map<Component::Type, std::vector<Component*>> components;
};

#endif