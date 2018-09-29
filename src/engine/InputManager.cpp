#include "InputManager.hpp"

#include <map>
#include <string>

#include "InputComponent.hpp"
#include "ControlComponent.hpp"

namespace Input
{
	const Uint8* keyboard_state;
};

void Input::init()
{
Input::keyboard_state = SDL_GetKeyboardState(nullptr);
}

void Input::update(int delta_t, const std::vector<Entity*>* entities)
{
	for (Entity* entity : *entities)
	{
		if (entity->get_type_id() & Component::Type::INPUT && entity->get_type_id() & Component::Type::CONTROL)
		{
			InputComponent* component = (InputComponent*) entity->get_component(Component::Type::INPUT);
			ControlComponent* c_component = (ControlComponent*) entity->get_component(Component::Type::CONTROL);
			component->update(delta_t);
			for (std::pair<SDL_Scancode, std::string> input_entry : component->key_inputs)
			{
				if (keyboard_state[input_entry.first])
				{
					c_component->execute_action(input_entry.second);
				}
			}
		}
	}
}
