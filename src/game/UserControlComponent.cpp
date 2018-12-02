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
	this->inputs.push_back(Input::Handler{SDLK_LEFT, std::bind(UserControlComponent::handle_input, "movel", std::placeholders::_1), nullptr});
	this->inputs.push_back(Input::Handler{SDLK_RIGHT, std::bind(UserControlComponent::handle_input, "mover", std::placeholders::_1), nullptr});
	this->inputs.push_back(Input::Handler{SDLK_UP, std::bind(UserControlComponent::handle_input, "moveu", std::placeholders::_1), nullptr});
	this->inputs.push_back(Input::Handler{SDLK_DOWN, std::bind(UserControlComponent::handle_input, "moved", std::placeholders::_1), nullptr});
	for (Input::Handler handler: this->inputs)
	{
		Input::bind(&handler);
	}
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

void UserControlComponent::handle_input(std::string control, void* arg)
{
	((ControlComponent*) arg)->execute_action(control);
}