#ifndef INPUT_COMPONENT_HPP
#define INPUT_COMPONENT_HPP

#include <vector>
#include "EngineCore.hpp"

class InputComponent
{
	public:
		InputComponent();
		~InputComponent();

	private:
		std::vector<Uint32> callback_ids;
};

#endif