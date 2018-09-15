#include "SquareControlComponent.hpp"

#include "../engine/MovementComponent.hpp"
#include "../engine/Timer.hpp"

SquareControlComponent::SquareControlComponent()
{
	Control::DigitalAction action = std::bind(&SquareControlComponent::turn, this);
	this->bind(&action, "turn");

	Timer::Callback callback = std::bind(static_cast<void (SquareControlComponent::*)(std::string action_name)> (&ControlComponent::execute_action), this, "turn");
	Timer::bind(&callback, 0, 300);
}

void SquareControlComponent::update(int delta_t)
{
	/*elapsed_time += delta_t;
	if (elapsed_time > 300)
	{
		this->execute_action("turn");
		elapsed_time = 0;
	}*/
}

void SquareControlComponent::turn()
{
	MovementComponent* m_component = (MovementComponent*) this->get_sibling_component(Component::MOVEMENT);
	if (m_component->velocity.x != 0)
	{
		m_component->velocity.y = m_component->velocity.x;
		m_component->velocity.x = 0;
	}
	else if (m_component->velocity.y != 0)
	{
		m_component->velocity.x = -m_component->velocity.y;
		m_component->velocity.y = 0;
	}
	else
	{
		m_component->velocity.x = -520;
	}
}