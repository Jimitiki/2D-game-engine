#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <vector>


class Component
{
public:
	typedef enum
	{
		NONE     = 0,
		GRAPHICS = 1,
		INPUT    = 2,
		CONTROL  = 4,
		POSITION = 8,
		MOVEMENT = 16
	} Type;

	//void add_component(Component* component);
	virtual ~Component() {}
	//std::vector<Component*> components;
	const Component::Type component_type;

protected:
	Component(Component::Type component_type);
};

#endif