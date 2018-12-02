#ifndef USERCONTROLCOMPONENT_HPP_
#define USERCONTROLCOMPONENT_HPP_

#include "../engine/ControlComponent.hpp"
#include "../engine/InputManager.hpp"

class UserControlComponent : public ControlComponent
{
public:
	UserControlComponent();

private:
	void move_h(short direction);
	void move_v(short direction);

	static void handle_input(std::string control, void* arg);

	std::vector<Input::Handler> inputs;
};

#endif