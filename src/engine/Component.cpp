#include "Component.hpp"

#include "Entity.hpp"

Component* Component::get_sibling_component(Component::Type component_type)
{
	if (parent == nullptr)
	{
		return nullptr;
	}
	return parent->get_component(component_type);
}