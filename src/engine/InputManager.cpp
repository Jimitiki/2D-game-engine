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
	uint8_t* prev_key_state;
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>> down_events;
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>> hold_events;
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>> up_events;
	const std::unordered_map<Input::Type, SDL_EventType> input_types{{Input::DOWN, SDL_KEYDOWN}, {Input::HOLD, SDL_KEYDOWN}, {Input::UP, SDL_KEYUP}};
	const std::unordered_map<Input::Type, std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>>*> input_maps{{Input::DOWN, &down_events}, {Input::HOLD, &hold_events}, {Input::UP, &up_events}};
};

void Input::init()
{
	int num_keys;
	Input::key_state = SDL_GetKeyboardState(&num_keys);
	Input::prev_key_state = new uint8_t[num_keys]();
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
	event_handler->type = input_types.at(handler->type);
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

void Input::destroy()
{
	delete[] Input::prev_key_state;
}

bool Input::add_event_handler(Input::Handler* input_handler, Event::Handler* event_handler)
{
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>>* m = Input::input_maps.at(input_handler->type);
	std::pair<std::unordered_map<Input::Handler*, Event::Handler*>::iterator, bool> result = (*m)[input_handler->key].insert(std::pair<Input::Handler*, Event::Handler*>(input_handler, event_handler));
	return result.second;
}

Event::Handler* Input::remove_event_handler(Input::Handler* input_handler)
{
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>>* m = Input::input_maps.at(input_handler->type);
	std::unordered_map<SDL_Keycode, std::unordered_map<Input::Handler*, Event::Handler*>>::iterator m_it = m->find(input_handler->type);
	if (m_it != m->end())
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
