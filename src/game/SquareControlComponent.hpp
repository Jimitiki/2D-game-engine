#ifndef SQUARECONTROLCOMPONENT_HPP_
#define SQUARECONTROLCOMPONENT_HPP_

#include "../engine/ControlComponent.hpp"

class SquareControlComponent : public ControlComponent
{
public:
	SquareControlComponent();
	void update(int delta_t);

private:
	int elapsed_time = 0;
	void turn();
};

#endif