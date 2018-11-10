#ifndef USERCONTROLCOMPONENT_HPP_
#define USERCONTROLCOMPONENT_HPP_

#include "../engine/ControlComponent.hpp"

class UserControlComponent : public ControlComponent
{
public:
	UserControlComponent();

private:
	void move_h(short direction);
	void move_v(short direction);
};

#endif