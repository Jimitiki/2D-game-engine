#include "InputComponent.hpp"
#include "InputManager.hpp"

InputComponent::InputComponent()
{

}

InputComponent::~InputComponent()
{
	for (auto& callback_id : callback_ids)
	{
		Input::unbind(callback_id);
	}
}