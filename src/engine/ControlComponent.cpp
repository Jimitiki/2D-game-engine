#include "ControlComponent.hpp"

void ControlComponent::bind(Control::DigitalAction* digital_action, std::string action_name)
{
	digital_actions.insert(std::pair<std::string, Control::DigitalAction>(action_name, *digital_action));
}

void ControlComponent::bind(Control::AnalogAction* analog_action, std::string action_name)
{
	analog_actions.insert(std::pair<std::string, Control::AnalogAction>(action_name, *analog_action));
}

void ControlComponent::execute_action(std::string action_name)
{
	digital_actions[action_name]();
}

void ControlComponent::execute_action(std::string action_name, double value)
{
	analog_actions[action_name](value);
}