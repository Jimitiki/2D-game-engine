#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>

#include "EngineCore.hpp"

namespace Event
{
	typedef std::function<void(SDL_Event*, void*)> Callback;
	typedef struct
	{
		SDL_EventType type;
		Event::Callback callback;
		void* arg;
	} Handler;

	void bind(Event::Handler* handler);
	void unbind(Event::Handler* handler);
};

#endif