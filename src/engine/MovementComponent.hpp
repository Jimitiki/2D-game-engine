#ifndef MOVEMENTCOMPONENT_HPP_
#define MOVEMENTCOMPONENT_HPP_

#include "Component.hpp"
#include "geometry.hpp"

class MovementComponent : public Component
{
public:
	MovementComponent(Vec2D *velocity, double angular_velocity) : Component(Component::Type::MOVEMENT), velocity(*velocity), angular_velocity(angular_velocity) {}

	Vec2D velocity;
	float angular_velocity;

protected:
	MovementComponent() : Component(Component::Type::MOVEMENT), velocity{0, 0}, angular_velocity(0) {}
};

#endif