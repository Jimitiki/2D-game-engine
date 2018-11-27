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
	std::map<std::string, Control::DigitalAction>::iterator it = digital_actions.find(action_name);
	if (it != digital_actions.end())
	{
		it->second();
	}
}

void ControlComponent::execute_action(std::string action_name, double value)
{
	std::map<std::string, Control::AnalogAction>::iterator it = analog_actions.find(action_name);
	if (it != analog_actions.end())
	{
		it->second(value);
	}
}