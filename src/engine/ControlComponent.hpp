#ifndef CONTROLCOMPONENT_HPP_
#define CONTROLCOMPONENT_HPP_

#include <map>
#include <string>

#include "Component.hpp"
#include "ControlManager.hpp"

class ControlComponent : public Component
{
public:
	ControlComponent() : Component(Component::CONTROL) {}

	void bind(Control::DigitalAction* digital_action, std::string action_name);
	void bind(Control::AnalogAction* analog_action, std::string action_name);

	void execute_action(std::string action_name);
	void execute_action(std::string action_name, double value);

	std::map<std::string, Control::DigitalAction> digital_actions;
	std::map<std::string, Control::AnalogAction> analog_actions;
};

#endif