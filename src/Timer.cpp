#include <vector>
#include <queue>
#include "Timer.hpp"

typedef struct
{
	void (*callback_fn) (void *);
	void *arg;
	int delay;
	int interval;
	int call_timer;
} timer_callback;

namespace Timer
{
	namespace
	{
		std::vector<timer_callback *> callbacks;
		std::queue<int> unbound_slots;
	}
}

int Timer::bind(void (*callback_fn) (void *), int delay, void *arg)
{
	return bind(callback_fn, delay, -1, arg);
}


int Timer::bind(void (*callback_fn) (void *), int delay, int interval, void *arg)
{
	timer_callback *callback = new timer_callback;
	callback->callback_fn = callback_fn;
	callback->delay = delay;
	callback->interval = -1;
	callback->arg = arg;
	callback->call_timer = delay;

	if (unbound_slots.size() == 0)
	{
		callbacks.push_back(callback);
		return callbacks.size() - 1;
	}
	int timer_id = unbound_slots.front();
	callbacks[timer_id] = callback;
	return timer_id;
}

void Timer::unbind(int timer_id)
{
	delete callbacks[timer_id];
	callbacks[timer_id] = nullptr;
	unbound_slots.push(timer_id);
}

void Timer::update(int delta_time)
{
	for (unsigned int i = 0; i < callbacks.size(); i++)
	{
		if (callbacks[i] == nullptr)
		{
			continue;
		}
		
		callbacks[i]->call_timer -= delta_time;
		if (callbacks[i]->call_timer > 0)
		{
			continue;
		}
		callbacks[i]->callback_fn(callbacks[i]->arg);
		if (callbacks[i]->interval > 0)
		{
			callbacks[i]->call_timer += callbacks[i]->interval;
		}
		else
		{
			unbind(i);
		}
	}
}