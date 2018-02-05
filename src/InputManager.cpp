#include "InputManager.hpp"
#include <map>
#include <vector>

namespace Input
{
	typedef std::vector<callback *> callback_list;
	typedef std::map<SDL_Scancode, callback_list> key_map;
	typedef std::map<uint8_t, callback_list> mouse_map;

	typedef enum
	{
		KEY_DOWN = 0,
		KEY_HOLD = 1,
		KEY_UP = 2,
		MOUSE_MOVE = 3,
		MOUSE_DOWN = 4,
		MOUSE_HOLD = 5,
		MOUSE_UP = 6
	} input_type;

	uint32_t bind_callback(uint32_t input, input_type type, callback *fn, callback_list *callbacks);

	key_map key_down_callbacks;
	key_map key_hold_callbacks;
	key_map key_up_callbacks;

	callback_list mouse_motion_callbacks;
	mouse_map mouse_button_down_callbacks;
	mouse_map mouse_button_hold_callbacks;
	mouse_map mouse_button_up_callbacks;

	std::vector<bool> key_states(SDL_NUM_SCANCODES);
	std::vector<bool> mouse_states(5);
}

void Input::update()
{
	for (auto pair : key_hold_callbacks)
	{
		SDL_KeyboardEvent event;
		event.type = KEY_DOWN;
		event.state = SDL_PRESSED;
		event.keysym.mod = SDL_GetModState();

		if (key_states[pair.first])
		{
			event.keysym.scancode = pair.first;
			event.keysym.sym = SDL_GetKeyFromScancode(pair.first);
			for (auto& fn : pair.second)
			{
				(*fn)(nullptr);
			}
		}
	}
	for (auto pair : mouse_button_hold_callbacks)
	{
		SDL_MouseButtonEvent event;
		event.type = MOUSE_DOWN;
		event.state = SDL_PRESSED;

		if (mouse_states[pair.first - 1])
		{
			event.button = pair.first;
			for (auto& fn : pair.second)
			{
				(*fn)(nullptr);
			}
		}
	}
}

uint32_t Input::bind_key_down(SDL_Scancode key, callback *fn)
{
	return bind_callback(key, KEY_DOWN, fn, &key_down_callbacks[key]);
}

uint32_t Input::bind_key_hold(SDL_Scancode key, callback *fn)
{
	return bind_callback(key, KEY_HOLD, fn, &key_hold_callbacks[key]);
}

uint32_t Input::bind_key_up(SDL_Scancode key, callback *fn)
{
	return bind_callback(key, KEY_UP, fn, &key_up_callbacks[key]);
}

uint32_t Input::bind_mouse_move(callback *fn)
{
	if (mouse_motion_callbacks.size() == 65535)
	{
		throw at_capacity();
	}
	mouse_motion_callbacks.push_back(fn);
	return MOUSE_MOVE << 25 | mouse_motion_callbacks.size() - 1;
}

uint32_t Input::bind_mouse_button_down(uint8_t button, callback *fn)
{
	return bind_callback(button, MOUSE_DOWN, fn, &mouse_button_down_callbacks[button]);
}

uint32_t Input::bind_mouse_button_hold(uint8_t button, callback *fn)
{
	return bind_callback(button, MOUSE_HOLD, fn, &mouse_button_hold_callbacks[button]);
}

uint32_t Input::bind_mouse_button_up(uint8_t button, callback *fn)
{
	return bind_callback(button, MOUSE_UP, fn, &mouse_button_up_callbacks[button]);
}

uint32_t Input::bind_callback(uint32_t input, input_type type, callback *fn, callback_list *callbacks)
{
	if (callbacks->size() == 65535)	//16 bits. I figure 65 thousand callbacks is more than enough for one input.
	{
		throw at_capacity();
	}
	callbacks->push_back(fn);
	return type << 25 | input << 16 | static_cast<uint32_t> (callbacks->size() - 1); //append the input type and the key code to the index
}

void Input::handle_input_event(SDL_Event *event)
{
	try
	{
		callback_list *callbacks;
		switch(event->type)
		{
			case SDL_KEYDOWN:
				{
					SDL_KeyboardEvent *k_event = reinterpret_cast<SDL_KeyboardEvent *> (event);
					key_states[k_event->keysym.scancode] = true;
					callbacks = &key_down_callbacks.at(k_event->keysym.scancode);
				}
				break;
			case SDL_KEYUP:
				{
					SDL_KeyboardEvent *k_event = reinterpret_cast<SDL_KeyboardEvent *> (event);
					key_states[k_event->keysym.scancode] = false;
					callbacks = &key_up_callbacks.at(k_event->keysym.scancode);
				}
				break;
			case SDL_MOUSEMOTION:
				{
					callbacks = &mouse_motion_callbacks;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					SDL_MouseButtonEvent *m_event = reinterpret_cast<SDL_MouseButtonEvent *> (event);
					mouse_states[m_event->button] = true;
					callbacks = &mouse_button_down_callbacks.at(m_event->button);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				{
					SDL_MouseButtonEvent *m_event = reinterpret_cast<SDL_MouseButtonEvent *> (event);
					mouse_states[m_event->button] = false;
					callbacks = &mouse_button_up_callbacks.at(m_event->button);
				}
				break;
			default:
				return;
		}

		for (auto& fn : *callbacks)
		{
			if (fn != nullptr)
			{
				(*fn)(event);
			}
		}
	}
	catch (std::out_of_range) {}
}

Input::callback *Input::unbind(uint32_t id)
{
	int index = id & 0x0000FFFF;
	id = id >> 16;
	int input = id & 0x01FF;
	input_type type = static_cast<input_type> (id >> 9);

	callback_list *callbacks = nullptr;
	callback *fn;

	try{
		switch(type)
		{
			case KEY_DOWN:
				callbacks = &key_down_callbacks.at(static_cast<SDL_Scancode> (input));
				break;
			case KEY_HOLD:
				static_cast<SDL_Scancode> (input);
				callbacks = &key_hold_callbacks.at(static_cast<SDL_Scancode> (input));
				break;
			case KEY_UP:
				callbacks = &key_up_callbacks.at(static_cast<SDL_Scancode> (input));
				break;
			case MOUSE_MOVE:
				callbacks = &mouse_motion_callbacks;
				break;
			case MOUSE_DOWN:
				callbacks = &mouse_button_down_callbacks.at(input);
				break;
			case MOUSE_HOLD:
				callbacks = &mouse_button_down_callbacks.at(input);
				break;
			case MOUSE_UP:
				callbacks = &mouse_button_down_callbacks.at(input);
				break;
			default:
				return nullptr;
		}

		if (callbacks == nullptr)
		{
			return nullptr;
		}
		fn = callbacks->at(index);
		callbacks->at(index) = nullptr;
	}
	catch (std::out_of_range)
	{
		fn = nullptr;
	}
	return fn;
}