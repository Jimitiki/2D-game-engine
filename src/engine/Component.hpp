#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <vector>

class Entity;

class Component
{
public:
	typedef enum
	{
		NONE      = 0,
		GRAPHICS  = 1,
		INPUT     = 2,
		CONTROL   = 4,
		TRANSFORM = 8,
		MOVEMENT  = 16
	} Type;

	virtual ~Component() {}
	virtual void update() {}
	const Component::Type component_type;

protected:
	Component(Component::Type component_type) : component_type(component_type) {};
	Component* get_sibling_component(Component::Type component_type);

private:
	Entity* parent;
};

#endif