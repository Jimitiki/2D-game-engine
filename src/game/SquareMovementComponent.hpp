#ifndef SQUAREMOVEMENTCOMPONENT
#define SQUAREMOVEMENTCOMPONENT

#include "../engine/MovementComponent.hpp"

#include "../engine/geometry.hpp"

class SquareMovementComponent : public MovementComponent
{
public:
	SquareMovementComponent() : MovementComponent(), speed(0), duration(1) {}
	SquareMovementComponent(float speed, float duration) : MovementComponent(), speed(speed), duration(duration) {}
	virtual void update(int delta_t);

private:
	int elapsed_time = 0;
	float speed;
	float duration;
};

#endif