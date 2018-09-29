#ifndef USERCONTROLCOMPONENT_HPP_
#define USERCONTROLCOMPONENT_HPP_

#include "../engine/ControlComponent.hpp"

class UserControlComponent : public ControlComponent
{
public:
	UserControlComponent();

private:
	void move_l();
	void move_r();
	void move_u();
	void move_d();
};

#endif