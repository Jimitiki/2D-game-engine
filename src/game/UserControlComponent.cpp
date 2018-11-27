#include "UserControlComponent.hpp"

#include "../engine/MovementComponent.hpp"

UserControlComponent::UserControlComponent()
{
	Control::DigitalAction l_action = std::bind(&UserControlComponent::move_h, this, -1);
	Control::DigitalAction r_action = std::bind(&UserControlComponent::move_h, this, 1);
	Control::DigitalAction u_action = std::bind(&UserControlComponent::move_v, this, -1);
	Control::DigitalAction d_action = std::bind(&UserControlComponent::move_v, this, 1);
	this->bind(&l_action, "movel");
	this->bind(&r_action, "mover");
	this->bind(&u_action, "moveu");
	this->bind(&d_action, "moved");
}

void UserControlComponent::move_h(short direction)
{
	MovementComponent* m_component = (MovementComponent*) this->get_sibling_component(Component::Type::MOVEMENT);
	m_component->velocity.x = direction * 120;
}

void UserControlComponent::move_v(short direction)
{
	MovementComponent* m_component = (MovementComponent*) this->get_sibling_component(Component::Type::MOVEMENT);
	m_component->velocity.y = direction * 120;
}