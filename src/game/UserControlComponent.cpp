#include "UserControlComponent.hpp"

#include "../engine/TransformComponent.hpp"

UserControlComponent::UserControlComponent()
{
	Control::DigitalAction l_action = std::bind(&UserControlComponent::move_l, this);
	Control::DigitalAction r_action = std::bind(&UserControlComponent::move_r, this);
	Control::DigitalAction u_action = std::bind(&UserControlComponent::move_u, this);
	Control::DigitalAction d_action = std::bind(&UserControlComponent::move_d, this);
	this->bind(&l_action, "movel");
	this->bind(&r_action, "mover");
	this->bind(&u_action, "moveu");
	this->bind(&d_action, "moved");
}

void UserControlComponent::move_l()
{
	TransformComponent* t_component = (TransformComponent*) this->get_sibling_component(Component::Type::TRANSFORM);
	t_component->position.x -= 0.5;
}

void UserControlComponent::move_r()
{
	TransformComponent* t_component = (TransformComponent*) this->get_sibling_component(Component::Type::TRANSFORM);
	t_component->position.x += 0.5;
}

void UserControlComponent::move_u()
{
	TransformComponent* t_component = (TransformComponent*) this->get_sibling_component(Component::Type::TRANSFORM);
	t_component->position.y -= 0.5;
}

void UserControlComponent::move_d()
{
	TransformComponent* t_component = (TransformComponent*) this->get_sibling_component(Component::Type::TRANSFORM);
	t_component->position.y += 0.5;
}