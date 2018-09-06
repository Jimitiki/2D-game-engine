#include "Component.hpp"
/*
void Component::add_component(Component* component)
{
	components.push_back(component);
}

Component::~Component()
{
	for (Component* component : components)
	{
		delete component;
	}
}

ComponentType Component::get_type() const
{
	return component_type;
}*/

Component::Component(Component::Type component_type) : component_type(component_type) {}