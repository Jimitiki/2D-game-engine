#include "SquareMovementComponent.hpp"

#include <math.h>

#define PI 3.14159265

void SquareMovementComponent::update(int delta_t)
{
	this->elapsed_time += delta_t;
	if (elapsed_time > 1000 * duration)
	{
		elapsed_time = 0;
	}
	this->velocity.x = speed * cos(elapsed_time / (1000.0f * duration) * 2 * PI);
}