#include "Component.hpp"

#include "Entity.hpp"

void Component::set_parent(Entity* parent)
{
	this->parent = parent;
}

Component* Component::get_sibling_component(Component::Type component_type)
{
	if (parent == nullptr)
	{
		return nullptr;
	}
	return parent->get_component(component_type);
}