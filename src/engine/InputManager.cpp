#include "InputManager.hpp"

#include <unordered_map>
#include <string>

#include "EventManager.hpp"

namespace Input
{
	void handle(SDL_Event* event, void* arg);
	bool add_event_handler(Input::Handler* input_handler, Event::Handler* event_handler);
	Event::Handler* remove_event_handler(Input::Handler* input_handler);

	const uint8_t* key_state;
	int num_keys;
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>> input_handlers;
};

void Input::init()
{
	Input::key_state = SDL_GetKeyboardState(&num_keys);
}

void Input::handle(SDL_Event* event, void* arg)
{
	Input::Handler* handler = (Input::Handler*) arg;
	if (handler->key == ((SDL_KeyboardEvent*) event)->keysym.sym)
	{
		handler->callback(handler->arg);
	}
}

void Input::bind(Input::Handler* handler)
{
	Event::Handler* event_handler = new Event::Handler;
	event_handler->type = SDL_KEYDOWN;
	event_handler->arg = (void*) handler;
	event_handler->callback = Input::handle;
	Event::bind(event_handler);
	Input::add_event_handler(handler, event_handler);
}

void Input::unbind(Input::Handler* handler)
{
	Event::Handler* event_handler = Input::remove_event_handler(handler);
	if (event_handler != nullptr)
	{
		Event::unbind(event_handler);
		delete event_handler;
	}
}

void Input::destroy() {}

bool Input::add_event_handler(Input::Handler* input_handler, Event::Handler* event_handler)
{
	std::pair<std::unordered_map<Input::Handler*, Event::Handler*>::iterator, bool> result = input_handlers[input_handler->key].insert(std::pair<Input::Handler*, Event::Handler*>(input_handler, event_handler));
	return result.second;
}

Event::Handler* Input::remove_event_handler(Input::Handler* input_handler)
{
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>>::iterator m_it = input_handlers.find(input_handler->key);
	if (m_it != input_handlers.end())
	{
		std::unordered_map<Input::Handler*, Event::Handler*>::iterator handler_it = m_it->second.find(input_handler);
		if (handler_it != m_it->second.end())
		{
			m_it->second.erase(handler_it);
			return handler_it->second;
		}
	}
	return nullptr;
}

std::string Input::get_keys_pressed()
{
	std::string keys_pressed;
	for (int i = 0; i < Input::num_keys; i++)
	{
		if (Input::key_state[i] == 1)
		{
			const char* key_name = SDL_GetKeyName(i);
			keys_pressed += key_name;
			if (i < Input::num_keys - 1)
			{
				keys_pressed += ", ";
			}
		}
	}
	return keys_pressed;
}
