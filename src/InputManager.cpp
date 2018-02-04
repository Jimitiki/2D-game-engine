#include "InputManager.hpp"
#include <map>
#include <vector>

namespace Input
{
	namespace
	{
		typedef enum
		{
			KEY_DOWN = 0,
			KEY_HOLD = 1,
			KEY_UP = 2,
			MOUSE_MOVE = 3,
			MOUSE_BUTTON_DOWN = 4,
			MOUSE_BUTTON_HOLD = 5,
			MOUSE_BUTTON_UP = 6
		} input_type;

		std::map<SDL_Scancode, std::vector<callback *>> key_down_callbacks;
		std::map<SDL_Scancode, std::vector<callback *>> key_hold_callbacks;
		std::map<SDL_Scancode, std::vector<callback *>> key_up_callbacks;

		std::vector<callback *> mouse_motion_callbacks;
		std::map<uint8_t, std::vector<callback *>> mouse_button_down_callbacks;
		std::map<uint8_t, std::vector<callback *>> mouse_button_hold_callbacks;
		std::map<uint8_t, std::vector<callback *>> mouse_button_up_callbacks;
	}

}

uint32_t Input::bind_key_hold(SDL_Scancode key, callback *fn)
{
	std::vector<callback *> callbacks = key_hold_callbacks[key];
	if (callbacks.size() == 65535)	//16 bits. I figure 65 thousand callbacks is more than enough for one input.
	{
		throw at_capacity();
	}
	callbacks.push_back(fn);
	return KEY_HOLD << 25 | key << 16 | static_cast<uint32_t> (callbacks.size() - 1); //append the input type and the key code to the index
}

void Input::handle_input_event(SDL_Event *event)
{
	try
	{
		std::vector<callback *> *callbacks;
		printf("Event type: %d\n", event->type);
		switch(event->type)
		{
			case SDL_KEYDOWN:
				{
					SDL_KeyboardEvent *k_event = reinterpret_cast<SDL_KeyboardEvent *> (event);
					callbacks = &key_hold_callbacks.at(k_event->keysym.scancode);
				}
				break;
			case SDL_KEYUP:
				{
					SDL_KeyboardEvent *k_event = reinterpret_cast<SDL_KeyboardEvent *> (event);
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
					callbacks = &mouse_button_hold_callbacks.at(m_event->button);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				{
					{
						SDL_MouseButtonEvent *m_event = reinterpret_cast<SDL_MouseButtonEvent *> (event);
						callbacks = &mouse_button_up_callbacks.at(m_event->button);
					}
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
	int index = id & 0x0000;
	id = id >> 16;
	int input = id & 0x01;
	input_type type = static_cast<input_type> (id >> 9);

	std::vector<callback *> *callbacks;
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
			case MOUSE_BUTTON_DOWN:
				callbacks = &mouse_button_down_callbacks.at(input);
				break;
			case MOUSE_BUTTON_HOLD:
				callbacks = &mouse_button_down_callbacks.at(input);
				break;
			case MOUSE_BUTTON_UP:
				callbacks = &mouse_button_down_callbacks.at(input);
				break;
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