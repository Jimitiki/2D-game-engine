#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>

#include "EngineCore.hpp"

namespace Event
{
	typedef std::function<void(SDL_Event*)> Callback;
	typedef struct
	{
		SDL_EventType event_type;
		Event::Callback callback;
	} Handler;

	void bind(Event::Handler* handler);
	void unbind(Event::Handler* handler);
};

#endif