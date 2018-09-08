#ifndef TRANSFORMCOMPONENT_HPP_
#define TRANSFORMCOMPONENT_HPP_

#include "Component.hpp"
#include "geometry.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent(Vec2D *position, double rotation, Vec2D *scale) : Component(Component::Type::TRANSFORM), position(*position), rotation(rotation), scale(*scale) {};
	Vec2D position;
	double rotation;
	Vec2D scale;
};

#endif