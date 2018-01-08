#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace Timer
{
	int bind(void (*callback_fn) (void *), int delay, void *arg);
	int bind(void (*callback_fn) (void *), int delay, int interval, void *arg);
	void unbind(int timer_id);
	void update(int delta_time);
}

#endif