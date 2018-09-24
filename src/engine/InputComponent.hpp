#ifndef INPUT_COMPONENT_HPP
#define INPUT_COMPONENT_HPP

#include <vector>

#include "Component.hpp"
#include "InputManager.hpp"

class InputComponent : public Component
{
	public:
		InputComponent() : Component(Component::INPUT) {}

		void add_key_input(SDL_Scancode key, Input::Type, std::string action_name);

};

#endif