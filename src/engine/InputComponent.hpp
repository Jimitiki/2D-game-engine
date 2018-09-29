#ifndef INPUT_COMPONENT_HPP
#define INPUT_COMPONENT_HPP

#include <map>

#include "Component.hpp"
#include "InputManager.hpp"

class InputComponent : public Component
{
	public:
		InputComponent() : Component(Component::INPUT) {}
		std::map<SDL_Scancode, std::string> key_inputs;
};

#endif