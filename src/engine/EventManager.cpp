#include "EventManager.hpp"

namespace Event
{
	int handle(void* userdata, SDL_Event* event);
}

int Event::handle(void* userdata, SDL_Event* event)
{
	Event::Handler* handler = (Event::Handler*) userdata;
	if (event->type == handler->type)
	{
		handler->callback(event, handler->arg);
	}
	return 0;
}

void Event::bind(Event::Handler* handler)
{
	SDL_AddEventWatch(Event::handle, handler);
}

void Event::unbind(Event::Handler* handler)
{
	SDL_DelEventWatch(Event::handle, handler);
}