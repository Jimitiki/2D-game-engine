#include "InputManager.hpp"
#include <map>
#include <vector>

namespace Input
{
	typedef std::vector<Callback *> CallbackList;
	typedef std::map<SDL_Scancode, CallbackList> KeyMap;
	typedef std::map<uint8_t, CallbackList> MouseMap;

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

	CallbackID bind_callback(CallbackID input, input_type type, Callback *callback_fn, CallbackList *callbacks);

	KeyMap key_down_callbacks;
	KeyMap key_hold_callbacks;
	KeyMap key_up_callbacks;

	CallbackList motion_callbacks;
	MouseMap button_down_callbacks;
	MouseMap button_hold_callbacks;
	MouseMap button_up_callbacks;

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
			for (auto& callback_fn : pair.second)
			{
				(*callback_fn)(nullptr);
			}
		}
	}
	for (auto pair : button_hold_callbacks)
	{
		SDL_MouseButtonEvent event;
		event.type = MOUSE_DOWN;
		event.state = SDL_PRESSED;

		if (mouse_states[pair.first - 1])
		{
			event.button = pair.first;
			for (auto& callback_fn : pair.second)
			{
				(*callback_fn)(nullptr);
			}
		}
	}
}

Input::CallbackID Input::bind_key_down(SDL_Scancode key, Callback *callback_fn)
{
	return bind_callback(key, KEY_DOWN, callback_fn, &key_down_callbacks[key]);
}

Input::CallbackID Input::bind_key_hold(SDL_Scancode key, Callback *callback_fn)
{
	return bind_callback(key, KEY_HOLD, callback_fn, &key_hold_callbacks[key]);
}

Input::CallbackID Input::bind_key_up(SDL_Scancode key, Callback *callback_fn)
{
	return bind_callback(key, KEY_UP, callback_fn, &key_up_callbacks[key]);
}

Input::CallbackID Input::bind_mouse_move(Callback *callback_fn)
{
	if (motion_callbacks.size() == 65535)
	{
		throw at_capacity();
	}
	motion_callbacks.push_back(callback_fn);
	return MOUSE_MOVE << 25 | motion_callbacks.size() - 1;
}

Input::CallbackID Input::bind_button_down(uint8_t button, Callback *callback_fn)
{
	return bind_callback(button, MOUSE_DOWN, callback_fn, &button_down_callbacks[button]);
}

Input::CallbackID Input::bind_button_hold(uint8_t button, Callback *callback_fn)
{
	return bind_callback(button, MOUSE_HOLD, callback_fn, &button_hold_callbacks[button]);
}

Input::CallbackID Input::bind_button_up(uint8_t button, Callback *callback_fn)
{
	return bind_callback(button, MOUSE_UP, callback_fn, &button_up_callbacks[button]);
}

Input::CallbackID Input::bind_callback(CallbackID input, input_type type, Callback *callback_fn, CallbackList *callbacks)
{
	if (callbacks->size() == 65535)	//16 bits. I figure 65 thousand callbacks is more than enough for one input.
	{
		throw at_capacity();
	}
	Callback *fn = new Callback;
	*fn = *callback_fn; // Copy the callback using allocated memory so that we can feel "safe" managing it here.
	callbacks->push_back(fn);
	return type << 25 | input << 16 | static_cast<CallbackID> (callbacks->size() - 1); //append the input type and the key code to the index
}

void Input::handle_input_event(SDL_Event *event)
{
	try
	{
		CallbackList *callbacks;
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
					callbacks = &motion_callbacks;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					SDL_MouseButtonEvent *m_event = reinterpret_cast<SDL_MouseButtonEvent *> (event);
					mouse_states[m_event->button] = true;
					callbacks = &button_down_callbacks.at(m_event->button);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				{
					SDL_MouseButtonEvent *m_event = reinterpret_cast<SDL_MouseButtonEvent *> (event);
					mouse_states[m_event->button] = false;
					callbacks = &button_up_callbacks.at(m_event->button);
				}
				break;
			default:
				return;
		}

		for (auto& callback_fn : *callbacks)
		{
			if (callback_fn != nullptr)
			{
				(*callback_fn)(event);
			}
		}
	}
	catch (std::out_of_range) {}
}

Input::Callback *Input::unbind(CallbackID id)
{
	int index = id & 0x0000FFFF;
	id = id >> 16;
	int input = id & 0x01FF;
	input_type type = static_cast<input_type> (id >> 9);

	CallbackList *callbacks = nullptr;
	Callback *callback_fn;

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
				callbacks = &motion_callbacks;
				break;
			case MOUSE_DOWN:
				callbacks = &button_down_callbacks.at(input);
				break;
			case MOUSE_HOLD:
				callbacks = &button_down_callbacks.at(input);
				break;
			case MOUSE_UP:
				callbacks = &button_down_callbacks.at(input);
				break;
			default:
				return nullptr;
		}

		if (callbacks == nullptr)
		{
			return nullptr;
		}
		callback_fn = callbacks->at(index);
		callbacks->at(index) = nullptr;
	}
	catch (std::out_of_range)
	{
		callback_fn = nullptr;
	}
	return callback_fn;
}