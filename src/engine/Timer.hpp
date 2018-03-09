#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <functional>

namespace Timer
{
	int bind(std::function <void()> callback_fn, int delay);
	int bind(std::function <void()> callback_fn, int delay, int interval);
	void unbind(int timer_id);
	void update(int delta_time);
}

#endif