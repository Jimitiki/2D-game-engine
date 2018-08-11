#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <functional>


namespace Timer
{
	typedef uint32_t CallbackID;
	typedef std::function <void()> Callback;

	CallbackID bind(Callback *callback_fn, int delay);
	CallbackID bind(Callback *callback_fn, int delay, int interval);
	void unbind(CallbackID timer_id);
	void update(int delta_time);
}

#endif